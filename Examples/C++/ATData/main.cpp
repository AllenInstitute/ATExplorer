#pragma hdrstop
#pragma argsused
#include "atIFData.h"
#include "dslLogger.h"
using namespace dsl;

int main()
{
    //Setup logging
    LogOutput::mShowLogLevel = true;
    gLogger.logToConsole(true);

    ATIFData myData("D:\\data\\raw\\data\\");

    //Print some information
    cout<< "Data for "<<myData.getNumberOfRibbons()<<" ribbons";

//    for(int ribbon = 0; ribbon < myData.getNumberOfRibbons(); ribbon++)
//    {
//        cout << "Ribbon #"<<ribbon<<" contain "<<myData.getRibbonFolder(ribbon).getNumberOfsections()<<" sections";
//    }

//    cout<<"This data set contains a total of "<<myData.getNumberOfTiles()<< " tiles";

    if(!myData.validate())
    {
        Log(lError) << "This data do have problems. Exiting!";
        return -1;
    }


	return 0;
}

#pragma comment(lib, "dslCommon.lib")
#pragma comment(lib, "atCore.lib")
#pragma comment(lib, "poco_foundation.lib")