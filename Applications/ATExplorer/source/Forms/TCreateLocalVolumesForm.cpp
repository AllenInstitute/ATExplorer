#include <vcl.h>
#pragma hdrstop
#include "TCreateLocalVolumesForm.h"
#include "atRenderServiceParameters.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "TCreateStackThreadFrame.h"
#include "Poco/File.h"
#include "dslFileUtils.h"
#include "dslProcess.h"
#include <functional>
#include "atTiffStack.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTFloatLabeledEdit"
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTPropertyCheckBox"
#pragma resource "*.dfm"
TCreateLocalVolumesForm *CreateLocalVolumesForm;

using namespace at;
using namespace dsl;

//---------------------------------------------------------------------------
__fastcall TCreateLocalVolumesForm::TCreateLocalVolumesForm(RenderProject& rp, const string& imageMagickPath, TComponent* Owner)
	: TForm(Owner),
   	mRP(rp),
    mRC(rp, IdHTTP1),
    mImageMagickPath(imageMagickPath)
{
    mConvertExe = (joinPath(mImageMagickPath, "convert.exe"));
}

void TCreateLocalVolumesForm::populate(const RegionOfInterest& roi)
{
    mROI = roi;

    RenderServiceParameters rsp(mRP.getRenderServiceParameters());
	mRC.setBaseURL(rsp.getBaseURL());

    //Get stacks for project
    StringList stacks = mRC.getStacksForProject(mRP.getProjectOwner(), mRP.getRenderProjectName());
    if(stacks.size())
    {
	    populateCheckListBox(stacks, RenderStacksCB);
	   	StringList zs = getValidZsForStack(stacks[0]);
        Log(lInfo) << "Fetched "<<zs.count()<<" valid z's";
        Zs_GB->Caption = " Z Values (" + IntToStr((int) zs.count()) + ") ";

        //Populate list box
        populateCheckListBox(zs, mZs);
        mZs->CheckAll(cbChecked);

        //Setup ROI
        XCoordE->setValue(mROI.getX1());
        YCoordE->setValue(mROI.getY1());
        Width->setValue(mROI.getWidth());
        Height->setValue(mROI.getHeight());
        mScaleE->setValue(mROI.getScale());

        //Min and max intensity
        MinIntensityE->setReference(mRP.getMinIntensity());
        MaxIntensityE->setReference(mRP.getMaxIntensity());
    }
}

StringList TCreateLocalVolumesForm::getValidZsForStack(const string& stackName)
{
	//Fetch valid zs for current project
	mRP.setSelectedStackName(stackName);
    return mRC.getValidZs();
}

//---------------------------------------------------------------------------
void __fastcall TCreateLocalVolumesForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    //Check if we can close
    if(getNumberOfRunningThreads())
    {
        CanClose = (mrYes == MessageDlg("There are jobs still running. \n\nKill them?", mtWarning, TMsgDlgButtons() << mbYes<<mbNo, 0))
        ? true : false;
    }
    else
    {
    	CanClose = true;
    }
}

//---------------------------------------------------------------------------
void __fastcall TCreateLocalVolumesForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    //Cleanup and stop any running threads
}

//---------------------------------------------------------------------------
void __fastcall TCreateLocalVolumesForm::ImageTypeRGClick(TObject *Sender)
{
    ImageTypeCB->Enabled = false;
	Label4->Enabled = false;

    if(ImageTypeRG->ItemIndex == 1)
    {
        ImageTypeCB->Enabled = true;
        Label4->Enabled = true;
    }
}

//---------------------------------------------------------------------------
void __fastcall TCreateLocalVolumesForm::Button2Click(TObject *Sender)
{
    Close();
}

int TCreateLocalVolumesForm::getNumberOfRunningThreads()
{
    int runningCount(0);
    ThreadFrameThreadContainer::iterator it;
    for(it = mThreads.begin(); it != mThreads.end(); it++)
    {
        if(it->first->isRunning())
        {
			runningCount++;
        }
    }
    return runningCount;
}

