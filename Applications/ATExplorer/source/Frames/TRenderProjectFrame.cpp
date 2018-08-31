#include <vcl.h>
#pragma hdrstop
#include "TRenderProjectFrame.h"
#include "dslVCLUtils.h"
#include "atRenderServiceParameters.h"
#include "dslLogger.h"
#include "dslFileUtils.h"
#include <gdiplus.h>
#include "atApplicationSupportFunctions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTPropertyCheckBox"
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "dslTFloatLabeledEdit"
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTIntegerEdit"
#pragma link "dslTSTDStringEdit"
#pragma link "RzSpnEdt"
#pragma link "dslTSTDStringLabeledEdit"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

TRenderProjectFrame *RenderProjectFrame;
using namespace dsl;
using namespace at;
int frameNr(0);

//---------------------------------------------------------------------------
__fastcall TRenderProjectFrame::TRenderProjectFrame(RenderProject* rp, TComponent* Owner)
	: TFrame(Owner),
    mRP(rp),
    mRC(IdHTTP1),
   	mCurrentROI(0,0,1000,1000),
    mRenderEnabled(false),
    Drawing(false)
{
	mRC.setBaseURL(mHostURL);
    mRC.assignOnImageCallback(onImage);
    mRC.setLocalCacheFolder(rp->getLocalCacheFolder());
    this->Name = string("RPFrame_" +  dsl::toString(frameNr++)).c_str();
    populate();
    mCurrentROI.assignOnChangeCallback(onROIChanged);
}

void TRenderProjectFrame::populate()
{
    OwnerE->setValue(mRP->getProjectOwner());
    ProjectE->setValue(mRP->getRenderProjectName());

    RenderServiceParameters rsp(mRP->getRenderServiceParameters());
	mRC.setBaseURL(rsp.getBaseURL());

    //Get stacks for project
    StringList stacks = mRC.getStacksForProject(mRP->getProjectOwner(), mRP->getRenderProjectName());
    if(stacks.size())
    {
		StackCB->ItemIndex = populateDropDown(stacks, 		StackCB);
//		populateCheckListBox(stacks, 	StacksForProjectCB);
    }
	StackCBChange(NULL);
}

void TRenderProjectFrame::onROIChanged(void* arg1, void* arg2)
{
    TThread::Synchronize(NULL, &roiChanged);
}

void __fastcall TRenderProjectFrame::roiChanged()
{
    Log(lInfo) << "ROI was changed.";
    XCoordE->setValue(mCurrentROI.getX1());
    YCoordE->setValue(mCurrentROI.getY1());
    Width->setValue(mCurrentROI.getWidth());
    Height->setValue(mCurrentROI.getHeight());
    mScaleE->setValue(mCurrentROI.getScale());
    checkCache();
}

