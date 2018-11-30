#include <vcl.h>
#pragma hdrstop
#include "TRenderProjectFrame.h"
#include "dslVCLUtils.h"
#include "atRenderServiceParameters.h"
#include "dslLogger.h"
#include "dslFileUtils.h"
#include <gdiplus.h>
#include "Poco/Path.h"
#include "boost/filesystem.hpp"
#include "TImageForm.h"
#include "atRenderLayer.h"
#include "TCreateLocalVolumesForm.h"
#include "atVCLUtils2.h"
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
using namespace Poco;

int rpFrameNr(0);

TPoint controlToImage(const TPoint& p, double scale, double stretchFactor);

//---------------------------------------------------------------------------
__fastcall TRenderProjectFrame::TRenderProjectFrame(ATExplorer& e, RenderProject& rp, TComponent* Owner)
	: TFrame(Owner),
    mRP(rp),
    mRC(rp, IdHTTP1, e.DefaultRenderService),
    mRenderEnabled(false),
   	mCurrentROI(mRP.getCurrentRegionOfInterestReference()),
    mIsDrawing(false),
    mIMPath(e.getImageMagickPath()),
    mImageGrid(Image1, PaintBox1->Canvas),
    mCreateVolumesForm(NULL)
{
    mRC.assignOnImageCallback(onImage);
    mRC.setLocalCacheFolder(rp.getLocalCacheFolder());
    this->Name = string("RPFrame_" +  dsl::toString(rpFrameNr++)).c_str();
    populate();
    mCurrentROI.assignOnChangeCallback(onROIChanged);
}

void TRenderProjectFrame::populate()
{
    int secsWidth(0);
    for(int i = 0; i < HeaderControl1->Sections->Count; i++)
    {
		secsWidth += HeaderControl1->Sections->Items[i]->Width;
    }

    TPoint p1(HeaderControl1->Left, HeaderControl1->Top);
	TPoint p2 = HeaderControl1->ClientToScreen(p1);
	mZoomFactor->Left = p1.X + secsWidth;
	mZoomFactor->Top = p1.Y;
    mZoomFactor->Parent = HeaderControl1;

    OwnerE->setValue(mRP.getProjectOwner());
    ProjectE->setValue(mRP.getRenderProjectName());

	OutputDataRootFolderE->setValue(mRP.getLocalCacheFolder());
    //Min and max intensity
    MinIntensityE->setReference(mRP.getMinIntensity());
    MaxIntensityE->setReference(mRP.getMaxIntensity());

    //Get stacks for project
    StringList stacks = mRC.getStacksForProject(mRP.getProjectOwner(), mRP.getRenderProjectName());
    if(stacks.size())
    {
		StackCB->ItemIndex = populateDropDown(stacks, StackCB, mRP.getSelectedStackName());
   		StackCBChange(NULL);

        //Check selected channel
       	string ch = mRP.getSelectedChannelName();
        if(checkItem(ChannelsCB, ch, true))
        {
        	mZs->ItemIndex = mZs->Items->IndexOf(dsl::toString(mRP.getSelectedSection()).c_str());
	        //Setup ROI
			roiChanged();
        	ClickZ(NULL);
        }
    }
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
    //Todo reimplement this, to preserve any selected items, as clear remove any selected ones
    OtherCB->Clear();
    StacksCB->Clear();
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

    string stackName(stdstr(StackCB->Text));
    mRC.setSelectedStackName(stackName);
   	getValidZsForStack();

    //Populate channels
    StringList chs = mRC.getChannelsInStack(stackName);
    populateCheckListBox(chs, ChannelsCB);
	enableDisableGroupBox(imageParasGB, true);
	enableDisableGroupBox(Zs_GB, true);
	mRenderEnabled = true;
}

