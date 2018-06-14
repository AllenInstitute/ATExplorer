#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include <vector>
#include "atRenderClient.h"
//#include "dslExeFile.h"
#include "dslMathUtils.h"
#include "dslTMemoLogger.h"
#include "TSelectZsForm.h"
#include "TImageForm.h"
#include "atApplicationSupportFunctions.h"
#include "TOverlayedImage.h"
#include "atVolumeCreatorProject.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTFloatLabeledEdit"
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "dslTIntLabel"
#pragma link "dslTPropertyCheckBox"
#pragma link "dslTIniFileC"
#pragma link "dslTIntegerEdit"
#pragma link "TSSHFrame"
#pragma link "TImageControlsFrame"
#pragma link "TParaConverterFrame"

#pragma link "dslTFloatLabeledEdit"
#pragma link "dslTIniFileC"
#pragma link "dslTIntegerEdit"
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTIntLabel"
#pragma link "dslTPropertyCheckBox"
#pragma link "dslTSTDStringLabeledEdit"
#pragma resource "*.dfm"
TMainForm *MainForm;

using namespace dsl;
using namespace std;
TImage *CurrImage;
extern string gAppDataLocation;
extern string gLogFileName;
extern string gAppName;

//__fastcall      TRegistryForm(const string& regRoot, const string& formName, TComponent* Owner);
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TRegistryForm(gApplicationRegistryRoot, "MainForm", Owner),
    mLogLevel(lAny),
    mLogFileReader(joinPath(gAppDataLocation, gLogFileName), logMsg),
    mBottomPanelHeight(205),
	mCreateCacheThread(),
    mRC(IdHTTP1),
    mRenderEnabled(false),
    mCurrentProject(""),
    mCurrentOwner(""),
    mCurrentStack(""),
    mIsStyleMenuPopulated(false),
	gImageForm(NULL),
    mProjectManager((*ProjectTView)),
    mAppProperties(gAppName, gApplicationRegistryRoot, ""),
    mGeneralProperties(shared_ptr<IniFileProperties>(new IniFileProperties)),
	mServer1Properties(shared_ptr<IniFileProperties>(new IniFileProperties)),
	mServer2Properties(shared_ptr<IniFileProperties>(new IniFileProperties))

{
    setupIniFile();
    setupAndReadIniParameters();
    mCreateCacheThread.setCacheRoot(mImageCacheFolderE->getValue());
  	TMemoLogger::mMemoIsEnabled = true;
	CurrImage = Image1;
    mRC.assignOnImageCallback(onImage);
}

__fastcall TMainForm::~TMainForm()
{
	delete gImageForm;
}

//#define ThrowWandException(wand) \
//{ \
//  char \
//    *description; \
// \
//  ExceptionType \
//    severity; \
// \
//  description=MagickGetException(wand,&severity); \
//  (void) fprintf(stderr,"%s %s %lu %s\n",GetMagickModule(),description); \
//  description=(char *) MagickRelinquishMemory(description); \
//  exit(-1); \
//}
//
void ThrowWandException(MagickWand* wand)
{
  	char *description;
	ExceptionType severity;

  	description = MagickGetException(wand, &severity);
    Log(lInfo) << "ImageMagic encountered a problem: " <<description <<" in module "<<GetMagickModule();
  	description = (char *) MagickRelinquishMemory(description);
}

