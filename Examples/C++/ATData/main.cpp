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

    ATIFData myData("D:\\data\\raw\\data\\", false);

    //Print some information
    Log(lInfo) << "There are "<<myData.getNumberOfRibbonFolders()<<" ribbons";
    FileFolders ribbonFolders = myData.getRibbonFolders();

    for(int i = 0; i < ribbonFolders.size(); i++)
    {
        Log(lInfo) << "Checking ribbon folder: " << ribbonFolders[i]->toString();
        FileFolders sessions = myData.getSessionFolders(i + 1);
        for(int i = 0; i < sessions.size(); i++)
        {
	        Log(lInfo) << "Checking session folder: " << sessions[i]->toString();

			//Check channels for each session..
            FileFolders channels = myData.getChannelFolders(sessions[i]);
            StringList chs = sessions[i]->getSubFoldersAsList();
            Log(lInfo) << "There are " << channels.size() <<" channels in session: " << '\n' << chs.asString();
        }
    }

    //Look into one single session

//    for(int ribbon = 0; ribbon < myData.getNumberOfRibbons(); ribbon++)
//    {
//        cout << "Ribbon #"<<ribbon<<" contain "<<myData.getRibbonFolder(ribbon).getNumberOfsections()<<" sections";
//    }

//    cout<<"This data set contains a total of "<<myData.getNumberOfTiles()<< " tiles";

//    if(!myData.validate())
//    {
//        Log(lError) << "This data do have problems. Exiting!";
//        return -1;
//    }

	return 0;
}

#pragma comment(lib, "dslCommon.lib")
#pragma comment(lib, "atCore.lib")
#pragma comment(lib, "poco_foundation.lib")