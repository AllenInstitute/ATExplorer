#ifndef atcore_classH
#define atcore_classH
#include "atcli.h"
#include <string>
#include "atATIFData.h"
//---------------------------------------------------------------------------

using std::string;
using TCLAP::ValueArg;
using TCLAP::SwitchArg;
using TCLAP::CmdLine;
using at::ATIFData;
class ATCore
{
    public:
                            //The ATCli is an object dealing with the command line
        ATCli               CLI;

        void                populateData();
        					ATCore(int argc, const char * argv[]);
     	ATIFData   			IFData;
    private:

};

#endif
