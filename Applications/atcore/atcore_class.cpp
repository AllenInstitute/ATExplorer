#pragma hdrstop
#include "atcore_class.h"
//---------------------------------------------------------------------------

ATCli::ATCli(int argc, const char * argv[])
:
    logLevel("l", "loglevel", "Set loglevel", false, "Info", "string"),
    dataRoot("d", "dataroot", "Absolute path to root folder of input data (project) to process", true, "", "string"),
    printJSON("j","json","Output data in JSON format", false),
    cmdLine("Command description message", ' ', "0.9")
{
    cmdLine.setExceptionHandling(true);
    cmdLine.add(logLevel);
    cmdLine.add(dataRoot);
    cmdLine.add(printJSON);
    cmdLine.parse( argc, argv );
}


