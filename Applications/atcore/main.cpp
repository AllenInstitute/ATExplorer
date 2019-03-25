#pragma hdrstop
#include "dslUtils.h"
#include "dslFileUtils.h"
#include "dslLogger.h"
#include "atcore_class.h"
#include "atATExplorer.h"
#include "atATEExceptions.h"
//---------------------------------------------------------------------------
using namespace std;
using namespace dsl;
using namespace at;
using namespace TCLAP;

int main(int argc, const char * argv[])
{
    try
    {
		ATCore atCore(argc, argv);
        gLogger.logToConsole(atCore.CLI.showLogs.getValue());

	    if(atCore.CLI.dataroot.isSet())  //for verbosity only, if not set, the CLI throws
    	{
        	atCore.populateData();
        }

    	//Check if no other flag is set, pring information
        if(!atCore.CLI.datainfo.isSet() && !atCore.CLI.printjson.isSet())
        {
		    cout << atCore.IFData.getInfo();
        }

        if(atCore.CLI.datainfo.isSet())
        {
            cout << atCore.IFData.getInfo();
        }
        else if(atCore.CLI.printjson.isSet())
        {
            cout << atCore.IFData.getInfoJSON();
        }
    }
    catch(dsl::DSLException& ex)
    {
        Log(lError)<<"Application exception occurred: "<<ex.what()<<endl;
    }
    catch(const FileSystemException& e)
    {
        Log(lError) << "Exception: " << e.what();
        Log(lInfo)  <<  "atcore is exiting..";
    }
	catch (TCLAP::ArgException &e)  // catch any exceptions
	{
    	Log(lError) << "Error: " << e.error();
    }
    catch(...)
    {
        Log(lError)<<"There was an unknown problem.."<<endl;
    }

    Log(lInfo)<< "atcore is exiting..";
	return 0;

}

#if defined(WIN32)
#pragma comment(lib, "dslFoundation.lib")
#pragma comment(lib, "atExplorerFoundation.lib")
#pragma comment(lib, "poco_foundation.lib")
#endif
