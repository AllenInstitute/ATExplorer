#pragma hdrstop
#include "atcli.h"
//---------------------------------------------------------------------------

ATCli::ATCli(int argc, const char * argv[])
:
    logLevel("l", 		"loglevel", "		Set loglevel", 															false, "Info", "string"),
    dataRoot("d", 		"dataroot", 		"Absolute path to root folder of input data (project) to process", 		true, "", "string"),
    printJSON("j",		"json",				"Output data in JSON format", 											false),
	showLogs("",		"nologs", 			"No logs to console", 													false),
    cmdLine("Command description message", ' ', "0.9")
{
    //Have TCLAP handle any command line excveptions..
    cmdLine.setExceptionHandling(true);
    cmdLine.add(logLevel);
    cmdLine.add(dataRoot);
    cmdLine.add(printJSON);
    cmdLine.add(showLogs);
    cmdLine.parse( argc, argv );
}


