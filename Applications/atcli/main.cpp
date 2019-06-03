#pragma hdrstop
#include "dslUtils.h"
#include "dslFileUtils.h"
#include "dslLogger.h"
#include "atcore_class.h"
#include "atATEExceptions.h"
#include "dslException.h"
#include "atRibbon.h"
//---------------------------------------------------------------------------
using namespace std;
using namespace dsl;
using namespace at;
using namespace TCLAP;

string gATcliVersion = "0.5.1";

int main(int argc, const char * argv[])
{
    try
    {
        //The ATCore ctor parses some supplied arguments, such as loglevel
		ATCore atCore(argc, argv, gATcliVersion);
        gLogger.logToConsole(atCore.CLI.consolelogs.getValue());

        //if no options are set, print usage
        if(atCore.CLI.numberofArgsSet() == 0)
        {
			//atCore.CLI.cmdLine.add("--usage");
            atCore.CLI.showUsage();
            exit(0);
        }

        //When getting info regarding raw data
	    if(atCore.CLI.data.isSet())
    	{
            if(!folderExists(atCore.CLI.data.getValue()))
            {
                stringstream msg;
                msg << "The data folder: "<< atCore.CLI.data.getValue() << " don't exist. Bailing..";
                throw (FileSystemException(msg.str()));
            }

        	atCore.populateData();

            //Check flags
            if(atCore.CLI.datasummary.isSet())
            {
                cout << atCore.IFData.getSummaryJSON();
            }
            else
            {
                cout << atCore.IFData.getInfoJSON();
            }
        }

//        if(atCore.CLI.getstacknames.isSet())
//        {
//        	if(!atCore.CLI.project.isSet())
//            {
//	            atCore.CLI.showUsage();
//                exit(0);
//            }
//
//            string owner(atCore.getOwner());
//            string project(atCore.CLI.project.getValue());
//            clog << "Get stacknames for owner: '" << owner << "' and project: '" << project << "'";
//            cout << atCore.mATExplorer.RenderClient.StackDataAPI.getStacksForProject(owner, project);
//        }
//
//        else if(atCore.CLI.deletestack.isSet())
//        {
//            //User must supply renderproject and optionally owner
//        }
//
//        if(atCore.CLI.deletestacks.isSet())
//        {
//            //User must supply renderproject and optionally owner
//			if(!atCore.CLI.project.isSet())
//            {
//	            atCore.CLI.showUsage();
//                exit(0);
//            }
//
//            string owner(atCore.getOwner());
//            string project(atCore.CLI.project.getValue());
//            Log(lDebug) << "Delete stacks for owner: '" << owner << "' in project: '" << project << "'";
//
//            StringList stacks = atCore.mATExplorer.RenderClient.StackDataAPI.getStacksForProject(owner, project);
//            for(int i = 0; i < stacks.count(); i++)
//            {
//                string stack(stacks[i]);
//                Log(lDebug) << "Deleting stack: " << stack;
//                char confirm;
//                cout << "Confirm delettion of stack! (y/n)";
//                cin >> confirm;
//                if(confirm == 'y')
//                {
//		            cout << atCore.mATExplorer.RenderClient.StackDataAPI.deleteStack(owner, project, stack);
//                }
//                else
//                {
//                    Log(lInfo) << "The stack: " << stack << " was not deleted";
//
//                }
//            }
//        }
    }
    catch(dsl::DSLException& ex)
    {
        Log(lError) << "Error: "<<ex.what() << endl;
    }
    catch(const FileSystemException& e)
    {
        Log(lError) << "Errot: " << e.what() << endl;
    }
	catch (TCLAP::ArgException &e)  // catch any exceptions
	{
    	Log(lError) << "Error: " << e.error() << endl ;
    }
    catch(...)
    {
        Log(lError)<<"Error: There was an unknown problem."<<endl;
    }

    Log(lInfo)<< "atcli is exiting..";
	return 0;
}

#if defined(WIN32)
	#pragma comment(lib, "dslFoundation.lib")
	#pragma comment(lib, "atExplorerFoundation.lib")
	#pragma comment(lib, "poco_foundation.lib")
#endif
