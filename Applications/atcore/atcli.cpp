#pragma hdrstop
#include "atcli.h"
//---------------------------------------------------------------------------

ATCli::ATCli(int argc, const char * argv[])
:                  //Flags..................        Information.............................                                    Required..  Value.. 	type
    loglevel(		"l", 		"loglevel", 		"Set loglevel, Error, Warning, Info, Debug, Debug1-5", 	 					false, 		"Info", 	"string"),
    dataroot(		"d", 		"dataroot", 		"Absolute path to root folder of input data (project) to process", 			true, 		"", 		"string"),
    datainfo(		"",			"datainfo",		 	"Return data information", 													false),
    sectionsinribbon("",        "sectionsinribbon", "Return number of sections in Ribbon#",                                 	false, 		-1,     	"int"),
    printjson(		"j",		"json",				"Output data in JSON format", 												false),
	consolelogs(	"",			"consolelogs", 		"console logging", 															false),
    cmdLine("Command description message", ' ', "0.5")
{
    //Have TCLAP handle any command line excveptions..
    cmdLine.setExceptionHandling(true);
    cmdLine.add(loglevel);
    cmdLine.add(dataroot);
    cmdLine.add(printjson);
    cmdLine.add(datainfo);
    cmdLine.add(sectionsinribbon);
    cmdLine.add(consolelogs);
    cmdLine.parse( argc, argv );
}


