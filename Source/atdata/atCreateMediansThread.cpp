#pragma hdrstop
#include "dslProcess.h"
#include "atCreateMediansThread.h"
#include "dslLogger.h"
#include "Poco/File.h"
#include "dslStringUtils.h"
#include "dslFileUtils.h"
#include "atRibbon.h"
#include "atSession.h"
#include "atATEExceptions.h"
//#include "atUtils.h"
#include "atStringUtils.h"
//---------------------------------------------------------------------------

namespace at
{
using namespace dsl;

CreateMediansThread::CreateMediansThread(ATIFData& d)
:
ATIFDataProcessThread(d, NULL)
{}

void CreateMediansThread::run()
{
	mIsRunning 		= true;
    mIsTimeToDie 	= false;

//    if(onEnter)
//    {
//        onEnter(&mTheData, NULL, NULL);
//    }
//
//    Log(lDebug4) << "Started creation of state tables";
//    try
//    {
//        //First delete all tables in the folder..
//
//        //Create StateTables
//        //Print some information about ribbons and sections
//        Log(lInfo) << "This is a " << mTheData.getNumberOfRibbons()<<" ribbons dataset";
//        Sessions* sessions = mTheData.getSessions();
//
//        for(int session = 0; session < mTheData.getNumberOfSessions(); session++)
//        {
//            SessionSP aSession = sessions->getSession(session);
//            if(!aSession)
//            {
//                continue;
//            }
//
//            if(onProgress)
//            {
////                        onProgress(&mTheData, NULL, NULL);
//            }
//
//        }
//    }
//    catch(const FileSystemException& e)
//    {
//        Log(lError) << "Exception: " << e.what();
//    }
//    catch(...)
//    {
//    }
//
//    finish_line:
//    //Finish line...
//  	Log(lInfo) << "Finished Populate AT Data Thread.";
//
//    if(onExit)
//    {
//    	onExit(&mTheData, nullptr, nullptr);
//    }

    mIsRunning = false;
    mIsFinished = true;
}

//string createDockerCommand(const string& outFile, const string& projDir, int ribbon, int session, int section);

//string createDockerCommand(const string& outFile, const string& projDir, int ribbon, int session, int section)
//{
//// Example
////            docker exec renderapps python /pipeline/make_state_table_ext_multi_pseudoz.py
////            --projectDirectory /mnt/data/M33
////            --outputFile  /mnt/data/M33/scripts/test
////            --oneribbononly True
////            --ribbon 4
////            --session 1
////            --section 0
//
//	stringstream cmdLine;
//    cmdLine << "exec renderapps_multchan python /pipeline/make_state_table_ext_multi_pseudoz.py";
//	cmdLine << " --projectDirectory " 	<< toPosixPath(projDir, "/mnt");
//    cmdLine << " --outputFile "         << toPosixPath(outFile, "/mnt");
//    cmdLine << " --oneribbononly "      << "True";
//    cmdLine << " --ribbon "        		<< ribbon;
//    cmdLine << " --session "        	<< session;
//    cmdLine << " --section "        	<< section;
//    return cmdLine.str();
//}
//

}
