#pragma hdrstop
#pragma argsused
#include "atATIFData.h"
#include "dslLogger.h"
#include "atExceptions.h"
#include "atSession.h"
//#include "atATProjectItem.h"

using namespace dsl;
using namespace at;
int main()
{
    //Setup logging
    LogOutput::mShowLogLevel = true;
    gLogger.setLogLevel(lDebug3);
    gLogger.logToConsole(true);
    gLogger.logToFile("p:\\ATProjects\\MyLog.txt");

    try
    {
        Path dataPath("F:\\data\\M33\\");
        Path projectFilePath("P:\\ATProjects\\AFirstProject.atp");
//        ATProjectItem atProject("MyFirstProject");
//        atProject.open(projectFilePath.toString());


        ATData *atData = new ATIFData(dataPath, false);

        //!Don't allow two items with the same name.. print error and don't
        //add

//        atProject.addProjectObject(atData);
//        atProject.save();



//        //!Populating the data object causes a scan of folders and files
//        //!representing the data. No image data is loaded
        atData->populate();

        //Print some information about ribbons and sections
        Log(lInfo) << "This is a "<<atData->getNumberOfRibbons()<<" ribbons dataset";

	    Ribbon* ribbon = atData->getFirstRibbon();
        while(ribbon)
        {
	        Log(lInfo) << "There are "<<ribbon->sectionCount()<<" sections in ribbon "<< ribbon->getAlias();
            ribbon = atData->getNextRibbon();
        }

        //Check Sessions and channels, i.e. actual data
        Session* session =  atData->getFirstSession();
        while(session)
        {
        	Log(lInfo) << "Checking session " << session->getLabel();
            //Get Channels in session
            Channel* chan = atData->getFirstChannel(session);
            while(chan)
            {
              	Log(lInfo) << "Checking channel: " << chan->getLabel();
            	Ribbon* ribbon = atData->getFirstRibbon();
                while(ribbon)
                {
                    Section* section = ribbon->getFirstSection();
                    //Loop through frames
                    while(section)
                    {
                        Tiles& tiles = section->getTiles(*chan);
                        Log(lInfo) << "There are " << tiles.count() << " tiles in section: " << section->id()<< ", channel \"" << chan->getLabel() << "\" on ribbon \"" << ribbon->getAlias() << "\"";
                        section = ribbon->getNextSection();
                    }

		            ribbon = atData->getNextRibbon();
                }
                chan = atData->getNextChannel(session);
            }
            session = atData->getNextSession();
        }


//        atProject.save();
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

#pragma comment(lib, "atExplorerFoundation")
#pragma comment(lib, "dslFoundation")
#pragma comment(lib, "poco_foundation")
#pragma comment(lib, "tinyxml2")
