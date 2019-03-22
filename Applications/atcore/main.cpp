#pragma hdrstop
#include "dslUtils.h"
#include "dslFileUtils.h"
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
	        gLogger.setLogLevel(lDebug5);
        }

        Log(lInfo) << "Working Directory: " << getCWD() << endl;
//        ATExplorer atExplorer;

        //Set data.. if any
     	ATData* atData(nullptr);

        if(cli.dataRoot.isSet())
        {
            string value =cli.dataRoot.getValue();
            value = fixPathEnding(value);
		    Path dataPath(value);
	        Log(lInfo) << "Looking at data in folder: " << value;
            if(!folderExists(value))
            {
                throw(FileSystemException("The Folder: " + value + " don't exist!"));
            }

            atData = new ATIFData(dataPath);
		    atData->assignOnPopulateCallbacks(onStartingPopulating, onProgressPopulating, onFinishedPopulating);
			Log (lInfo) << "Starting populating";

		    const bool dummy(false);
		    atData->populate(dummy);
        }
        else
        {
            Log(lError) << "data root is not set..";
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
        Log(lInfo)  <<  "Application exiting..";
    }
	catch (TCLAP::ArgException &e)  // catch any exceptions
	{
    	Log(lError) << "Error: " << e.error();
    }
    catch(...)
    {
        Log(lError)<<"There was an unknown problem.."<<endl;
    }

    Log(lInfo)<< "atcli is done....";
	return 0;

}

#if defined(WIN32)
#pragma comment(lib, "dslFoundation.lib")
#pragma comment(lib, "atExplorerFoundation.lib")
#pragma comment(lib, "poco_foundation.lib")
#endif
