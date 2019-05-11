#pragma hdrstop
#include "atTiffStackCreator.h"
#include "dslStringList.h"
#include "dslStringUtils.h"
#include "dslFileUtils.h"
#include "dslUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace dsl;
namespace at
{
TiffStackCreator::TiffStackCreator(const string& imPath, const string& wf)
:
mImageMagickPath(imPath),
mWorkingFolder(wf)
{
    mConvertExe = (joinPath(mImageMagickPath, "convert.exe"));
}

TiffStackCreator::~TiffStackCreator()
{}

void TiffStackCreator::onIMProcessFinished(void* arg1, void* arg2)
{
    Log(lInfo) << "Process Finished";

//    if(arg1 == (void*) StacksCB)
//    {
//        int itemIndx = StacksCB->ItemIndex;
//	    checkCache();
//        StacksCB->ItemIndex = itemIndx;
//        StacksCB->OnClick(StacksCB);
//
//        //Open MIP window
//        if(arg2)
//        {
//        	string& fName = *((string*) arg2);
//            if(fileExists(fName))
//            {
//                OpenImageForm(fName);
//                delete &fName;
//            }
//        }
//    }
//    else if(arg1 == (void*) mZs)
//    {
//        int itemIndx = StacksCB->ItemIndex;
//	    checkCache();
//        StacksCB->ItemIndex = itemIndx;
//    }
}

void TiffStackCreator::create(const StringList& fileNames)
{
    Process& IMConvert = mAProcess;
    string convertExe(joinPath(mImageMagickPath, "convert.exe"));

    if(!fileExists(convertExe))
    {
        stringstream msg;
        msg << "Image magicks 'convert.exe' was not found in the path:\n";
        msg << getFilePath(convertExe) << endl << endl;
        msg << "Make sure you have a proper installation of Image Magick";
        //MessageDlg(msg.str().c_str(), mtError, TMsgDlgButtons() << mbOK, 0);
        Log(lError) << msg;
        return;
    }

    IMConvert.setExecutable(convertExe);
    IMConvert.setWorkingDirectory(mWorkingFolder);

    //Extract selected filenames from checked z's
//    StringList sections = getCheckedItems(mZs);

    //Creat output filename
    string stackFName("stack_" + getUUID());

    //Create commandline for imagemagicks convert program
    stringstream cmdLine;
    for(int i = 0; i < fileNames.count(); i++)
    {
        cmdLine << fileNames[i] <<" ";
    }

	cmdLine << stackFName << ".tif";

    Log(lInfo) << "Running convert using commandline: " << cmdLine.str();

	IMConvert.setup(cmdLine.str(), mhCatchMessages);
    IMConvert.assignCallbacks(NULL, NULL, onIMProcessFinished);
    IMConvert.assignOpaqueData((void*) &fileNames, nullptr);
    IMConvert.start(true);
}

}
