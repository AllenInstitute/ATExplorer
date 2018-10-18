#pragma hdrstop
#include "dslProcess.h"
#include "atCreateATIFDataStateTablesThread.h"
#include "dslLogger.h"
#include "Poco/File.h"
#include "dslStringUtils.h"
#include "dslFileUtils.h"
#include "atRibbon.h"
#include "atSession.h"
#include "atExceptions.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace at
{
using namespace dsl;

CreateATIFDataStateTablesThread::CreateATIFDataStateTablesThread(ATIFData& d)
:
mTheData(d),
onEnter(nullptr),
onProgress(nullptr),
onExit(nullptr)
{}

void CreateATIFDataStateTablesThread::assignCallBacks(FITCallBack one, FITCallBack two, FITCallBack three)
{
    onEnter 	= one;
    onProgress 	= two;
    onExit 		= three;
    mTheData.assignOnPopulateCallbacks(one, two, three);
}

void CreateATIFDataStateTablesThread::run()
{
    worker();
}

string createDockerCommand(const string& outFile, const string& projDir, int ribbon, int session, int section);

void CreateATIFDataStateTablesThread::worker()
{
	mIsRunning 		= true;
    mIsTimeToDie 	= false;

    if(onEnter)
    {
        onEnter(&mTheData, NULL);
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
                        Log(lInfo) << "Aborting creation of StateTables";
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
                        dp.setWorkingDirectory(".");
                        dp.setExecutable("docker.exe");
                        string cmd = createDockerCommand(stateTblFileWithpath,  projDir, aRibbon->getAliasAsInt(), session + 1, section);


                        if(!dp.setup(cmd, mhIgnoreMessages))
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
                        onProgress(&mTheData, NULL);
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
    	onExit(&mTheData, nullptr);
    }

    mIsRunning = false;
    mIsFinished = true;
}

string toPosixPath(const string& winpath);

string createDockerCommand(const string& outFile, const string& projDir, int ribbon, int session, int section)
{
// Example
//            docker exec renderapps python /pipeline/make_state_table_ext_multi_pseudoz.py
//            --projectDirectory /mnt/data/M33
//            --outputFile  /mnt/data/M33/scripts/test
//            --oneribbononly True
//            --ribbon 4
//            --session 1
//            --section 0

	stringstream cmdLine;
    cmdLine << "exec renderapps python /pipeline/make_state_table_ext_multi_pseudoz.py";
	cmdLine << " --projectDirectory " 	<< joinPath("/mnt", toPosixPath(projDir), '/');
    cmdLine << " --outputFile "         << joinPath("/mnt", toPosixPath(outFile), '/');
    cmdLine << " --oneribbononly "      << "True";
    cmdLine << " --ribbon "        		<< ribbon;
    cmdLine << " --session "        	<< session;
    cmdLine << " --section "        	<< section;
    return cmdLine.str();
}

string stripToChar(const string& str, char theChar)
{
    // trim leading spaces
    size_t startpos = str.find_first_of(theChar);
    if(startpos != string::npos)
    {
	    string str2;
        str2 = str.substr( startpos + 1 );
	    return str2;
    }
    else
    {
        return str;
    }
}

string toPosixPath(const string& winpath)
{
    //Strip driveletter
    string pPath(stripToChar(winpath, ':'));
	std::replace(pPath.begin(), pPath.end(), '\\', '/');

    pPath = trimBack(pPath, '/');
    return pPath;
}
}
