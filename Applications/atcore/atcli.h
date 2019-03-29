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
		ValueArg<string> 	            loglevel;
        ValueArg<string> 	            dataroot;
        ValueArg<int>	                sectionsinribbon;
        SwitchArg 		 	            datainfo;
        SwitchArg 		 	            printjson;
        SwitchArg 		 	            consolelogs;
		TCLAP::CmdLine 		            cmdLine;

        					            ATCli(int argc, const char * argv[]);
};

#endif