//---------------------------------------------------------------------------
void __fastcall TCreateLocalVolumesForm::RunBtnClick(TObject *Sender)
{

    if(getNumberOfRunningThreads())
    {
        MessageDlg("Not Implemented", mtInformation, TMsgDlgButtons() << mbOK, 0);
    }
    else
    {
        StringList paras;
        paras.append(string("&maxTileSpecsToRender=150"));

	    //Create a thread for each stack
	    for(int i = 0; i < RenderStacksCB->Count; i++)
    	{
        	if(RenderStacksCB->Checked[i])
	        {
                mRP.setSelectedStackName(stdstr(RenderStacksCB->Items->Strings[i]));
                RenderServiceParameters rs = mRC.getRenderServiceParameters();
                int z = toInt(stdstr(mZs->Items->Strings[0]));

                mRC.setRenderProject(mRP);
                mRC.init(getImageType(), z, mScaleE->getValue(), MinIntensityE->getValue(), MaxIntensityE->getValue());

                //Create image URLs
                StringList urls;
                for(int i = 0; i < mZs->Count; i++)
                {
                    if(mZs->Checked[i])
                    {
                    	int	z = toInt(stdstr(mZs->Items->Strings[i]));
	                    urls.append(mRC.getURLForZ(z));
                    }
                }

                shared_ptr<FetchImagesThread> t = shared_ptr<FetchImagesThread>(new FetchImagesThread());
        		t->setup(urls, mRP.getLocalCacheFolder());
	    	    t->addParameters(paras);
                t->assignCallBacks(onThreadEnter, onThreadProgress, onThreadExit);

                shared_ptr<TCreateStackThreadFrame> frame = createThreadFrame(t);
                frame->GroupBox1->Caption = mRP.getSelectedStackName().c_str();
                frame->ProgressBar1->Max = urls.count();
                mThreads[t] = frame;
		        t->start();
            }
        }
        CreateStacksTimer->Enabled = true;
    }
}

shared_ptr<TCreateStackThreadFrame> TCreateLocalVolumesForm::createThreadFrame(shared_ptr<FetchImagesThread> t)
{
	shared_ptr<TCreateStackThreadFrame> f = shared_ptr<TCreateStackThreadFrame>(new TCreateStackThreadFrame(*t, ThreadsPanel));
    f->Parent = ThreadsPanel;
    f->Align = alTop;
    f->Height = 80;
    return f;
}

string TCreateLocalVolumesForm::getImageType()
{
    switch(ImageTypeRG->ItemIndex)
    {
        case 0: return "jpeg-image";
        case 1: return "tiff-image";
        case 2: return "png-image";
    }

    return "unknown";
}

//---------------------------------------------------------------------------
void __fastcall TCreateLocalVolumesForm::RenderStacksCBClick(TObject *Sender)
{
    int checkedCount(0);
    for(int i = 0; i < RenderStacksCB->Count; i++)
    {
        if(RenderStacksCB->Checked[i])
        {
			checkedCount++;
        }
    }

	RunBtn->Enabled = checkedCount > 0 ? true : false;
}

void __fastcall TCreateLocalVolumesForm::CreateStacksTimerTimer(TObject *Sender)

{
	if(getNumberOfRunningThreads())
    {
		RunBtn->Caption = "Stop";
    }
    else
    {
		CreateStacksTimer->Enabled = false;
	    ThreadFrameThreadContainer::iterator it;
    	for(it = mThreads.begin(); it != mThreads.end(); it++)
    	{
        	mThreads.erase(it);
    	}

        mThreads.clear();
		RunBtn->Caption = "Start";
    }
}

TCreateStackThreadFrame* TCreateLocalVolumesForm::getFrameForRawThread(FetchImagesThread* t)
{
    ThreadFrameThreadContainer::iterator it;
    for(it = mThreads.begin(); it != mThreads.end(); it++)
    {
        if(it->first.get() == t)
        {
            return it->second.get();
        }
    }
    return nullptr;
}

void TCreateLocalVolumesForm::onThreadEnter(void* arg1, void* arg2)
{
	FetchImagesThread* rawThread = (FetchImagesThread*) arg1;
    TCreateStackThreadFrame* frame = getFrameForRawThread(rawThread);
    if(frame)
    {
    	Log(lInfo) <<"Started creating TIFF stack for stack: " << stdstr(frame->GroupBox1->Caption);
    }
}

