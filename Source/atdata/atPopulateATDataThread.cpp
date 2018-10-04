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

PopulateATDataThread::PopulateATDataThread(ATData* d)
:
mTheData(d),
onEnter(nullptr),
onProgress(nullptr),
onExit(nullptr)
{}

void PopulateATDataThread::setData(ATData* d)
{
	mTheData = d;
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
        onEnter(this, NULL);
    }

    if(!mTheData)
    {
        Log(lError) << "Tried to populate NULL data object in thread..";
    }
    else
    {

        Log(lDebug4) << "Started populating ATData from root folder: " << mTheData->getBasePath().toString();

        try
        {

            //!Populating the data object causes a scan of folders and files
            //!representing the data. No image data is loaded
            mTheData->populate();

            //Print some information about ribbons and sections
            Log(lInfo) << "This is a "<<mTheData->getNumberOfRibbons()<<" ribbons dataset";

            //Add ribbon items to TreeView

//
//            Ribbon* ribbon = mTheData->getFirstRibbon();
//            while(ribbon)
//            {
//                Log(lInfo) << "There are "<<ribbon->sectionCount()<<" sections in ribbon "<< ribbon->getAlias();
//                ribbon = mTheData->getNextRibbon();
//            }
//
//            //Check Sessions and channels, i.e. actual data
//            Session* session =  mTheData->getFirstSession();
//            while(session)
//            {
//                Log(lInfo) << "Checking session " << session->getLabel();
//                //Get Channels in session
//                Channel* chan = mTheData->getFirstChannel(session);
//                while(chan)
//                {
//                    Log(lInfo) << "Checking channel: " << chan->getLabel();
//                    Ribbon* ribbon = mTheData->getFirstRibbon();
//                    while(ribbon)
//                    {
//                        Section* section = ribbon->getFirstSection();
//                        //Loop through frames
//                        while(section)
//                        {
//                            Tiles& tiles = section->getTiles(*chan);
//                            section = ribbon->getNextSection();
//                        }
//
//                        ribbon = mTheData->getNextRibbon();
//                    }
//                    chan = mTheData->getNextChannel(session);
//                }
//                session = mTheData->getNextSession();
//            }

            if(onProgress)
            {
                onProgress(this, mTheData);
            }

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
        onExit(this, NULL);
    }

    mIsRunning = false;
    mIsFinished = true;
}

void PopulateATDataThread::assignCallBacks(FITCallBack one, FITCallBack two, FITCallBack three)
{
    onEnter 	= one;
    onProgress 	= two;
    onExit 		= three;
}

}
