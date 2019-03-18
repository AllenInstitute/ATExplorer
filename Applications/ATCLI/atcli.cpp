#pragma hdrstop
#include "optionparser/ezOptionParser.h"
#include "dslStringList.h"
#include "dslUtils.h"
#include "dslException.h"
#include "dslLogger.h"
#include "dslStringUtils.h"
#include "atdata/atATIFData.h"
#include "dslLogger.h"
#include "atATEExceptions.h"
#include "atSession.h"
#include "atRibbon.h"

//---------------------------------------------------------------------------
using namespace std;
using namespace ez;
using namespace dsl;
using namespace at;

int setupAndParseOptions(ezOptionParser& opt, int argc, const char * argv[]);
void Usage(ezOptionParser& opt)
{
	std::string usage;
	opt.getUsage(usage);
	std::cout << usage;
};

//Arg1 -> AtData
void onStartingPopulating(void* arg1, void* arg2, void* arg3)
{
    Log(lInfo) << "Starting populating data..";
}

//Arg1 -> AtData
void onProgressPopulating(void* arg1, void* arg2, void* arg3)
{
    ATData* data = (ATData*)arg1;
    Log(lInfo) << "Progressing populating data: ";
    if(data)
    {
        Log(lInfo) << "Sections: " <<data->getNumberOfSections();
    }
}

//Arg1 -> AtData
void onFinishedPopulating(void* arg1, void* arg2, void* arg3)
{
    ATData* data = (ATData*)arg1;

    Log(lInfo) << "Finished populating data";
   	Log(lInfo) << data->getInfo();
}

void populate(ATData* data);
int main(int argc, const char * argv[])
{
    try
    {
        gLogger.logToConsole(true);
        ezOptionParser opt;
        int r = setupAndParseOptions(opt, argc, argv);

        OptionGroup* o = opt.get("-l");
	    string value;
        if(o)
        {
	        o->getString(value);
	        gLogger.setLogLevel(toLogLevel(toUpperCase(value)));
	        Log(lInfo) << "Current loglevel: " << toString(gLogger.getLogLevel());
        }

        Log(lDebug) << "Working Directory: " << getCWD() << endl;

        //Set data.. if any
     	ATData* atData(nullptr);
        o = opt.get("-d");

        if(o)
        {
	        o->getString(value);
	        Log(lInfo) << "Looking at data in folder: " << value;
		    Path dataPath(value);
            atData = new ATIFData(dataPath);
		    atData->assignOnPopulateCallbacks(onStartingPopulating, onProgressPopulating, onFinishedPopulating);
            populate(atData);
        }

    }
    catch(dsl::DSLException& ex)
    {
        Log(lError)<<"Application exception occurred: "<<ex.what()<<endl;
    }
    catch(...)
    {
        Log(lError)<<"There was an unknown problem.."<<endl;
    }

    Log(lInfo)<<"Application is exiting...";
	return 0;

}

int setupAndParseOptions(ezOptionParser& opt, int argc, const char * argv[])
{
	opt.overview 	= "atcli: command line interface to the ATExplorer backend.";
	opt.syntax 		= "atcli --dataroot /nas1/data/M33 [OPTIONS]";
	opt.example 	= "atcli --dataroot /nas1/data/M33 --pipeline stitch --sections 1-3,5\n\n";
	opt.footer 		= "ATExplorer CLI 0.1  Copyright (C) 2019 Allen Institute for Brain Science\nThis program is free and without warranty.\n";

	opt.add(
		"", // Default.
		0, // Required?
		0, // Number of args expected.
		0, // Delimiter if expecting multiple args.
		"Display help instructions.", // Help description.
		"-h",     // Flag token.
		"--help" // Flag token.
	);

	opt.add(
		"", // Default.
		0, // Required?
		1, // Number of args expected.
		0, // Delimiter if expecting multiple args.
		"Absolute path to root folder of input data (project) to process", // Help description.
		"-d",     // Flag token.
		"--dataroot" // Flag token.
	);

	opt.add(
		"Info", // Default.
		0, // Required?
		0, // Number of args expected.
		0, // Delimiter if expecting multiple args.
		"Set desired LogLevel (Error, Warning, Info, Debug1-Debug5",
		"-l",     // Flag token.
		"--loglevel" // Flag token.
	);

    //Parse command line options
    opt.parse(argc, argv);

    if (opt.isSet("-h"))
    {
        Usage(opt);
        return 1;
    }

    if (opt.lastArgs.size() < 2)
    {
        Usage(opt);
        return 1;
    }
    return 0;
}


void populate(ATData* atData)
{
    try
    {
        //!Populating the data object causes a scan of folders and files
        //!representing the data. No image data is loaded
        const bool dummy(false);
        atData->populate(dummy);

        //Print some information about ribbons and sections
        Log(lInfo) << "This is a "<<atData->getNumberOfRibbons()<<" ribbon(s) dataset";

        RibbonSP ribbon = atData->getFirstRibbon();
        while(ribbon)
        {
            Log(lInfo) << "There are "<<ribbon->getNumberOfSections()<<" sections in ribbon "<< ribbon->getAlias();
            ribbon = atData->getNextRibbon();
        }

        //Check Sessions and channels, i.e. actual data
        SessionSP session =  atData->getFirstSession();
        while(session)
        {
            Log(lInfo) << "Checking session " << session->getLabel();

            //Get Channels in session
            ChannelSP ch = session->getFirstChannel();
            while(ch)
            {
                Log(lInfo) << "Checking channel: " << ch->getLabel();
                RibbonSP ribbon = atData->getFirstRibbon();
                while(ribbon)
                {
                    SectionSP section = ribbon->getFirstSection();
                    //Loop through sections
                    while(section)
                    {
                        TilesSP tiles = section->getTiles(ch);
                        if(tiles)
                        {
                            Log(lDebug) << "There are " << tiles->count() << " tiles in section: " << section->id()<< ", channel \"" << tiles->getChannel().getLabel() << "\" in session: "<<session->getLabel()<<" on ribbon \"" << ribbon->getAlias() << "\"";
                        }
                        section = ribbon->getNextSection();
                    }

                    ribbon = atData->getNextRibbon();
                }
                ch = session->getNextChannel();
            }
            session = atData->getNextSession();
        }

        //Total number of tiles??
        long nrOfTiles = atData->getNumberOfTiles();
        Log(lInfo) << "Number of Tiles: " << nrOfTiles;
    }
    catch(const FileSystemException& e)
    {
        Log(lError) << "Exception: " << e.what();
        Log(lInfo) << "Application exiting..";
    }
    catch(...)
    {

    }
}

#pragma comment(lib, "dslFoundation.lib")
#pragma comment(lib, "atExplorerFoundation.lib")
#pragma comment(lib, "poco_foundation.lib")
