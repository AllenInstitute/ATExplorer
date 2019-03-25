#pragma hdrstop
#include "atcore_class.h"
#include "dslLogger.h"
#include "dslUtils.h"
#include "dslFileUtils.h"
#include "atcore_utils.h"
#include "atATEExceptions.h"
//---------------------------------------------------------------------------

using namespace dsl;
using namespace std;
using namespace at;
ATCore::ATCore(int argc, const char * argv[])
:
CLI(argc, argv),
IFData(string(""))
{
    //Observe that TCLAP will throw and handle any command line exceptions
    //before even getting here..
    if(CLI.loglevel.isSet())
    {
        string value = CLI.loglevel.getValue();
        gLogger.setLogLevel(toLogLevel(toUpperCase(value)));
        Log(lInfo) << "Current loglevel: " << toString(gLogger.getLogLevel());
    }
    else
    {
        string v = CLI.loglevel.getValue();
        gLogger.setLogLevel(toLogLevel(v));
    }
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