void TCreateLocalVolumesForm::onThreadProgress(void* arg1, void* arg2)
{
    FetchImagesThread* rawThread = (FetchImagesThread*) arg1;
    int* progress = (int*) arg2;
    if(rawThread)
    {
        //Get the frame associated with this thread
        TCreateStackThreadFrame* frame = getFrameForRawThread(rawThread);
        if(frame && progress)
        {
            frame->ProgressBar1->Position = *progress;
            stringstream caption;
            caption << *progress << " ("<<frame->ProgressBar1->Max<<")";
            frame->CurrentZ->Caption = caption.str().c_str();
        }
    }
}

void TCreateLocalVolumesForm::onThreadExit(void* arg1, void* arg2)
{
    //Use this callback to create a stack
    FetchImagesThread* rawThread = (FetchImagesThread*) arg1;

    if(!rawThread)
    {
        return;
    }

    StringList urls(rawThread->getImageURLs());

    if(urls.size() < 1)
    {
        return;
    }

    StringList imageFiles;
    string dataRoot(rawThread->getCacheRootFolder());
    string imagesFolder(getImageLocalCachePathFromURL(urls[0], dataRoot));
    string stackOutputFolder(getRenderProjectLocalDataRootFolderFromURL(urls[0], dataRoot));

    for(uint i = 0; i < urls.count(); i++)
    {
        string url = urls[i];
        //Make sure file exists
        string outFilePathANDFileName = getImageLocalCacheFileNameAndPathFromURL(url, dataRoot);
        Poco::File f(outFilePathANDFileName);
        if(fileExists(outFilePathANDFileName))
        {
            Log(lInfo) << "Stacking file: " << f.path();
            imageFiles.append(getFileNameNoPath(f.path()));
        }
    }

    //  CreateStack (blocking)
    TiffStack* tiffStack = createTiffStack(imageFiles, imagesFolder, stackOutputFolder);

    // Create Stack Metadata file

    //Add to project
    mRP.addChild(tiffStack);
    if(RemoveSectionsCB->Checked)
    {
        for(uint i = 0; i < urls.count(); i++)
        {
            string url = urls[i];
            //Make sure file exists
            string outFilePathANDFileName = getImageLocalCacheFileNameAndPathFromURL(url, dataRoot);
            Poco::File f(outFilePathANDFileName);
            if(f.exists())
            {
                Log(lInfo) << "Removing file: " << f.path();
                f.remove();
            }
        }
    }
}

//This will create a physical tiffstack on file, as well as a tiffstack project holding meta data
TiffStack* TCreateLocalVolumesForm::createTiffStack(const StringList& images, const string& wd, const string& outFolder)
{

	Process IMConvert;
    IMConvert.setExecutable(mConvertExe);
    IMConvert.setWorkingDirectory(wd);

    //Creat output filename
    //Instead of UUID, create a hash from the section numbers involved
    string stackFName("stack_" + getUUID());

    TiffStack* tiffStack = new TiffStack(stackFName, outFolder);

    //Create commandline for imagemagicks convert program
    stringstream cmdLine;
    cmdLine << " -monitor ";
    for(int i = 0; i < images.count(); i++)
    {
        string fName(images[i]);
        cmdLine << fName <<" ";
    }

	cmdLine << joinPath(outFolder, stackFName) << ".tif";

    Log(lInfo) << "Running convert.exe using command line:" << cmdLine.str();
	IMConvert.setup(cmdLine.str(), mhCatchMessages);
    IMConvert.start(false);
    return tiffStack;
}
//---------------------------------------------------------------------------
void __fastcall TCreateLocalVolumesForm::FormShow(TObject *Sender)
{
    if(!fileExists(mConvertExe))
    {
        stringstream msg;
        msg << "Image magicks 'convert.exe' was not found in the path:\n";
        msg << getFilePath(mConvertExe) << endl << endl;
        msg << "Make sure you have a proper installation of Image Magick! \nThe run button will be disabled..";
        MessageDlg(msg.str().c_str(), mtError, TMsgDlgButtons() << mbOK, 0);
        this->RunBtn->Enabled = false;
    }
}

void __fastcall TCreateLocalVolumesForm::FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}

