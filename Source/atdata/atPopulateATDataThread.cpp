#pragma hdrstop
#include "atPopulateATDataThread.h"
#include "dslLogger.h"
#include "Poco/File.h"
#include "dslFileUtils.h"
#include "atRibbon.h"
#include "atSession.h"
#include "atExceptions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace at
{
using namespace dsl;

PopulateATDataThread::PopulateATDataThread(ATData& d)
:
mTheData(d),
onEnter(nullptr),
onProgress(nullptr),
onExit(nullptr)
{}

//void PopulateATDataThread::setData(ATDataSP d)
//{
//	mTheData = d;
//}

void PopulateATDataThread::assignCallBacks(FITCallBack one, FITCallBack two, FITCallBack three)
{
    onEnter 	= one;
    onProgress 	= two;
    onExit 		= three;
//    if(mTheData)
    {
        mTheData.assignOnPopulateCallbacks(one, two, three);
    }
}


void PopulateATDataThread::run()
{
    worker();
}

void PopulateATDataThread::worker()
{
	mIsRunning 		= true;
    mIsTimeToDie 	= false;

    if(onEnter)
    {
        onEnter(&mTheData, NULL);
    }

//    if(!mTheData)
//    {
//        Log(lError) << "Tried to populate NULL data object in thread..";
//    }
//    else
    {
        Log(lDebug4) << "Started populating ATData from root folder: " << mTheData.getBasePath().toString();
        try
        {
            //!Populating the data object causes a scan of folders and files
            //!representing the data. No image data is loaded
            mTheData.populate(mIsTimeToDie);

            //Print some information about ribbons and sections
            Log(lInfo) << "This is a "<<mTheData.getNumberOfRibbons()<<" ribbons dataset";

        }
        catch(const FileSystemException& e)
        {
            Log(lError) << "Exception: " << e.what();
        }
        catch(...)
        {
        }
    }

    //Finish line...
  	Log(lInfo) << "Finishing Populate AT Data Thread.";

    if(onExit)
    {
    	onExit(&mTheData, nullptr);
    }

    mIsRunning = false;
    mIsFinished = true;
}

}