void TRenderProjectFrame::checkCache()
{
    //OtherCB
    StacksCB->Clear();
    OtherCB->Clear();
    StringList stackFiles(getFilesInFolder(mRC.getImageLocalCachePath(), "tif", false));
    for(int i = 0; i < stackFiles.count(); i++)
    {
        if(startsWith("stack_", stackFiles[i]))
        {
            //Setup something robust here later on
            string* item = new string(joinPath(mRC.getImageLocalCachePath(), stackFiles[i]));
            stringstream itemCaption;
            itemCaption << "Stack_"<<i + 1;
            StacksCB->AddItem(vclstr(itemCaption.str()), (TObject*) item);
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TRenderProjectFrame::StackCBChange(TObject *Sender)
{
    if(StackCB->ItemIndex == -1)
    {
		return;
    }

//    string stack = stdstr(StackCB->Items->Strings[StackCB->ItemIndex]);
//	gAU.CurrentStack.setValue(stack);
    mRC.init(mRP->getProjectOwner(), mRP->getRenderProjectName(), stdstr(StackCB->Text));

   	getValidZsForStack();

	ClickZ(NULL);
    updateROIs();
    //Update stack generation page
	//User changed stack.. Clear check list box and select current one
//    for(int i = 0; i < StacksForProjectCB->Items->Count; i++)
//    {
//    	StacksForProjectCB->Checked[i] = (StacksForProjectCB->Items->Strings[i] == StackCB->Text) ? true : false;
//    }

//	StackCB->Hint = vclstr(stack);

    //Disable uninitialized sections of the UI
	enableDisableGroupBox(imageParasGB, true);
	enableDisableGroupBox(Zs_GB, true);
	mRenderEnabled = true;
}

void __fastcall TRenderProjectFrame::getValidZsForStack()
{
	//Fetch valid zs for current project

    mRC.init(mRP->getProjectOwner(), mRP->getRenderProjectName(), stdstr(StackCB->Text));

    StringList zs = mRC.getValidZs();

	Log(lInfo) << "Fetched "<<zs.count()<<" valid z's";

	Zs_GB->Caption = " Z Values (" + IntToStr((int) zs.count()) + ") ";

    //Populate list box
	populateCheckListBox(zs, mZs);
    mZs->CheckAll(cbChecked);
}

//---------------------------------------------------------------------------
void __fastcall TRenderProjectFrame::ClickZ(TObject *Sender)
{
    if(mZs->ItemIndex == -1)
    {
    	return;
    }

    int z = toInt(stdstr(mZs->Items->Strings[mZs->ItemIndex]));

    //Fetch data using URL
	mRC.init(mRP->getProjectOwner(), mRP->getRenderProjectName(), stdstr(StackCB->Text), "jpeg-image", z, mCurrentROI, mScaleE->getValue(), MinIntensityE->getValue(), MaxIntensityE->getValue());

    if(VisualsPC->Pages[VisualsPC->TabIndex] == TabSheet2)
    {
		this->Image1->Cursor = crHourGlass;
        StringList paras;
//        paras.append(string("&maxTileSpecsToRender=") + stdstr(maxTileSpecsToRenderE->Text));
        paras.append(string("&maxTileSpecsToRender=150"));

    	//Image pops up in onImage callback
	    mRC.getImageInThread(z, paras);
    }
    else
    {
//		OpenInNDVIZBtnClick(NULL);
    }

//    URLE->setValue(createNDVIZURL());
}

//This is called from a thread and need to be synchronized with the UI main thread
void __fastcall TRenderProjectFrame::onImage()
{
	TMemoryStream* imageMem = mRC.getImageMemory();
    if(!imageMem)
    {
    	return;
    }

    if(!fileExists(mRC.getImageLocalCachePathAndFileName()))
    {
        Log(lError) << "File does not exist: " <<mRC.getImageLocalCachePathAndFileName();
        return;
    }

    mCurrentImageFile = mRC.getImageLocalCachePathAndFileName().c_str();
	double val = CustomImageRotationE->getValue();
    if(val != 0)
    {
		paintRotatedImage(val);
    }
    else
    {
        try
        {
            //Create a temporary stream
            unique_ptr<TMemoryStream> stream = unique_ptr<TMemoryStream>(new TMemoryStream());
            stream->LoadFromFile(mCurrentImageFile.c_str());
            if(stream->Size)
            {
            	stream->Position = 0;
                Image1->Picture->LoadFromStream(stream.get());
            }
        }
        catch(...)
        {
            Log(lError) << "Failed to load image: "<<mCurrentImageFile;
            return;
        }
    }

//    if(gImageForm && gImageForm->Visible)
//    {
//    	gImageForm->load(mCurrentImageFile);
//    }

    Image1->Refresh();

    Log(lDebug3) << "WxH = " <<Image1->Picture->Width << "x" << Image1->Picture->Height;
    this->Image1->Cursor = crDefault;
}

//---------------------------------------------------------------------------
void TRenderProjectFrame::paintRotatedImage(double angle)
{
    Image1->Align = alNone;
    Image1->Picture = NULL;
    TCanvas* c = Image1->Canvas;

    wstring fName(mCurrentImageFile.begin(), mCurrentImageFile.end());
    Gdiplus::Image image(fName.c_str());

    //Get native image dimensions
    Image1->Height = image.GetHeight();
	Image1->Width = image.GetWidth();

    Gdiplus::Graphics graphics(c->Handle);

    Gdiplus::PointF center(Image1->Width/2, Image1->Height/2);
    Gdiplus::Matrix matrix;

    matrix.RotateAt(angle, center);
    graphics.SetTransform(&matrix);

    c->Brush->Color = clBlack;
	c->Rectangle(0,0, PaintBox1->Width, PaintBox1->Height);

    //draw rotated image
    graphics.DrawImage(&image,0, 0, Image1->Width, Image1->Height);

    Image1->Align = alClient;
    Image1->Invalidate();
}

void __fastcall TRenderProjectFrame::ResetButtonClick(TObject *Sender)
{
	try
    {
	    //mScaleE->setValue(0.05 * ScaleConstantE->getValue());
        mCurrentROI = mRC.getLayerBoundsForZ(getCurrentZ());

        XCoordE->setValue(mCurrentROI.getX1());
        YCoordE->setValue(mCurrentROI.getY1());
        Width->setValue(mCurrentROI.getWidth());
        Height->setValue(mCurrentROI.getHeight());
	    updateScale();

        ClickZ(NULL);
        Log(lDebug1) << "Origin: (X0,Y0) = (" << XCoordE->getValue() + Width->getValue()/2.<<"," <<YCoordE->getValue() + Height->getValue()/2.<<")";
	    checkCache();
        updateROIs();
    }
    catch(...)
    {}
}

int	TRenderProjectFrame::getCurrentZ()
{
	int ii = mZs->ItemIndex;
    if(ii == -1)
    {
    	return -1;
    }

    return toInt(stdstr(mZs->Items->Strings[ii]));
}

//---------------------------------------------------------------------------
void TRenderProjectFrame::updateScale()
{
//    mCurrentROI = RegionOfInterest(XCoordE->getValue(), YCoordE->getValue(), Width->getValue(), Height->getValue());

    //Scale the scaling
    double scale  = (double) Image1->Height / (double) mCurrentROI.getHeight();
    Log(lDebug5) << "Image Scale: " << scale;
	if(scale < 0.005)
    {
    	scale = 0.009;
    }
    else if(scale > 1.0)
    {
    	scale = 1.0;
    }
	mScaleE->setValue(scale);
    mCurrentROI.setScale(scale);
}

void TRenderProjectFrame::updateROIs()
{
    StringList rois(mRC.getROIFoldersForCurrentStack());
    populateCheckListBox(rois, ROI_CB);
}

//---------------------------------------------------------------------------
void __fastcall TRenderProjectFrame::FrameMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if(mRenderEnabled == false)
    {
    	return;
    }

	if(Button == TMouseButton::mbRight)
    {
        return;
    }

	double stretchFactor = getImageStretchFactor();
	if(Button == TMouseButton::mbMiddle)
    {
       	Screen->Cursor = crSize;
		mTopLeftSelCorner = Mouse->CursorPos;
		mTopLeftSelCorner = this->Image1->ScreenToClient(mTopLeftSelCorner);

		//Convert to world image coords (minus offset)
	    mTopLeftSelCorner = controlToImage(mTopLeftSelCorner, mScaleE->getValue(), stretchFactor);
        return;
    }

    Drawing = true;
    getCanvas()->MoveTo(X , Y);
    Origin = Point(X, Y);
    MovePt = Origin;

    //For selection
	mTopLeftSelCorner = Mouse->CursorPos;
	mTopLeftSelCorner = this->Image1->ScreenToClient(mTopLeftSelCorner);

	//Convert to world image coords (minus offset)
    mTopLeftSelCorner = controlToImage(mTopLeftSelCorner, mScaleE->getValue(), stretchFactor);
}

//---------------------------------------------------------------------------
void __fastcall TRenderProjectFrame::Image1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{

	if(Drawing)
  	{
		DrawShape(Origin, MovePt, pmNotXor);
		MovePt = Point(X, Y);
		DrawShape(Origin, MovePt, pmNotXor);
  	}

	TPoint p = this->Image1->ScreenToClient(Mouse->CursorPos);
    double stretchF = getImageStretchFactor();
	XE->Caption = IntToStr((int) (p.X * stretchF) + XCoordE->getValue()) ;
	YE->Caption = IntToStr((int) (p.Y * stretchF) + YCoordE->getValue());
//    ImageWidthL->Caption = IntToStr((int) Image1->Width);
//    ImageHeightL->Caption = IntToStr((int) Image1->Height);

	//Convert to world image coords (minus offset)
    double stretchFactor = getImageStretchFactor();
    if(stretchFactor)
    {
	    p = controlToImage(p, mScaleE->getValue(), stretchFactor);
//	  	mX->setValue(p.X);
//		mY->setValue(p.Y);
    }

	if(GetAsyncKeyState(VK_MBUTTON) < 0)
    {
    	//Move the picture
//        Image1->Top = Image1->Top + 1;
    }
}


void __fastcall TRenderProjectFrame::Image1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
    double stretchFactor = getImageStretchFactor();
	if(Button == TMouseButton::mbMiddle)
    {
	  	Screen->Cursor = crDefault;
    	TPoint p2;
		p2 = Mouse->CursorPos;
		p2 = this->Image1->ScreenToClient(p2);
	    p2 = controlToImage(p2, mScaleE->getValue(), stretchFactor);

		//Convert to world image coords (minus offset)
		XCoordE->setValue(XCoordE->getValue() + (mTopLeftSelCorner.X - p2.X));
		YCoordE->setValue(YCoordE->getValue() + (mTopLeftSelCorner.Y - p2.Y));

		mCurrentROI = RegionOfInterest(XCoordE->getValue(), YCoordE->getValue(), Width->getValue(), Height->getValue(), mScaleE->getValue());
       	ClickZ(Sender);
    }

	if(!Drawing || (Button == TMouseButton::mbRight))
    {
    	return;
    }

	Drawing = false;

    //For selection
	mBottomRightSelCorner = this->Image1->ScreenToClient(Mouse->CursorPos);

	//Convert to world image coords (minus offset)
    mBottomRightSelCorner = controlToImage(mBottomRightSelCorner, mScaleE->getValue(), stretchFactor);

	//Check if selection indicate a 'reset'
	if(mBottomRightSelCorner.X - mTopLeftSelCorner.X <= 0 || mBottomRightSelCorner.Y - mTopLeftSelCorner.Y <= 0)
    {
    	ResetButtonClick(NULL);
		return;
    }

	mCurrentROI = RegionOfInterest(	XCoordE->getValue() + mTopLeftSelCorner.X,
    				 				YCoordE->getValue() + mTopLeftSelCorner.Y,
                                    mBottomRightSelCorner.X - mTopLeftSelCorner.X,
                                    mBottomRightSelCorner.Y - mTopLeftSelCorner.Y,
                                    mScaleE->getValue());
//	XCoordE->setValue(XCoordE->getValue() + mTopLeftSelCorner.X);
//	YCoordE->setValue(YCoordE->getValue() + mTopLeftSelCorner.Y);
//    Width->setValue(mBottomRightSelCorner.X - mTopLeftSelCorner.X);
//    Height->setValue(mBottomRightSelCorner.Y - mTopLeftSelCorner.Y);

//	mCurrentROI = RegionOfInterest(XCoordE->getValue(), YCoordE->getValue(), Width->getValue(), Height->getValue());
    updateScale();
	roiChanged();

    updateROIs();
	ClickZ(NULL);
    checkCache();
}

//---------------------------------------------------------------------------
double TRenderProjectFrame::getImageStretchFactor()
{
	if((mScaleE->getValue() * Height->getValue() * Width->getValue()) == 0)
    {
    	Log(lError) << "Tried to divide by zero!";
    	return 1;
    }

    if(Image1->Height < Image1->Width)
    {
    	return Image1->Height / (mScaleE->getValue() * Height->getValue());
    }
    else
    {
		return Image1->Width / (mScaleE->getValue() * Width->getValue());
    }
}

//---------------------------------------------------------------------------
TCanvas* TRenderProjectFrame::getCanvas()
{
	return PaintBox1->Canvas;
}

//---------------------------------------------------------------------------
void TRenderProjectFrame::DrawShape(TPoint TopLeft, TPoint BottomRight, TPenMode AMode)
{
  	getCanvas()->Pen->Mode = AMode;
	getCanvas()->Rectangle(TopLeft.x, TopLeft.y, BottomRight.x, BottomRight.y);
}

//---------------------------------------------------------------------------
void __fastcall TRenderProjectFrame::IntensityKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if(Key != VK_RETURN)
    {
    	return;
    }
    int minInt = MinIntensityE->getValue();
    int maxInt = MaxIntensityE->getValue();
    if(mZs->ItemIndex == -1)
    {
        return;
    }

    int z = toInt(stdstr(mZs->Items->Strings[mZs->ItemIndex]));
    ClickZ(NULL);
}


//---------------------------------------------------------------------------
void __fastcall TRenderProjectFrame::FrameMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
	if(Drawing)
  	{
		DrawShape(Origin, MovePt, pmNotXor);
		MovePt = Point(X, Y);
		DrawShape(Origin, MovePt, pmNotXor);
  	}

	Image1MouseMove(Sender, Shift, X, Y);
}


void __fastcall TRenderProjectFrame::ROIKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if(Key == VK_RETURN)
    {
        mCurrentROI = RegionOfInterest(XCoordE->getValue(), YCoordE->getValue(), Width->getValue(), Height->getValue(), mScaleE->getValue());
		ClickZ(Sender);
    }
}
//---------------------------------------------------------------------------

