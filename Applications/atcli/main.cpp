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

int main(int argc, const char * argv[])
{
    try
    {

        //The ATCore ctor parses some supplied arguments, such as loglevel
		ATCore atCore(argc, argv);
        gLogger.logToConsole(atCore.CLI.consolelogs.getValue());

        //if no options are set, print usage
        if(atCore.CLI.numberofArgsSet() == 0)
        {
			//atCore.CLI.cmdLine.add("--usage");
            atCore.CLI.showUsage();
            exit(0);
        }

        //When getting info regarding raw data
	    if(atCore.CLI.dataroot.isSet())
    	{
            if(!folderExists(atCore.CLI.dataroot.getValue()))
            {
                stringstream msg;
                msg << "The data folder: "<< atCore.CLI.dataroot.getValue() << " don't exist. Bailing..";
                throw (FileSystemException(msg.str()));
            }
        	atCore.populateData();

            //Check if no other flag is set, print information
            if(!atCore.CLI.datainfo.isSet() && !atCore.CLI.printjson.isSet() )
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
        Log(lError)<<"Application exception occurred: "<<ex.what()<<endl;
    }
    catch(const FileSystemException& e)
    {
        Log(lError) << "Exception: " << e.what();
    }
	catch (TCLAP::ArgException &e)  // catch any exceptions
	{
    	Log(lError) << "Error: " << e.error();
    }
    catch(...)
    {
        Log(lError)<<"There was an unknown problem.."<<endl;
    }

    Log(lInfo)<< "atcli is exiting..";
	return 0;
}

#if defined(WIN32)
#pragma comment(lib, "dslFoundation.lib")
#pragma comment(lib, "atExplorerFoundation.lib")
#pragma comment(lib, "poco_foundation.lib")
#endif
