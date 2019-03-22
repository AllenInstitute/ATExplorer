#ifndef atcore_classH
#define atcore_classH
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
		ValueArg<string> 	logLevel;
        ValueArg<string> 	dataRoot;
        SwitchArg 		 	printJSON;
		TCLAP::CmdLine 		cmdLine;

        					ATCli(int argc, const char * argv[]);
};

#endif