void __fastcall TRenderProjectFrame::getValidZsForStack()
{
	//Fetch valid zs for current project
	mRP.setSelectedStackName(stdstr(StackCB->Text));

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
    mRP.setSelectedSection(z);

    //Fetch data using URL
	mRC.init("jpeg-image", z, mScaleE->getValue(), MinIntensityE->getValue(), MaxIntensityE->getValue());

    if(VisualsPC->Pages[VisualsPC->TabIndex] == TabSheet2)
    {
		this->Image1->Cursor = crHourGlass;
        StringList paras;
        paras.append(string("&maxTileSpecsToRender=150"));

    	//Image pops up in onImage callback
	    mRC.getImageInThread(z, paras);
    }
    else
    {
//		OpenInNDVIZBtnClick(NULL);
    }

    URLE->setValue(createNDVIZURL());
    checkCache();
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
    catch (const EIdHTTPProtocolException& e)
    {
        Log(lError) << "There was an exception: " << stdstr(e.Message);
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

    mIsDrawing = true;
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
	if(mIsDrawing)
  	{
		DrawShape(Origin, MovePt, pmNotXor);
		MovePt = Point(X, Y);
		DrawShape(Origin, MovePt, pmNotXor);
  	}

	TPoint p = this->Image1->ScreenToClient(Mouse->CursorPos);
    double stretchF = getImageStretchFactor();
	XE->Caption = IntToStr((int) (p.X * stretchF) + XCoordE->getValue()) ;
	YE->Caption = IntToStr((int) (p.Y * stretchF) + YCoordE->getValue());

	//Convert to world image coords (minus offset)
    double stretchFactor = getImageStretchFactor();
    if(stretchFactor)
    {
	    p = controlToImage(p, mScaleE->getValue(), stretchFactor);
    }

	if(GetAsyncKeyState(VK_MBUTTON) < 0)
    {
    	//Move the picture
	//        Image1->Top = Image1->Top + 1;
    }
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
void __fastcall TRenderProjectFrame::openInChromeClick(TObject *Sender)
{
    string url = URLE->getValue();
	ShellExecuteA(0,0, "chrome.exe", url.c_str(), 0, SW_SHOWMAXIMIZED);
}

string TRenderProjectFrame::createNDVIZURL()
{
    const RenderServiceParameters* rs = mRC.getRenderServiceParameters();

    string baseURL = "http://" + rs->getHost();
	string URL(baseURL + ":8001/#!{'layers':{'STACK':{'type':'image'_'source':'render://" + baseURL + "/OWNER/PROJECT/STACK'_'max':MAX_INTENSITY}}_'navigation':{'pose':{'position':{'voxelSize':[1_1_1]_'voxelCoordinates':[X_CENTER_Y_CENTER_Z_VALUE]}}_'zoomFactor':ZOOM_FACTOR}}");

	//http://localhost:8001/#!{'layers':{'TESTAcquisition_GFP':{'type':'image'_'source':'render://http://localhost/Testing/Test/TESTAcquisition_GFP'_'max':0.15259}}_'navigation':{'pose':{'position':{'voxelSize':[1_1_1]_'voxelCoordinates':[3576_5709_403]}}_'zoomFactor':1.834862}}

    double xCenter = XCoordE->getValue() + Width->getValue()/2.;
	double yCenter = YCoordE->getValue() + Height->getValue()/2.;
    URL = replaceSubstring("STACK", 	        stdstr(StackCB->Text), 	                                URL);
    URL = replaceSubstring("OWNER", 	        stdstr(OwnerE->Text), 	                                URL);
    URL = replaceSubstring("PROJECT", 	        stdstr(ProjectE->Text), 	                                URL);
    URL = replaceSubstring("MAX_INTENSITY", 	dsl::toString(2.0 * (MaxIntensityE->getValue()/65535.0)), 	URL);
    URL = replaceSubstring("X_CENTER", 			dsl::toString(xCenter), 					                URL);
    URL = replaceSubstring("Y_CENTER", 			dsl::toString(yCenter), 					                URL);
    URL = replaceSubstring("Z_VALUE", 			dsl::toString(getCurrentZ()), 	 			                URL);
    URL = replaceSubstring("ZOOM_FACTOR", 		dsl::toString(0.5*(1.0/mScaleE->getValue())), 	 			URL);
    Log(lDebug5) <<"NDVIZ url: "<< URL;
	return URL;
}

void __fastcall TRenderProjectFrame::FetchSelectedZsBtnClick(TObject *Sender)
{
    TButton* b = dynamic_cast<TButton*>(Sender);
    if(b == FetchSelectedZsBtn)
    {
        if(mCreateCacheThread.isRunning())
        {
            mCreateCacheThread.stop();
        }
        else
        {
		    const RenderServiceParameters* rs = mRC.getRenderServiceParameters();
            int z = toInt(stdstr(mZs->Items->Strings[0]));
            RenderClient rc(mRP, IdHTTP1, rs, mRP.getLocalCacheFolder());
            rc.init("jpeg-image", z, mScaleE->getValue(), MinIntensityE->getValue(), MaxIntensityE->getValue());

            //Create image URLs
            StringList urls;
            for(int i = 0; i < mZs->Count; i++)
            {
                int	z = toInt(stdstr(mZs->Items->Strings[i]));
                urls.append(rc.getURLForZ(z));
            }

    	    StringList paras;
	        paras.append(string("&maxTileSpecsToRender=150"));// + 150)stdstr(maxTileSpecsToRenderE->Text));
            mCreateCacheThread.setup(urls, mRP.getLocalCacheFolder());
            mCreateCacheThread.addParameters(paras);
            mCreateCacheThread.setChannel(mRP.getSelectedChannelName());
            mCreateCacheThread.start();
            CreateCacheTimer->Enabled = true;
        }
    }
    else if(b == ClearCacheBtn)
    {
        //Clear cache for the current owner/project/stack
        Path p(mRP.getLocalCacheFolder());

        p.append(joinPath(mRP.getProjectOwner(), mRP.getRenderProjectName()));
        p.append(mRP.getSelectedStackName());

        Log(lInfo) << "Deleting local cache for stack: " << p.toString();
        boost::filesystem::remove_all(p.toString());
        checkCache();
    }
}

//---------------------------------------------------------------------------
void __fastcall TRenderProjectFrame::CreateTiffStackExecute(TObject *Sender)
{
    Process& IMConvert = mAProcess;
    string convertExe(joinPath(mIMPath, "convert.exe"));

    if(!fileExists(convertExe))
    {
        stringstream msg;
        msg << "Image magicks 'convert.exe' was not found in the path:\n";
        msg << getFilePath(convertExe) << endl << endl;
        msg << "Make sure you have a proper installation of Image Magick";
        MessageDlg(msg.str().c_str(), mtError, TMsgDlgButtons() << mbOK, 0);
        return;
    }

    IMConvert.setExecutable(convertExe);
    IMConvert.setWorkingDirectory(mRC.getImageLocalCachePath());

    //Extract selected filenames from checked z's
    StringList sections = getCheckedItems(mZs);

    //Creat output filename
    string stackFName("stack_" + getUUID());

    //Create commandline for imagemagicks convert program
    stringstream cmdLine;
    for(int i = 0; i < sections.count(); i++)
    {
        int z(toInt(sections[i]));
        string fName(getFileNameNoPath(mRC.getImageLocalCachePathAndFileNameForZ(z, mRP.getSelectedChannelName()) ));
        cmdLine << fName <<" ";
    }

	cmdLine << stackFName << ".tif";

    Log(lInfo) << "Running convert on " << cmdLine.str();

	IMConvert.setup(cmdLine.str(), mhCatchMessages);
    IMConvert.assignCallbacks(NULL, NULL, onIMProcessFinished);
    IMConvert.assignOpaqueData(mZs, nullptr);
    IMConvert.start(true);
}

//---------------------------------------------------------------------------
void __fastcall TRenderProjectFrame::CreateMIPAExecute(TObject *Sender)
{
    string cvt(joinPath(mIMPath, "convert.exe"));
    Process& IMConvert = mAProcess;
    IMConvert.reset();
    IMConvert.setExecutable(cvt);
    IMConvert.setWorkingDirectory(mRC.getImageLocalCachePath());

    //Find all stacks for current ROI
    StringList stackFiles(getFilesInFolder(mRC.getImageLocalCachePath(), "stack_", "tif", false));

    //Create MIP's for current stack file

    string* temp = (string*) StacksCB->Items->Objects[StacksCB->ItemIndex];
    if(!temp)
    {
        Log(lError) << "Failed to extract string item";
        return;
    }

    string currentStack(*temp);
    string* mipFName = new string(getFileNameNoExtension(currentStack));

    *mipFName = "mip_" + *mipFName + ".tif";
    *mipFName = replaceSubstring("stack_", "", *mipFName);
    stringstream cmdLine;
    cmdLine << cvt <<" " << currentStack << " -monitor -evaluate-sequence max "<<*mipFName;
    Log(lInfo) << "Running convert on " << cmdLine.str();

    IMConvert.setup(cmdLine.str(), mhCatchMessages);
    IMConvert.assignCallbacks(NULL, NULL, onIMProcessFinished);

    *mipFName = joinPath(getFilePath(currentStack), *mipFName);
    IMConvert.assignOpaqueData(StacksCB, (void*) mipFName);
    IMConvert.start(true);
}

//---------------------------------------------------------------------------
void __fastcall TRenderProjectFrame::CheckBoxClick(TObject *Sender)
{
    //Open mip
    TCheckListBox* lb = dynamic_cast<TCheckListBox*>(Sender);
    if(lb == StacksCB && StacksCB->ItemIndex != -1)
    {
        string* temp = (string*) StacksCB->Items->Objects[StacksCB->ItemIndex];
        if(!temp)
        {
            Log(lError) << "Failed to extract string item";
            return;
        }


        string currentStack(getFileNameNoPathNoExtension(*temp));
		currentStack = replaceSubstring("stack_", "", currentStack);

        //Populate mips for current stack
        OtherCB->Clear();
        StringList mipFiles(getFilesInFolder(mRC.getImageLocalCachePath(), "tif", false));
        for(int i = 0; i < mipFiles.count(); i++)
        {
            if(startsWith("mip_", mipFiles[i]))
            {
                //Setup something robust here later on
                string* item = new string(joinPath(mRC.getImageLocalCachePath(), mipFiles[i]));
                if(item && contains(currentStack, *item))
                {
                    stringstream itemCaption;
    	            itemCaption << "MIP_" << i + 1;
	                OtherCB->AddItem(vclstr(itemCaption.str()), (TObject*) item);
                }
            }
        }
    }
    else if(lb == OtherCB)
    {
    }
}

void TRenderProjectFrame::OpenImageForm(string fName)
{
    struct TLocalArgs
    {
        string fName;
        void __fastcall sync()
        {
            TImageForm* iForm (new TImageForm("", "", NULL));
            iForm->load(fName);
            iForm->Show();
        }
    };

    TLocalArgs Args;
    Args.fName = fName;
    TThread::Synchronize(NULL, &Args.sync);
}

void TRenderProjectFrame::onIMProcessFinished(void* arg1, void* arg2)
{
    Log(lInfo) << "Process Finished";

    if(arg1 == (void*) StacksCB)
    {
        int itemIndx = StacksCB->ItemIndex;
	    checkCache();
        StacksCB->ItemIndex = itemIndx;
        StacksCB->OnClick(StacksCB);

        //Open MIP window
        if(arg2)
        {
        	string& fName = *((string*) arg2);
            if(fileExists(fName))
            {
                OpenImageForm(fName);
                delete &fName;
            }
        }
    }
    else if(arg1 == (void*) mZs)
    {
        int itemIndx = StacksCB->ItemIndex;
	    checkCache();
        StacksCB->ItemIndex = itemIndx;
    }
}

//---------------------------------------------------------------------------
void __fastcall TRenderProjectFrame::ROI_CBClick(TObject *Sender)
{
    //Switch ROI
    if(ROI_CB->ItemIndex != -1)
    {
	    RegionOfInterest roi = RegionOfInterest(stdstr(ROI_CB->Items->Strings[ROI_CB->ItemIndex]), mCurrentROI.getScale());
        RenderLayer rl(mRC.getProject(), roi, mRC.getCacheRoot());

        mCurrentROI = roi;
        mCurrentROI.setScale(rl.getLowestScaleInCache());
        mScaleE->setValue(mCurrentROI.getScale());
		ClickZ(Sender);
    }
}

string getFilePathFromSelectedCB(TCheckListBox* b)
{
    string fName("");
    if(b->ItemIndex != -1)
    {
    	string* s = (string*) b->Items->Objects[b->ItemIndex];
        if(s)
        {
            fName = *s;
        }
    }

    return fName;
}
//---------------------------------------------------------------------------
void __fastcall TRenderProjectFrame::OpenInExplorerAExecute(TObject *Sender)
{
    //Check who sender is

    TAction* a = dynamic_cast<TAction*>(Sender);
    if(!a)
    {
        return;
    }

    string fName("");

    if(a->ActionComponent == OpenSectionInExplorer)
    {
        //Get section file from z's
        if(mZs->ItemIndex != -1)
        {
            fName = mRC.getImageLocalCachePathAndFileName();
        }
    }
    else if(a->ActionComponent == OpenStackInExplorer)
    {
        fName = getFilePathFromSelectedCB(StacksCB);
	}
    else if(a->ActionComponent == OpenMIPInExplorer)
    {
        fName = getFilePathFromSelectedCB(OtherCB);
    }
    else if(a->ActionComponent == OpenROIInExplorer)
    {
        fName = joinPath(getFilePath(mRC.getImageLocalCachePathAndFileNameForZ(0, mRP.getSelectedChannelName())), getFilePathFromSelectedCB(ROI_CB));
    }

    if(fName.size())
    {
        ITEMIDLIST *pidl = ILCreateFromPath(fName.c_str());
        if(pidl)
        {
            SHOpenFolderAndSelectItems(pidl,0,0,0);
            ILFree(pidl);
        }
    }
}

void TRenderProjectFrame::zoom(int zoomFactor, bool out)
{
    if(out)
    {
		zoomFactor *= (-1.0);
    }
	//Modify bounding box with x%
    mCurrentROI = RegionOfInterest(XCoordE->getValue(), YCoordE->getValue(), Width->getValue(), Height->getValue());
    mCurrentROI.zoom(zoomFactor);

	XCoordE->setValue(mCurrentROI.getX1());
    YCoordE->setValue(mCurrentROI.getY1());
    Width->setValue( mCurrentROI.getWidth());
    Height->setValue(mCurrentROI.getHeight());

    updateScale();
	ClickZ(NULL);
    checkCache();
}

//---------------------------------------------------------------------------
void __fastcall TRenderProjectFrame::RzSpinButtons1DownLeftClick(TObject *Sender)

{
	CustomImageRotationE->setValue(CustomImageRotationE->getValue() - 0.5);
	double val = CustomImageRotationE->getValue();
	paintRotatedImage(val);

}

//---------------------------------------------------------------------------
void __fastcall TRenderProjectFrame::RzSpinButtons1UpRightClick(TObject *Sender)

{
	CustomImageRotationE->setValue(CustomImageRotationE->getValue() +0.5);
	double val = CustomImageRotationE->getValue();
	paintRotatedImage(val);
}


//---------------------------------------------------------------------------
void __fastcall TRenderProjectFrame::ToggleImageGridAExecute(TObject *Sender)

{
    Log(lDebug5) << "Action Component: " << stdstr(ToggleImageGridA->ActionComponent->Name);

    TMenuItem* ac = dynamic_cast<TMenuItem*>(ToggleImageGridA->ActionComponent);
    if(ac)
    {
        ShowImageGridCB->Checked = !ShowImageGridCB->Checked;
    }
    else
    {
   		PaintBox1Paint(NULL);
    }
}

//---------------------------------------------------------------------------
void __fastcall TRenderProjectFrame::ToggleImageGridAUpdate(TObject *Sender)
{
    if(!mIsDrawing)
    {
        PaintBox1->BringToFront();
		PaintBox1->Invalidate();
    }
}

//---------------------------------------------------------------------------
void __fastcall TRenderProjectFrame::PaintBox1Paint(TObject *Sender)
{
//    if(ShutDownTimer->Enabled)
//    {
//        return;
//    }

    if(ShowImageGridCB->Checked)
    {
        mImageGrid.paint();
    }
}

//---------------------------------------------------------------------------
void __fastcall TRenderProjectFrame::OtherCBDblClick(TObject *Sender)
{
    TCheckListBox* lb = dynamic_cast<TCheckListBox*>(Sender);
    if(lb != OtherCB)
    {
        return;
    }

    //Get item
    TObject* item = lb->Items->Objects[lb->ItemIndex];
    if(item)
    {
        string* fName((string*) item);
        TImageForm* iForm (new TImageForm("", "", this));
        iForm->load(*fName);
        iForm->Show();
    }
}

void __fastcall TRenderProjectFrame::PaintBox1MouseUp(TObject *Sender, TMouseButton Button,
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

	if(!mIsDrawing || (Button == TMouseButton::mbRight))
    {
    	return;
    }

	mIsDrawing = false;

    //For selection
	mBottomRightSelCorner = this->Image1->ScreenToClient(Mouse->CursorPos);

	//Convert to world image coords (minus offset)
    mBottomRightSelCorner = controlToImage(mBottomRightSelCorner, mScaleE->getValue(), stretchFactor);

	//Check if selection indicate a 'reset'
	if(mBottomRightSelCorner.X - mTopLeftSelCorner.X <= 0 || mBottomRightSelCorner.Y - mTopLeftSelCorner.Y <= 0)
    {
//    	resetButtonClick(NULL);
		return;
    }

	mCurrentROI = RegionOfInterest(	XCoordE->getValue() + mTopLeftSelCorner.X,
    				 				YCoordE->getValue() + mTopLeftSelCorner.Y,
                                    mBottomRightSelCorner.X - mTopLeftSelCorner.X,
                                    mBottomRightSelCorner.Y - mTopLeftSelCorner.Y,
                                    mScaleE->getValue());

    updateScale();
	roiChanged();
    updateROIs();
	ClickZ(NULL);
    checkCache();
}

//---------------------------------------------------------------------------
void __fastcall TRenderProjectFrame::CreateCacheTimerTimer(TObject *Sender)
{
	if(mCreateCacheThread.isRunning())
    {
		FetchSelectedZsBtn->Caption = "Stop";
    }
    else
    {
		CreateCacheTimer->Enabled = false;
		FetchSelectedZsBtn->Caption = "Generate";
    }
}

//---------------------------------------------------------------------------
void __fastcall TRenderProjectFrame::Button1Click(TObject *Sender)
{
	updateROIs();
}

//---------------------------------------------------------------------------
void __fastcall TRenderProjectFrame::Button2Click(TObject *Sender)
{
    //Open creat volumes form
	if(!mCreateVolumesForm)
    {
    	mCreateVolumesForm = new TCreateLocalVolumesForm(mRP, mIMPath, this);
    }

    StringList stacks;
    stacks.append(stdstr(StackCB->Text));
    mCreateVolumesForm->populate(mCurrentROI, stacks);
    mCreateVolumesForm->Show();
}

//---------------------------------------------------------------------------
void __fastcall TRenderProjectFrame::BrowseForDataOutputPathBtnClick(TObject *Sender)

{
    TButton* btn = dynamic_cast<TButton*>(Sender);
    if(btn == BrowseForDataOutputPathBtn)
    {
        //Browse for folder
        string res = browseForFolder(OutputDataRootFolderE->getValue());
        if(folderExists(res))
        {
            OutputDataRootFolderE->setValue(res);
            mRP.assignLocalCacheRootFolder(res);
        }
        else
        {
            Log(lWarning) << "Path was not set..!";
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TRenderProjectFrame::OutputDataRootFolderEKeyDown(TObject *Sender,
          WORD &Key, TShiftState Shift)
{
    if(Key == VK_RETURN)
    {
		mRP.assignLocalCacheRootFolder(OutputDataRootFolderE->getValue());
    }
}

TPoint controlToImage(const TPoint& p, double scale, double stretchFactor)
{
	TPoint pt;
    if(scale > 0)
    {
    	pt.X = (p.X / scale) / stretchFactor;
	    pt.Y = (p.Y / scale) / stretchFactor;
    }
	return pt;
}

//---------------------------------------------------------------------------
void __fastcall TRenderProjectFrame::ChannelsCBClick(TObject *Sender)
{
;
}

void __fastcall TRenderProjectFrame::ChannelsCBClickCheck(TObject *Sender)
{
	int indx(-1);
    for(int i = 0; i < ChannelsCB->Count; i++)
    {
    	if(ChannelsCB->Selected[i])
        {
            indx = i;
            break;
        }
    }

    ChannelsCB->CheckAll(cbUnchecked);
    ChannelsCB->Checked[indx] = cbChecked;

    string channel = stdstr(ChannelsCB->Items->Strings[indx]);

    //Render this channel
    mRP.setSelectedChannelName(channel);
    ClickZ(NULL);
}

void __fastcall TRenderProjectFrame::HeaderControl1SectionClick(THeaderControl *HeaderControl,
          THeaderSection *Section)
{
    //
    if(Section->Text == '+')
    {
	    zoom(mZoomFactor->getValue(), false);
    }
    else if(Section->Text == '-')
    {
	    zoom(mZoomFactor->getValue(), true);
    }
}

void __fastcall TRenderProjectFrame::Panel1ContextPopup(TObject *Sender, TPoint &MousePos,
          bool &Handled)
{
    TPoint popupCoord = Panel1->ClientToScreen(MousePos);
    ImagePopup->Popup(popupCoord.X, popupCoord.Y);
    Handled = true;
}

//---------------------------------------------------------------------------
void __fastcall TRenderProjectFrame::TabSheet2ContextPopup(TObject *Sender, TPoint &MousePos,
          bool &Handled)
{
//    ImagePopup->Popup(MousePos.X, MousePos.Y);
//    Handled = true;
}

void __fastcall TRenderProjectFrame::StacksCBClick(TObject *Sender)
{
    //
}

//---------------------------------------------------------------------------
void __fastcall TRenderProjectFrame::Checkrange1Click(TObject *Sender)
{
//
}


void __fastcall TRenderProjectFrame::CheckZs(TObject *Sender)
{
	TMenuItem* item = dynamic_cast<TMenuItem*>(Sender);
    if(item == CheckAll)
    {
		mZs->CheckAll(cbChecked);
    }
    else if(item == UnCheckAll)
    {
		mZs->CheckAll(cbUnchecked);
    }
}


