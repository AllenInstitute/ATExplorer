#pragma hdrstop
#include "dslUtils.h"
#include "dslLogger.h"
#include "atcore_class.h"
#include "atATExplorer.h"
#include "atATEExceptions.h"
#include "atATIFData.h"
#include "atcore_utils.h"

//---------------------------------------------------------------------------
using namespace std;
using namespace dsl;
using namespace at;
using namespace TCLAP;


int main(int argc, const char * argv[])
{
    try
    {
        gLogger.logToConsole(true);
		ATCli cli(argc, argv);

        if(cli.logLevel.isSet())
        {
            string value = cli.logLevel.getValue();
	        gLogger.setLogLevel(toLogLevel(toUpperCase(value)));
	        Log(lInfo) << "Current loglevel: " << toString(gLogger.getLogLevel());
        }
        else
        {
	        gLogger.setLogLevel(lInfo);
        }

//        Log(lDebug) << "Working Directory: " << getCWD() << endl;
//        ATExplorer atExplorer;

        //Set data.. if any
     	ATData* atData(nullptr);

        if(cli.dataRoot.isSet())
        {
            string value = cli.dataRoot.getValue();
	        Log(lInfo) << "Looking at data in folder: " << value;
            value = fixPathEnding(value);
		    Path dataPath(value);
            atData = new ATIFData(dataPath);
		    atData->assignOnPopulateCallbacks(onStartingPopulating, onProgressPopulating, onFinishedPopulating);
            populate(atData);
        }


        if(cli.printJSON.isSet())
        {
            if(atData)
            {
	            cout << atData->getInfoJSON();
            }
        }
    }
    catch(dsl::DSLException& ex)
    {
        Log(lError)<<"Application exception occurred: "<<ex.what()<<endl;
    }
    catch(const FileSystemException& e)
    {
        Log(lError) << "Exception: " << e.what();
        Log(lInfo) << "Application exiting..";
    }
	catch (TCLAP::ArgException &e)  // catch any exceptions
	{
    	Log(lError) << "Error: " << e.error();
    }
    catch(...)
    {
        Log(lError)<<"There was an unknown problem.."<<endl;
    }

    Log(lInfo)<<"Application is exiting...";
	return 0;

}

#if defined(WIN32)
#pragma comment(lib, "dslFoundation.lib")
#pragma comment(lib, "atExplorerFoundation.lib")
#pragma comment(lib, "poco_foundation.lib")
#endif
