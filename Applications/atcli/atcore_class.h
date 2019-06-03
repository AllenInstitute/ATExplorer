#ifndef atcore_classH
#define atcore_classH
#include "atcli.h"
#include <string>
#include "atdata/atATIFData.h"
#include "dslIniFile.h"
//#include "atATExplorer.h"
//---------------------------------------------------------------------------

using std::string;
using TCLAP::ValueArg;
using TCLAP::SwitchArg;
using TCLAP::CmdLine;
using at::ATIFData;
using dsl::IniFile;
//using at::ATExplorer;

class ATCore
{
    public:
        					ATCore(int argc, const char * argv[], const string& version);

                            //The ATCli is an object dealing with the command line
        ATCli               CLI;

        void                populateData();

     	ATIFData   			IFData;

//        string              getOwner();

                            //Have to use CURL or Poco instead of Indy
        //ATExplorer          mATExplorer;

    private:
        IniFile             mIniFile;
        string              mVersion;

};

#endif
