#pragma hdrstop
#include "dslProcess.h"
#include "atCreateRawDataRenderStacksThread.h"
#include "dslLogger.h"
#include "Poco/File.h"
#include "dslStringUtils.h"
#include "dslFileUtils.h"
#include "atRibbon.h"
#include "atSession.h"
#include "atExceptions.h"
#include "atUtils.h"
//---------------------------------------------------------------------------

namespace at
{
using namespace dsl;

CreateRawDataRenderStacksThread::CreateRawDataRenderStacksThread(ATIFData& d)
:
mTheData(d),
onEnter(nullptr),
onProgress(nullptr),
onExit(nullptr)
{}

void CreateRawDataRenderStacksThread::assignCallBacks(FITCallBack one, FITCallBack two, FITCallBack three)
{
    onEnter 	= one;
    onProgress 	= two;
    onExit 		= three;
//    mTheData.assignOnPopulateCallbacks(one, two, three);
}

void CreateRawDataRenderStacksThread::run()
{
    worker();
}

string createDockerCommand(const string& outFile, const string& projDir);

void CreateRawDataRenderStacksThread::worker()
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
                string cmd = createDockerCommand(stateTblFileWithpath,  projDir);

                if(!dp.setup(cmd, mhIgnoreMessages))
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

string createDockerCommand(const string& stateTablePathP, const string& projDir)
{
	stringstream cmdLine;
    cmdLine << "exec renderapps python -m renderapps.dataimport.create_fast_stacks_multi";
    cmdLine << " --render.client_scripts /shared/render/render-ws-java-client/src/main/scripts";
	cmdLine << " --render.host W10DTMJ03EG6Z.corp.alleninstitute.org";
    cmdLine << " --render.port 8080";
	cmdLine << " --render.owner " 		<< "ATExplorer";
    cmdLine << " --render.project "		<< getLastFolderInPath(projDir);
    cmdLine << " --render.memGB 5G";
    cmdLine << " --log_level INFO";
    cmdLine << " --outputStackPrefix ACQ_";
	cmdLine << " --projectDirectory " 	<< toPosixPath(projDir, "/mnt");
    cmdLine << " --statetableFile " 	<< toPosixPath(stateTablePathP, "/mnt");
    return cmdLine.str();
}

}
