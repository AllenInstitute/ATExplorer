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
    mRC(),
    mImageMagickPath(imageMagickPath)
{
    mConvertExe = (joinPath(mImageMagickPath, "convert.exe"));
}

void TCreateLocalVolumesForm::populate(const RegionOfInterest& roi, const StringList& checked_stacks)
{
    mROI = roi;
    mRC.setRenderServiceParameters(mRP.getRenderServiceParameters());

    //Setup ROI
    XCoordE->setValue(mROI.getX1());
    YCoordE->setValue(mROI.getY1());
    Width->setValue(mROI.getWidth());
    Height->setValue(mROI.getHeight());
    mScaleE->setValue(mROI.getScale());

    //Min and max intensity
    MinIntensityE->setReference(mRP.getMinIntensity());
    MaxIntensityE->setReference(mRP.getMaxIntensity());

    //Get stacks for project
    StringList stacks = mRC.StackDataAPI.getStacksForProject(mRP.getProjectOwner(), mRP.getRenderProjectName());
    if(stacks.size())
    {
	    populateCheckListBox(stacks, RenderStacksCB);
    }

    //Check stacks from supplied list
    for(int i = 0; i < checked_stacks.count(); i++)
    {
		int iToCheck = RenderStacksCB->Items->IndexOf(checked_stacks[i].c_str());
        if(iToCheck != -1)
        {
			RenderStacksCB->Checked[iToCheck] = true;
        }

        if(i == 0 && iToCheck != -1)
        {
        	RenderStacksCB->Selected[iToCheck] = true;
        	RenderStacksCB->ItemIndex = iToCheck;
        }
    }
	RenderStacksCBClick(NULL);
}

void TCreateLocalVolumesForm::populateZs(const string& stack)
{
    StringList zs = getValidZsForStack(stack);
    Log(lInfo) << "Fetched "<<zs.count()<<" valid z's";
    Zs_GB->Caption = " Z Values (" + IntToStr((int) zs.count()) + ") ";

    //Populate list box
    populateCheckListBox(zs, mZs);
    mZs->CheckAll(cbChecked);
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
	mThreads.clear();
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
                const RenderServiceParameters* rs = mRC.getRenderServiceParameters();
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

                shared_ptr<FetchImagesThread> t = shared_ptr<FetchImagesThread>(new FetchImagesThread(mRP.getSelectedStackName()));
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
        case 1: return "tiff16-image";
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

    //Populate z's
	RunBtn->Enabled = checkedCount > 0 ? true : false;
	string stack = stdstr(RenderStacksCB->Items->Strings[RenderStacksCB->ItemIndex]);

    //If we have one checked stack, make sure succesivley checked stacks have the same z's
    if(checkedCount)
    {
       	StringList zs = getValidZsForStack(stack);

		//make sure these z's are the same as the currenttly seleted ones
       	StringList currentzs = getStrings(mZs);

       	if(zs != currentzs && currentzs.count() != 0)
       	{
            MessageDlg("This stack can't be checked as it does not contain the same z's as other checked stacks!", mtError, TMsgDlgButtons() << mbOK, 0);
            RenderStacksCB->Checked[RenderStacksCB->ItemIndex] = false;
       	}
        else
        {
			populateZs(stack);
        }
    }
    else
    {
    	//Repopulate z's
	    populateZs(stack);
    }
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

    for(uint i = 0; i < urls.count(); i++)
    {
        string url = urls[i];
        //Make sure file exists
        string outFilePathANDFileName = getImageLocalCacheFileNameAndPathFromURL(url, dataRoot, mRP.getSelectedChannelName());
        Poco::File f(outFilePathANDFileName);
        if(fileExists(outFilePathANDFileName))
        {
            Log(lInfo) << "Stacking file: " << f.path();
            imageFiles.append(getFileNameNoPath(f.path()));
        }
    }

    string stackOutputFileNameAndPath(getRenderProjectLocalDataRootFolderFromURL(urls[0], dataRoot));
    stackOutputFileNameAndPath = joinPath(stackOutputFileNameAndPath, "stack_" + rawThread->getRenderStackName());

    //  CreateStack (blocking)
    TiffStack* tiffStack = createTiffStack(imageFiles, imagesFolder, stackOutputFileNameAndPath);

    // Create Stack Metadata file

    //Add to project
    mRP.addChild(tiffStack);
    if(RemoveSectionsCB->Checked)
    {
        for(uint i = 0; i < urls.count(); i++)
        {
            string url = urls[i];
            //Make sure file exists
            string outFilePathANDFileName = getImageLocalCacheFileNameAndPathFromURL(url, dataRoot, mRP.getSelectedChannelName());
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
TiffStack* TCreateLocalVolumesForm::createTiffStack(const StringList& images, const string& wd, const string& outFName)
{
	Process IMConvert;
    IMConvert.setExecutable(mConvertExe);
    IMConvert.setWorkingDirectory(wd);

    TiffStack* tiffStack = new TiffStack(getFileNameNoPath(outFName), getFilePath(outFName));

    //Create commandline for imagemagicks convert program
    stringstream cmdLine;
    cmdLine << " -monitor ";
    for(int i = 0; i < images.count(); i++)
    {
        string fName(images[i]);
        cmdLine << fName <<" ";
    }

    //Creat output filename
	cmdLine << outFName << ".tif";

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

