#pragma hdrstop
#pragma argsused
#include "atIFData.h"
#include "dslLogger.h"
#include "atExceptions.h"
#include "atSession.h"

using namespace dsl;
using namespace at;
int main()
{
    //Setup logging
    LogOutput::mShowLogLevel = true;
    gLogger.logToConsole(true);

//    //create tiles
//    list<Tile*> tiles;
//
//    Ribbon aRibbon(1, "Ribbon0001");
//    Section sec(1, aRibbon);
//    Session session1(1);
//    Session session2(2);
//
//    Channel dapiChannel1(session1, "DAPI");
//    Channel dapiChannel2(session2, "DAPI");
//    int tileCount(1000000);
//
//    for(int i = 0; i < tileCount; i++)
//    {
//        Tile* aTile = new Tile(i, sec, dapiChannel1);
//
//        tiles.push_back(aTile);
//    }

    try
    {
        Path dataPath("D:\\data\\M335503_Ai139_smallvol\\");
        ATData *atData = new ATIFData(dataPath, false);

        //!Populating the data object causes a scan of folders and files
        //!representing the data. No image data is loaded
        atData->populate();

        //Print some information
        Log(lInfo) << "This is a "<<atData->getNumberOfRibbons()<<" ribbons dataset";

		int ribbonID(1);
        if(atData->getNumberOfRibbons())
        {
            Ribbon* ribbon = atData->getRibbon(1);
            if(!ribbon)
            {
                throw("No such ribbon...");
            }

	        Log(lInfo) << "There are "<<ribbon->sectionCount()<<" sections in ribbon "<< ribbonID;

            Section* section = ribbon->getFirstSection();

            //Loop through frames
            while(section)
            {
                int nrOfTiles = section->getNumberOfTiles();
                Log(lInfo) << "There are " << nrOfTiles << " in section: " << section->id();
            };
        }



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