#pragma hdrstop
#include "atcore_class.h"
#include "dslLogger.h"
#include "dslUtils.h"
#include "dslFileUtils.h"
#include "atcore_utils.h"
#include "atATEExceptions.h"
#include "Poco/Environment.h"
//---------------------------------------------------------------------------

using namespace dsl;
using namespace std;
using namespace at;
using namespace Poco;

ATCore::ATCore(int argc, const char * argv[])
:
CLI(argc, argv),
IFData(string("")),
mIniFile("")//,
//mATExplorer()
{
    //Observe that TCLAP will throw and handle any command line exceptions
    //before even getting here..
    if(CLI.loglevel.isSet())
    {
        string value = CLI.loglevel.getValue();
        gLogger.setLogLevel(toLogLevel(toUpperCase(value)));
    }
    else
    {
        string v = CLI.loglevel.getValue();
        gLogger.setLogLevel(toLogLevel(v));
    }

    //Get path to at-system-config.ini from the environment

//    Environment env;
//    string envPath("AT_SYSTEM_CONFIG_FOLDER");
//    if(!env.has(envPath))
//    {
//        throw(FileSystemException("The environment variable: " + envPath + " is not set!"));
//    }
//
//    string path(env.get(envPath));
//    mIniFile.load(joinPath(path, "at-system-config.ini"));

    //Setup a renderservice
//    mATExplorer.createRenderService();
}

void ATCore::populateData()
{
    //Set data.. if any
    string value = CLI.dataroot.getValue();
    value = fixPathEnding(value);
    Path dataPath(value);
    Log(lInfo) << "Looking at data in folder: " << value;
    if(!folderExists(value))
    {
        throw(FileSystemException("The Folder: " + value + " don't exist!"));
    }

    IFData.setBasePath(dataPath.toString());
    IFData.assignOnPopulateCallbacks(onStartingPopulating, onProgressPopulating, onFinishedPopulating);

    //Catch signals and set dummy to false, will stop population of data gracefully
    bool dummy(false);
    IFData.populate(dummy);
}

//string ATCore::getOwner()
//{
//    IniSection* sec = mIniFile.getSection("GENERAL");
//
//    if(CLI.owner.isSet())
//    {
//        return CLI.owner.getValue();
//    }
//    else
//    {
//	    IniKey* ownerkey = sec->getKey("RENDER_PROJECT_OWNER");
//
//        if(ownerkey)
//        {
//            return ownerkey->mValue;
//        }
//    }
//    return "";
//
//}