//This is called from a thread and need to be synchronized with the UI main thread
void __fastcall TMainForm::onImage()
{
	TMemoryStream* imageMem = mRC.getImageMemory();
    if(!imageMem)
    {
    	return;
    }

    if(!fileExists(mRC.getImageLocalPathAndFileName()))
    {
        Log(lInfo) << "File does not exist: " <<mRC.getImageLocalPathAndFileName();
        return;
    }

    string pic = mRC.getImageLocalPathAndFileName().c_str();

    if(	IMContrastControl->Checked  ||
    	FlipImageRightCB->Checked   ||
        FlipImageLeftCB->Checked    ||
        ColorRG->ItemIndex > 0		||
		CustomRotationE->getValue() != 0
        )
    {
        //Read imageMagick image from file
        MagickWand* image_wand;
        MagickWandGenesis();
        image_wand = NewMagickWand();
        MagickBooleanType status = MagickReadImage(image_wand, pic.c_str());

        if (status == MagickFalse)
        {
            ThrowWandException(image_wand);
        }

        if(IMContrastControl->Checked)
        {
            applyContrastControl(image_wand);
        }

        if(FlipImageRightCB->Checked)
        {
            flipImage(image_wand, 90);
        }

        if(FlipImageLeftCB->Checked)
        {
            flipImage(image_wand, -90);
        }

        if(CustomRotationE->getValue() != 0)
        {
		    flipImage(image_wand, CustomRotationE->getValue());
        }

        if(ColorRG->ItemIndex > 0)
        {
            colorImage(image_wand, ColorRG->ItemIndex);
        }

        string newFName(createProcessedImageFileName(pic));


        /*    Write the image then destroy it.    */
        string procImageFName(createProcessedImageFileName(pic));
        status = MagickWriteImages(image_wand, procImageFName.c_str(), MagickTrue);
        if (status == MagickFalse)
        {
            ThrowWandException(image_wand);
        }

        // Release Wand handle
        DestroyMagickWand(image_wand);
        Image1->Picture->Graphic->LoadFromFile(newFName.c_str());
        mCurrentImageFile = newFName;
    }
    else
    {
        try
        {
            //Create a temporary stream
            unique_ptr<TMemoryStream> stream = unique_ptr<TMemoryStream>(new TMemoryStream());

            stream->LoadFromFile(pic.c_str());
            if(stream->Size)
            {
            	stream->Position = 0;
    	        Image1->Picture->Graphic->LoadFromStream(stream.get());
            }
        }
        catch(...)
        {
            Log(lError) << "Failed to load image: "<<pic;
            return;
        }
        mCurrentImageFile = pic;
    }

    if(gImageForm && gImageForm->Visible)
    {
    	gImageForm->load(mCurrentImageFile);
    }

    Image1->Repaint();
    Log(lInfo) << "WxH = " <<Image1->Picture->Width << "x" << Image1->Picture->Height;
    this->Image1->Cursor = crDefault;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ClickZ(TObject *Sender)
{
	int ii = mZs->ItemIndex;
    if(ii == -1)
    {
    	return;
    }

    int z = toInt(stdstr(mZs->Items->Strings[ii]));

    //Fetch data using URL
	mRC.setLocalCacheFolder(mImageCacheFolderE->getValue());
	mRC.init(mCurrentOwner.getValue(), mCurrentProject.getValue(), mCurrentStack.getValue(), "jpeg-image", z, mCurrentRB, mScaleE->getValue(), MinIntensity->getValue(), MaxIntensity->getValue());

    if(PageControl2->Pages[PageControl2->TabIndex] == TabSheet2)
    {
		this->Image1->Cursor = crHourGlass;
    	//Image pops up in onImage callback
	    mRC.getImageInThread(z);
    }
    else
    {
		OpenInNDVIZBtnClick(OpenInNDVIZBtn);
    }

    if(Sender != NULL)
    {
		mROIHistory.clear();
    	mROIHistory.add(mCurrentRB);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mScaleEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == VK_RETURN)
    {
        mCurrentRB = RenderBox(XCoord->getValue(), YCoord->getValue(), Width->getValue(), Height->getValue(), mScaleE->getValue());
		ClickZ(Sender);
    }
}

//---------------------------------------------------------------------------
double TMainForm::getImageStretchFactor()
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
TCanvas* TMainForm::getCanvas()
{
	return PaintBox1->Canvas;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormMouseDown(TObject *Sender, TMouseButton Button,
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
    	//Open popup
       	Screen->Cursor = crSize;
    	//Open popup
		mTopLeftSelCorner = Mouse->CursorPos;
		mTopLeftSelCorner = this->Image1->ScreenToClient(mTopLeftSelCorner);

		//Convert to world image coords (minus offset)
	    mTopLeftSelCorner = controlToImage(mTopLeftSelCorner, mScaleE->getValue(), stretchFactor);
//        Image1->Align = alNone;
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
void __fastcall TMainForm::Image1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	TPoint p = this->Image1->ScreenToClient(Mouse->CursorPos);
	mXC->setValue(p.X);
	mYC->setValue(p.Y);

	//Convert to world image coords (minus offset)
    double stretchFactor = getImageStretchFactor();
    if(stretchFactor)
    {
	    p = controlToImage(p, mScaleE->getValue(), stretchFactor);
	  	mX->setValue(p.X);
		mY->setValue(p.Y);
    }

	if(GetAsyncKeyState(VK_MBUTTON) < 0)
    {
    	//Move the picture
//        Image1->Top = Image1->Top + 1;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormMouseUp(TObject *Sender, TMouseButton Button,
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
		XCoord->setValue(XCoord->getValue() + (mTopLeftSelCorner.X - p2.X));
		YCoord->setValue(YCoord->getValue() + (mTopLeftSelCorner.Y - p2.Y));

		mCurrentRB = RenderBox(XCoord->getValue(), YCoord->getValue(), Width->getValue(), Height->getValue(), mScaleE->getValue());
       	ClickZ(Sender);
    }

	if(!Drawing ||  (Button == TMouseButton::mbRight))
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
    	resetButtonClick(NULL);
		return;
    }

	XCoord->setValue(XCoord->getValue() + mTopLeftSelCorner.X);
	YCoord->setValue(YCoord->getValue() + mTopLeftSelCorner.Y);

    Width->setValue(mBottomRightSelCorner.X - mTopLeftSelCorner.X);
    Height->setValue(mBottomRightSelCorner.Y - mTopLeftSelCorner.Y);

    updateScale();

    //Add to render history
    mCurrentRB = RenderBox(XCoord->getValue(), YCoord->getValue(), Width->getValue(), Height->getValue(), mScaleE->getValue());
    mROIHistory.insert(mCurrentRB);

    //Undo any flipping
    FlipImageRightCB->Checked = false;
    FlipImageLeftCB->Checked = false;
	ClickZ(NULL);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormMouseMove(TObject *Sender, TShiftState Shift,
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

//---------------------------------------------------------------------------
void __fastcall TMainForm::DrawShape(TPoint TopLeft, TPoint BottomRight, TPenMode AMode)
{
  	getCanvas()->Pen->Mode = AMode;
	getCanvas()->Rectangle(TopLeft.x, TopLeft.y, BottomRight.x, BottomRight.y);
}

int	TMainForm::getCurrentZ()
{
	int ii = mZs->ItemIndex;
    if(ii == -1)
    {
    	return -1;
    }

    return toInt(stdstr(mZs->Items->Strings[ii]));
}

void __fastcall TMainForm::resetButtonClick(TObject *Sender)
{
    //Get saved renderbox for current slice
	try
    {
	    mROIHistory.clear();
	    mScaleE->setValue(0.05 * ScaleConstantE->getValue());
        mCurrentRB = mRC.getBoxForZ(getCurrentZ());
        mCurrentRB.setScale(mScaleE->getValue());
        render(&mCurrentRB);
        mROIHistory.add(mCurrentRB);
    }
    catch(...)
    {}
}

void TMainForm::render(RenderBox* box)
{
	if(box)
    {
        mCurrentRB = *(box);
        XCoord->setValue(mCurrentRB.getX1());
        YCoord->setValue(mCurrentRB.getY1());
        Width->setValue(mCurrentRB.getWidth());
        Height->setValue(mCurrentRB.getHeight());
        mScaleE->setValue(mCurrentRB.getScale());
    }

	ClickZ(NULL);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::historyBtnClick(TObject *Sender)
{
    TButton* b = dynamic_cast<TButton*>(Sender);
    if(b == mHistoryFFW)
    {
        RenderBox* rb = mROIHistory.next();
        if(rb)
        {
            render(rb);
        }
    }
    else if(b == mHistoryBackBtn)
    {
        RenderBox* rb = mROIHistory.previous();
        if(rb)
        {
            render(rb);
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::TraverseZClick(TObject *Sender)
{
	TButton* b = dynamic_cast<TButton*>(Sender);
    if(mZs->ItemIndex > -1 && mZs->ItemIndex < mZs->Count)
    {
    	mZs->Selected[mZs->ItemIndex] = false;
    }
    mZs->Selected[mZs->ItemIndex] = true;
    render();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mFetchSelectedZsBtnClick(TObject *Sender)
{
	if(mCreateCacheThread.isRunning())
    {
		mCreateCacheThread.stop();
    }
    else
    {
        int z = toInt(stdstr(mZs->Items->Strings[0]));
        RenderClient rs(IdHTTP1, mBaseUrlE->getValue(), mCurrentOwner.getValue(), mCurrentProject.getValue(),
            mCurrentStack.getValue(), "jpeg-image", z, mCurrentRB, mScaleE->getValue(), MinIntensity->getValue(), MaxIntensity->getValue(), mImageCacheFolderE->getValue());

        //Create image URLs
        StringList urls;
        for(int i = 0; i < mZs->Count; i++)
        {
            int	z = toInt(stdstr(mZs->Items->Strings[i]));
            urls.append(rs.getURLForZ(z));
        }

        mCreateCacheThread.setup(urls, mImageCacheFolderE->getValue());
        mCreateCacheThread.start();
        CreateCacheTimer->Enabled = true;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mGetValidZsBtnClick(TObject *Sender)
{
	//Fetch valid zs for current project
   	RenderClient rs(IdHTTP1, mBaseUrlE->getValue(), mCurrentOwner.getValue(), mCurrentProject.getValue(),	mCurrentStack.getValue());
    StringList zs = rs.getValidZs();

	Log(lInfo) << "Fetched "<<zs.count()<<" valid z's";

	Zs_GB->Caption = " Z Values (" + IntToStr((int) zs.count()) + ") ";
    //Populate list box
	populateCheckListBox(zs, mZs);
    mZs->CheckAll(cbChecked);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mUpdateZsBtnClick(TObject *Sender)
{
	//Fetch valid zs for current project
   	RenderClient rs(IdHTTP1, mBaseUrlE->getValue(), mCurrentOwner.getValue(), mCurrentProject.getValue(),	mCurrentStack.getValue());
    StringList zs = rs.getZs();

    if(zs.size() > 1)
    {
    	//Populate list boxes
	    Log(lInfo) << "Valid Z's: "<<zs[0];
    	Log(lInfo) << "Missing Z's: "<<zs[1];
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::GetOptimalBoundsBtnClick(TObject *Sender)
{
	RenderClient rs(IdHTTP1, mBaseUrlE->getValue(), mCurrentOwner.getValue(), mCurrentProject.getValue(),	mCurrentStack.getValue());

    vector<int> zs = rs.getValidZs();
    RenderBox box = rs.getOptimalXYBoxForZs(zs);
    Log(lInfo) << "XMin = " << box.getX1();
    Log(lInfo) << "XMax = " << box.getX2();
    Log(lInfo) << "YMin = " << box.getY1();
    Log(lInfo) << "YMax = " << box.getY2();

   	vector<RenderBox> bounds = rs.getBounds();
    for(int i = 0; i < bounds.size(); i++)
    {
	    Log(lInfo) <<bounds[i].getZ()<<","<<bounds[i].getX1()<<","<<bounds[i].getX2()<<","<<bounds[i].getY1()<<","<<bounds[i].getY2();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mZoomBtnClick(TObject *Sender)
{
	TButton* b = dynamic_cast<TButton*>(Sender);

	double zoomFactor = mZoomFactor->getValue();
    if(b == mZoomOutBtn)
    {
		zoomFactor *= (-1.0);
    }

	//Modify bounding box with x%
    mCurrentRB = RenderBox(XCoord->getValue(), YCoord->getValue(), Width->getValue(), Height->getValue());
    mCurrentRB.zoom(zoomFactor);

	XCoord->setValue(mCurrentRB.getX1());
    YCoord->setValue(mCurrentRB.getY1());
    Width->setValue( mCurrentRB.getWidth());
    Height->setValue(mCurrentRB.getHeight());

    updateScale();
	ClickZ(Sender);
}

//---------------------------------------------------------------------------
void TMainForm::updateScale()
{
    mCurrentRB = RenderBox(XCoord->getValue(), YCoord->getValue(), Width->getValue(), Height->getValue());

    //Scale the scaling
    double scale  = (double) Image1->Height / (double) mCurrentRB.getHeight();
    Log(lInfo) << "Scaling is: " << scale;
	if(scale < 0.005)
    {
    	scale = 0.009;
    }
    else if(scale > 1.0)
    {
    	scale = 1.0;
    }
	mScaleE->setValue(scale);
}

//--------------------------------------------------------------------------
void __fastcall TMainForm::OwnerCBChange(TObject *Sender)
{
	//Update Projects CB
    //Get selected owner
    if(OwnerCB->ItemIndex == -1)
    {
		return;
    }

    //Disable uninitialized sections of the UI
	enableDisableGroupBox(imageParasGB, false);
	enableDisableGroupBox(Zs_GB, false);
    enableDisableGroupBox(StackGenerationGB, false);
   	mRenderEnabled = false;
	StackCB->Clear();

    string owner = stdstr(OwnerCB->Items->Strings[OwnerCB->ItemIndex]);
    mCurrentOwner.setValue(owner);

    //Populate projects
    StringList p = mRC.getProjectsForOwner(mCurrentOwner.getValue());
    if(p.size())
    {
		populateDropDown(p, ProjectCB);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ProjectCBChange(TObject *Sender)
{
	//Update Stacks CB
    //Get selected owner
    if(ProjectCB->ItemIndex == -1)
    {
		return;
    }

    //Disable uninitialized sections of the UI
	enableDisableGroupBox(imageParasGB, false);
	enableDisableGroupBox(Zs_GB, false);
    enableDisableGroupBox(StackGenerationGB, false);
	mRenderEnabled = false;
    string owner = stdstr(OwnerCB->Items->Strings[OwnerCB->ItemIndex]);
    string project = stdstr(ProjectCB->Items->Strings[ProjectCB->ItemIndex]);
    mCurrentProject.setValue(project);

    //Populate stacks
    StringList s = mRC.getStacksForProject(owner, mCurrentProject);
    if(s.size())
    {
		populateDropDown(s, StackCB);
		populateCheckListBox(s, StacksForProjectCB);
    }
}

void __fastcall TMainForm::StackCBChange(TObject *Sender)
{
    if(StackCB->ItemIndex == -1)
    {
		return;
    }

    string stack = stdstr(StackCB->Items->Strings[StackCB->ItemIndex]);
	mCurrentStack.setValue(stack);

	mRC.getProject().setupForStack(mCurrentOwner.getValue(), mCurrentProject.getValue(), mCurrentStack.getValue());

   	mGetValidZsBtnClick(NULL);
//    resetButtonClick(NULL);
	ClickZ(NULL);

    //Update stack generation page
	//User changed stack.. Clear check list box and select current one
    for(int i = 0; i < StacksForProjectCB->Items->Count; i++)
    {
        if(StacksForProjectCB->Items->Strings[i] == StackCB->Text)
        {
	    	StacksForProjectCB->Checked[i] = true;
        }
        else
        {
    		StacksForProjectCB->Checked[i] = false;
        }
    }

    //Disable uninitialized sections of the UI
	enableDisableGroupBox(imageParasGB, true);
	enableDisableGroupBox(Zs_GB, true);
	mRenderEnabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::CreateCacheTimerTimer(TObject *Sender)
{
	if(mCreateCacheThread.isRunning())
    {
		mFetchSelectedZsBtn->Caption = "Stop Cache Creation";
    }
    else
    {
		CreateCacheTimer->Enabled = false;
		mFetchSelectedZsBtn->Caption = "Generate Cache";
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::IntensityKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key != VK_RETURN)
    {
    	return;
    }
    int minInt = MinIntensity->getValue();
    int maxInt = MaxIntensity->getValue();
    int ii = mZs->ItemIndex;
    if(ii == -1)
    {
        return;
    }

    int z = toInt(stdstr(mZs->Items->Strings[ii]));

    //Fetch data using URL
    mRC.setLocalCacheFolder(mImageCacheFolderE->getValue());
    mRC.init(mCurrentOwner.getValue(), mCurrentProject.getValue(), mCurrentStack.getValue(), "jpeg-image", z, mCurrentRB, mScaleE->getValue(), minInt, maxInt);

    //First check if we already is having this data
    try
    {
        try
        {
            Log(lDebug) << "Loading z = "<<z;
            Log(lDebug) << "URL = "<< mRC.getURL();

            TMemoryStream* imageMem = mRC.reloadImage(z);
            if(imageMem)
            {
                Image1->Picture->Graphic->LoadFromStream(imageMem);
                Image1->Invalidate();
            }

            Log(lInfo) << "WxH = " <<Image1->Picture->Width << "x" << Image1->Picture->Height;
        }
        __except(EXCEPTION_EXECUTE_HANDLER)
        {
            Log(lError) << "There was a memory problem..";
        }
    }
    __finally
    {
        mRC.clearImageMemory();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::CheckAll1Click(TObject *Sender)
{
	TCheckListBox* lb = dynamic_cast<TCheckListBox*>(ZsPopUpMenu->PopupComponent);

    if(!lb)
    {
    	return;
    }

    for(int i = 0; i < lb->Count; i++)
    {
    	lb->Checked[i] = true;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::UncheckAll1Click(TObject *Sender)
{
	TCheckListBox* lb = dynamic_cast<TCheckListBox*>(ZsPopUpMenu->PopupComponent);

    if(!lb)
    {
    	return;
    }

    for(int i = 0; i < lb->Count; i++)
    {
    	lb->Checked[i] = false;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::Checkrange1Click(TObject *Sender)
{
	TSelectZsForm* sz = new TSelectZsForm(this);
    sz->populate(mZs);
    int mr = sz->ShowModal();

    if(mr == mrOk)
    {
    	//Check/Uncheck items
    	//First uncheck all
        for(int i = 0; i < mZs->Count; i++)
	    {
    		mZs->Checked[i] = false;
	    }

		StringList us(sz->getSelected());

        //Then select the selected ones
        for(int i = 0; i < mZs->Count; i++)
        {
        	string val(stdstr(mZs->Items->Strings[i]));
        	if(us.contains(val))
            {
				mZs->Checked[i] = true;
            }
        }
    }
    delete sz;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::StackFilterCBClick(TObject *Sender)
{
	StacksForProjectCB->Clear();
    StringList s = mRC.getStacksForProject(mCurrentOwner, mCurrentProject);

	if(CustomFilterCB->Checked)
    {
        for(int i = 0; i < s.count(); i++)
        {
            if(contains(stdstr(CustomFilterE->Text), s[i]))
            {
                StacksForProjectCB->AddItem(s[i].c_str(), NULL);
            }
        }
    }
    else
    {
        for(int i = 0; i < s.count(); i++)
        {
        	StacksForProjectCB->AddItem(s[i].c_str(), NULL);
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
    if(mIsStyleMenuPopulated == false)
    {
        populateStyleMenu(ThemesMenu, ThemesMenuClick);
        mIsStyleMenuPopulated = true;
	}
}

//---------------------------------------------------------------------------
string createProcessedImageFileName(const string& pic)
{
	string fName(getFileNameNoExtension(pic));
	string fPath(getFilePath(pic));
    string fExt(getFileExtension(pic));
    string newName(joinPath(fPath, fName + "_processed") + "." + fExt);
    return newName;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ClickImageProcCB(TObject *Sender)
{
	ClickZ(NULL);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ColorRGClick(TObject *Sender)
{
	if(ColorRG->ItemIndex != -1)
    {
		ClickZ(NULL);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::CustomFilterEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key != VK_RETURN)
    {
    	return;
    }

    StacksForProjectCB->Clear();
    StringList s = mRC.getStacksForProject(mCurrentOwner, mCurrentProject);
    if(CustomFilterCB->Checked)
    {
        for(int i = 0; i < s.count(); i++)
        {
            if(contains(stdstr(CustomFilterE->Text), s[i]))
            {
                StacksForProjectCB->AddItem(s[i].c_str(), NULL);
            }
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenaClone1Click(TObject *Sender)
{
	if(!gImageForm)
    {
    	gImageForm = new TImageForm(gApplicationRegistryRoot, "", this);
    }

	gImageForm->Show();
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::AddOverlayedImage1Click(TObject *Sender)
{
	TOverlayedImage* f = new TOverlayedImage(NULL);
    f->Show();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::CreateTIFFStackCBClick(TObject *Sender)
{
	DeleteTempTiffsCB->Enabled = CreateTIFFStackCB->Checked;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ProjectTViewEditing(TObject *Sender, TTreeNode *Node,
          bool &AllowEdit)
{
	AllowEdit = true;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ProjectTViewEdited(TObject *Sender, TTreeNode *Node,
          UnicodeString &S)
{
	//Update underlying object with new valuse..
    VolumeCreatorProject* vcp = (VolumeCreatorProject*) Node->Data;
    if(vcp)
    {
    	vcp->setProjectName(stdstr(S));
        vcp->setModified();
		SaveProjectA->Update();
    }
}

void __fastcall TMainForm::EditViewNodeExecute(TObject *Sender)
{
	TTreeNode* item = ProjectTView->Selected;
    if(item)
    {
    	item->EditText();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ProjectTViewClick(TObject *Sender)
{
	//Get current node from the treeview
	TTreeNode* item = ProjectTView->Selected;
	mProjectManager.selectItem(item);

}

//---------------------------------------------------------------------------
void __fastcall TMainForm::CustomRotationEKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if(Key == VK_RETURN)
    {
		//Do a rotation
		ClickZ(NULL);
    }
}


void __fastcall TMainForm::TestRenderServiceBtnClick(TObject *Sender)
{
    mRC.setBaseURL(mBaseUrlE->getValue());
    mRC.getProject().setupForStack(mCurrentOwner.getValue(), mCurrentProject.getValue(), mCurrentStack.getValue());

    //Populate owners
    StringList o = mRC.getOwners();
    if(o.size())
    {
		populateDropDown(o, OwnerCB);
    }
}


void __fastcall TMainForm::DcefBrowser1BeforeBrowse(ICefBrowser * const browser,
          ICefFrame * const frame, ICefRequest * const request,
          bool isRedirect, bool &Cancel)
{
    Log(lDebug) << "browsing..";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DcefBrowser1ConsoleMessage(ICefBrowser * const browser,
          const ustring message, const ustring source, int line,
          bool &Cancel)
{
    Log(lDebug) <<"Console Message";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DcefBrowser1StateChange(ICefBrowser * const browser,
          const TBrowserDataChangeKind Kind, const UnicodeString Value)

{
    Log(lDebug) <<"State Change";
}
//---------------------------------------------------------------------------

