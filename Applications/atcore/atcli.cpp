#pragma hdrstop
#include "atcli.h"
//---------------------------------------------------------------------------

ATCli::ATCli(int argc, const char * argv[])
:
    loglevel("l", 		"loglevel", 		"Set loglevel, Error, Warning, Info, Debug, Debug1-5", 	 				false, "Info", "string"),
    dataroot("d", 		"dataroot", 		"Absolute path to root folder of input data (project) to process", 		true, "", "string"),
    datainfo("",		"datainfo",		 	"Return data information", 												false),
    printjson("j",		"json",				"Output data in JSON format", 											false),
	showLogs("",		"nologs", 			"No logs to console", 													false),
    cmdLine("Command description message", ' ', "0.5")
{
    //Have TCLAP handle any command line excveptions..
    cmdLine.setExceptionHandling(true);
    cmdLine.add(loglevel);
    cmdLine.add(dataroot);
    cmdLine.add(printjson);
    cmdLine.add(datainfo);
    cmdLine.add(showLogs);
    cmdLine.parse( argc, argv );
}


