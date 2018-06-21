#pragma hdrstop
#pragma argsused
#include "atIFData.h"
#include "dslLogger.h"
#include "atExceptions.h"

using namespace dsl;
using namespace at;
int main()
{
    //Setup logging
    LogOutput::mShowLogLevel = true;
    gLogger.logToConsole(true);

    try
    {
        Path dataPath("D:\\data\\M335503_Ai139_smallvol\\");
        ATIFData atData(dataPath, false);

        //!Populating the data object causes a scan of folders and files
        //!representing the data. No image data is loaded

        atData.populate();


        //Print some information
        Log(lInfo) << "This is a "<<atData.getNumberOfRibbons()<<" ribbons dataset";


    }
    catch(const FileSystemException& e)
    {
        Log(lError) << "Exception: " << e.what();
        Log(lInfo) << "Application exiting..";
    }
    catch(...)
    {

    }
	return 0;
}

#pragma comment(lib, "dslCommon.lib")
#pragma comment(lib, "atCore.lib")
#pragma comment(lib, "poco_foundation.lib")