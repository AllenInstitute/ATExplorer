#pragma hdrstop
#include "dslProcess.h"
#include "atCreateATIFDataStateTablesThread.h"
#include "dslLogger.h"
#include "Poco/File.h"
#include "dslStringUtils.h"
#include "dslFileUtils.h"
#include "atRibbon.h"
#include "atSession.h"
#include "atATEExceptions.h"
#include "atStringUtils.h"
#include "atDockerContainer.h"
//---------------------------------------------------------------------------

namespace at
{
using namespace dsl;

CreateATIFDataStateTablesThread::CreateATIFDataStateTablesThread(ATIFData& d, DockerContainer* dc)
:
ATIFDataProcessThread(d, dc)
{}


void CreateATIFDataStateTablesThread::run()
{
	mIsRunning 		= true;
    mIsTimeToDie 	= false;

    if(onEnter)
    {
        onEnter(&mTheData, NULL, nullptr);
    }

    Log(lDebug4) << "Started creation of state tables";
    try
    {
        //First delete all tables in the folder..

        //Create StateTables
        //Print some information about ribbons and sections
        Log(lInfo) << "This is a " << mTheData.getNumberOfRibbons()<<" ribbons dataset";
        Sessions* sessions = mTheData.getSessions();

        for(int ribbon = 1; ribbon < mTheData.getNumberOfRibbons() + 1; ribbon++)
        {
	        RibbonSP aRibbon = mTheData.getRibbon(ribbon);
            if(!aRibbon)
            {
                continue;
            }
            for(int session = 0; session < mTheData.getNumberOfSessions(); session++)
            {
                SessionSP aSession = sessions->getSession(session);
                if(!aSession)
                {
                    continue;
                }
                for(int section = 0; section < mTheData.getNumberOfSections(); section++)
                {
                    if(mIsTimeToDie)
                    {
                        Log(lInfo) << "The creation of StateTables was ABORTED (check logs for any problems)";
                        //One fine time for using GOTO!
                        goto finish_line;
                    }

                    stringstream stateTblFileName;
                    stateTblFileName << "statetable_ribbon_";
                    stateTblFileName << aRibbon->getAliasAsInt();
                    stateTblFileName <<"_session_"<<aSession->getID();
                    stateTblFileName <<"_section_"<<section;
                    Log(lInfo) << "Creating state table file: " << stateTblFileName.str();

                    string projDir(mTheData.getBasePath().toString());
					string stateTblFileWithpath = joinPath(projDir, "scripts", stateTblFileName.str());

                    if(!fileExists(stateTblFileWithpath))
                    {
                        Process dp;
                        dp.assignCallbacks(nullptr, onDockerProgress, nullptr);
                        dp.setWorkingDirectory(".");
                        dp.setExecutable("docker.exe");
                        string cmd = createDockerCommand(stateTblFileWithpath,  projDir, aRibbon->getAliasAsInt(), session + 1, section);

                        if(!dp.setup(cmd, mhCatchMessages))
                        {
                            Log(lError) << "Failed setting up docker process. CMD: "<<cmd;
                        }

                        //Blocking..
                        dp.start(false);
                    }
                    else
                    {
                        Log(lWarning) << "StateTable file: " << stateTblFileName.str()<< " already exists";
                    }

                    if(onProgress)
                    {
                        onProgress(&mTheData, NULL, nullptr);
                    }
                }
            }
        }
    }
    catch(const FileSystemException& e)
    {
        Log(lError) << "Exception: " << e.what();
    }
    catch(...)
    {
    }

    finish_line:
    //Finish line...
  	Log(lInfo) << "Finished Populate AT Data Thread.";

    if(onExit)
    {
    	onExit(&mTheData, nullptr, nullptr);
    }

    mIsRunning = false;
    mIsFinished = true;
}

void CreateATIFDataStateTablesThread::onDockerProgress(void* arg1, void* arg2)
{
    if(arg2)
    {
        string& message = *((string*) arg2);

        //Check if message contain the word error. if so, finish the thread and
        //give some feedback
        if(contains("error", message, csCaseInsensitive))
        {
        	Log(lError) << "Docker Error message: " << message;
            mIsTimeToDie = true;
        }
    }
}

// Example
//            docker exec renderapps python /pipeline/make_state_table_ext_multi_pseudoz.py
//            --projectDirectory /mnt/data/M33
//            --outputFile  /mnt/data/M33/scripts/test
//            --oneribbononly True
//            --ribbon 4
//            --session 1
//            --section 0
string CreateATIFDataStateTablesThread::createDockerCommand(const string& outFile, const string& projDir, int ribbon, int session, int section)
{
    if(!mDockerContainer)
    {
        return "";
    }

	stringstream cmdLine;
    cmdLine << "exec " << mDockerContainer->getContainerName();
    cmdLine << " python /pipeline/make_state_table_ext_multi_pseudoz.py";
	cmdLine << " --projectDirectory " 	<< toDockerMountPath(projDir);
    cmdLine << " --outputFile "         << toDockerMountPath(outFile);
    cmdLine << " --oneribbononly "      << "True";
    cmdLine << " --ribbon "        		<< ribbon;
    cmdLine << " --session "        	<< session;
    cmdLine << " --section "        	<< section;
    return cmdLine.str();
}


}
