#pragma hdrstop
#include "dslProcess.h"
#include "atCreateRawDataRenderStacksThread.h"
#include "dslLogger.h"
#include "Poco/File.h"
#include "dslStringUtils.h"
#include "dslFileUtils.h"
#include "atRibbon.h"
#include "atSession.h"
#include "atATEExceptions.h"
#include "atStringUtils.h"
//---------------------------------------------------------------------------

namespace at
{

using namespace dsl;
CreateRawDataRenderStacksThread::CreateRawDataRenderStacksThread(ATIFData& d, const string& renderHost)
:
ATIFDataProcessThread(d, renderHost)
{}

void CreateRawDataRenderStacksThread::run()
{
	mIsRunning 		= true;
    mIsTimeToDie 	= false;

    if(onEnter)
    {
        onEnter(&mTheData, NULL, NULL);
    }

    Log(lInfo) << "Started creation of Raw Data RenderStacks";
    try
    {
        Log(lInfo) << "About to process: " << mTheData.getNumberOfStateTables()<<" state tables into RenderStacks";
        StringList tables = mTheData.getStateTables();
        for(int i = 0; i < tables.count(); i++)
        {

            if(mIsTimeToDie)
            {
                Log(lInfo) << "Aborting creation of StateTables";
                //One fine time for using GOTO!
                goto finish_line;
            }

            if(onProgress)
            {
                onProgress(&mTheData, &i, &tables[i]);
            }

            string projDir(mTheData.getBasePath().toString());
            string stateTblFileWithpath = joinPath(projDir, "scripts", tables[i]);
            if(fileExists(stateTblFileWithpath))
            {
                Process dp;
                dp.setWorkingDirectory(".");
                dp.setExecutable("docker.exe");
                dp.assignCallbacks(nullptr, onDockerProgress, nullptr);
                string cmd = createDockerCommand(stateTblFileWithpath,  projDir);

                if(!dp.setup(cmd, mhCatchMessages))
                {
                    Log(lError) << "Failed setting up docker process. CMD: "<<cmd;
                }

                //Blocking..
                dp.start(false);
            }
            else
            {
                Log(lWarning) << "StateTable file: " << tables[i]<< " don't exist!";
            }

            if(onProgress)
            {
                onProgress(&mTheData, &i, NULL);
            }
        }
    }
    catch(const FileSystemException& e)
    {
        Log(lError) << "Exception: " << e.what();
    }
    catch(...)
    {}

    //Finish line...  yes.. a GOTO label
    finish_line:

    Log(lInfo) << "Finished creation of Raw Data RenderStacks";

    if(onExit)
    {
    	onExit(&mTheData, NULL, NULL);
    }

    mIsRunning = false;
    mIsFinished = true;
}

void CreateRawDataRenderStacksThread::onDockerProgress(void* arg1, void* arg2)
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

string CreateRawDataRenderStacksThread::createDockerCommand(const string& stateTablePathP, const string& projDir)
{
	stringstream cmdLine;
//    cmdLine << "exec "<<mDockerContainer;
//    cmdLine << " python -m renderapps.dataimport.create_fast_stacks_multi";
//    cmdLine << " --render.client_scripts /shared/render/render-ws-java-client/src/main/scripts";
//	cmdLine << " --render.host " <<mRenderHost; // W10DTMJ03EG6Z.corp.alleninstitute.org";
//    cmdLine << " --render.port 8080";
//	cmdLine << " --render.owner " 		<< "ATExplorer";
//    cmdLine << " --render.project "		<< getLastFolderInPath(projDir);
//    cmdLine << " --render.memGB 5G";
//    cmdLine << " --log_level INFO";
//    cmdLine << " --outputStackPrefix ACQ_";
//	cmdLine << " --projectDirectory " 	<< toPosixPath(projDir, "/mnt");
//    cmdLine << " --statetableFile " 	<< toPosixPath(stateTablePathP, "/mnt");
    return cmdLine.str();
}

}
