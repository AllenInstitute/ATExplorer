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
mOutputFolder(wf),
mOnEnterCB(nullptr),
mTheStack(shared_ptr<TiffStackProject>(new TiffStackProject()))
{
    mConvertExe = (joinPath(mImageMagickPath, "convert.exe"));
}

TiffStackCreator::~TiffStackCreator()
{}

void TiffStackCreator::setStackName(const string& name)
{
    mTheStack->setProjectName(name);
}

void TiffStackCreator::assignCallbacks(dsl::Callback enter, dsl::Callback progress, dsl::Callback onExit)
{
    mOnEnterCB 		= enter;
    mOnProgressCB 	= progress;
    mOnExitCB 		= onExit;
}

shared_ptr<TiffStackProject> TiffStackCreator::getStack()
{
    return mTheStack;
}

bool TiffStackCreator::checkForImageMagick()
{
    if(!fileExists(mConvertExe))
    {
        stringstream msg;
        msg << "Image magicks 'convert.exe' was not found in the path:\n";
        msg << getFilePath(mConvertExe) << endl << endl;
        msg << "Make sure you have a proper installation of Image Magick!";
        Log(lError) << msg.str();
        return false;
    }
    return true;
}

bool TiffStackCreator::setOutputFolder(const string& path)
{
	mOutputFolder = path;
    return folderExists(path);
}

void TiffStackCreator::assignOpaqueData(void* arg1, void* arg2)
{
    mTheProcess.assignOpaqueData(arg1, arg2);
}

shared_ptr<TiffStackProject> TiffStackCreator::create(const StringList& fileNames, const string& outputFileName)
{
    mTheStack->reset();
    Process& IMConvert = mTheProcess;

	if(!checkForImageMagick())
    {
        Log(lError) << "No image magick..";
        return shared_ptr<TiffStackProject>();
    }

    IMConvert.setExecutable(mConvertExe);
    IMConvert.setWorkingDirectory(getFilePath(outputFileName));

    //Create commandline for imagemagicks convert program
    stringstream cmdLine;
    for(int i = 0; i < fileNames.count(); i++)
    {
        cmdLine << fileNames[i] <<" ";
    }

	cmdLine << outputFileName;

    Log(lInfo) << "Running ImageMagick's convert using commandline: " << cmdLine.str();


    mTheStack->setFilePath(getFilePath(outputFileName));
    mTheStack->setFileName(getFileNameNoPath(outputFileName));

	IMConvert.setup(cmdLine.str(), mhCatchMessages);
    IMConvert.assignCallbacks(mOnEnterCB, mOnProgressCB, mOnExitCB);
    IMConvert.start(true);
    return mTheStack;
}

}
