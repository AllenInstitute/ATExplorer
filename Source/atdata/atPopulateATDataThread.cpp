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

PopulateATDataThread::PopulateATDataThread(ATIFData& d)
:
ATIFDataProcessThread(d, NULL)
{}

void PopulateATDataThread::run()
{
	mIsRunning 		= true;
    mIsTimeToDie 	= false;

    Log(lDebug4) << "Started populating ATData from root folder: " << mTheData.getBasePath().toString();
    try
    {
        if(onEnter)
        {
            onEnter(&mTheData, NULL, nullptr);
        }

        if(mIsTimeToDie)
        {
        	Exception e("Aborting population of ATData");
            throw(e);
        }

        //!Populating the data object causes a scan of folders and files
        //!representing the data. No image data is loaded
        mTheData.populate(mIsTimeToDie);

        //Print some information about ribbons and sections
        Log(lInfo) << "This is a "<<mTheData.getNumberOfRibbons()<<" ribbons dataset";

        //Finish line...
        Log(lInfo) << "Finishing Populate AT Data Thread.";

        if(onExit)
        {
            onExit(&mTheData, nullptr, nullptr);
        }

    }
    catch(const FileSystemException& e)
    {
        Log(lError) << "Exception: " << e.what();
    }
    catch(const Exception& e)
    {
		Log(lError) << "Exception: " << e.what();
    }
    catch(...)
    {
    }


    mIsRunning = false;
    mIsFinished = true;
}

}
