#ifndef atcliH
#define atcliH
#include "tclap/CmdLine.h"
#include <string>
//---------------------------------------------------------------------------

using std::string;
using TCLAP::ValueArg;
using TCLAP::SwitchArg;
using TCLAP::CmdLine;

class ATCli
{
    public:
    	//Command line arguments
		ValueArg<string> logLevel;
        ValueArg<string> dataRoot;
        SwitchArg 		 printJSON;

		TCLAP::CmdLine cmdLine;

        ATCli(int argc, const char * argv[]) :
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
};

#endif
