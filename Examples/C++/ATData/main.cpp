#pragma hdrstop
#pragma argsused
#include "atIFData.h"
#include "dslLogger.h"
#include "atExceptions.h"
using namespace dsl;

int main()
{
    //Setup logging
    LogOutput::mShowLogLevel = true;
    gLogger.logToConsole(true);

    try
    {
        ATIFData atData("D:\\data\\M335503_Ai139_smallvol\\", false);
//        ATIFData atData("D:\\data\\raw", false);

        //Print some information
        Log(lInfo) << "There are "<<atData.getNumberOfRibbonFolders()<<" ribbon folders";
        FileFolders ribbonFolders = atData.getRibbonFolders();

        for(int i = 0; i < ribbonFolders.size(); i++)
        {
            FileFolder* ribbonFolder = ribbonFolders[i];
            Log(lInfo) << "Checking ribbon folder: " << ribbonFolder->toString();
            FileFolders sessions = atData.getSessionFolders(ribbonFolder);
            for(int i = 0; i < sessions.size(); i++)
            {
                Log(lInfo) << "Checking session folder: " << sessions[i]->toString();

                //Check channels for each session..
                FileFolders channels = atData.getChannelFolders(sessions[i]);
                StringList chs = sessions[i]->getSubFoldersAsList();
                Log(lInfo) << "There are " << channels.size() <<" channels in session: " << '\n' << chs.asString();
            }
        }

    //Look into one single session

//    for(int ribbon = 0; ribbon < atData.getNumberOfRibbons(); ribbon++)
//    {
//        cout << "Ribbon #"<<ribbon<<" contain "<<atData.getRibbonFolder(ribbon).getNumberOfsections()<<" sections";
//    }

//    cout<<"This data set contains a total of "<<atData.getNumberOfTiles()<< " tiles";

//    if(!atData.validate())
//    {
//        Log(lError) << "This data do have problems. Exiting!";
//        return -1;
//    }
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