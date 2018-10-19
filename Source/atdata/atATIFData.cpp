#pragma hdrstop
#include "atATIFData.h"
#include "dslLogger.h"
#include "dslConstants.h"
#include "atATDataUtils.h"
#include "atSession.h"
#include "atExceptions.h"
#include "atTile.h"
#include "atFileFolder.h"
#include "atRibbon.h"
#include "dslFileUtils.h"
//---------------------------------------------------------------------------

namespace at
{

using namespace dsl;
using namespace std;
using namespace Poco;

ATIFData::ATIFData(const string& basePath)
:
ATData(basePath),
mRibbonsFolderPath()
{
	setBasePath(basePath);
}

ATIFData::ATIFData(const Path& basePath)
:
ATData(basePath),
mRibbonsFolderPath(joinPath(mBasePath.toString(),  (joinPath("raw", "data\\"))))
{
	setBasePath(basePath.toString());
}

bool ATIFData::setBasePath(const string& bp)
{
    if(folderExists(bp))
    {
	    mBasePath = Path(bp);
        mRibbonsFolderPath 		= Path(joinPath(mBasePath.toString(),  (joinPath("raw", "data\\"))));
        if(folderExists(mRibbonsFolderPath.toString()))
        {
        	mRibbonsDataFolder 		= FileFolderSP(new FileFolder(mRibbonsFolderPath));
        }
        if(folderExists(joinPath(mBasePath.toString(), "processed")))
        {
        	mProcessedDataFolder 	= FileFolderSP(new FileFolder(joinPath(mBasePath.toString(), "processed")));
        }

        if(folderExists(joinPath(mBasePath.toString(), 	"scripts")))
        {
        	mScriptsDataFolder		= FileFolderSP(new FileFolder(joinPath(mBasePath.toString(), 	"scripts")));
        }
        return true;
    }
    else
    {
        Log(lWarning) << "Data folder: " << bp <<" don't exist";
        return false;
    }
}

StringList ATIFData::getStateTables()
{
    return mStateTables;
}

ATDataFileFormat ATIFData::getFileFormat()
{
    return mFileFormat;
}

void ATIFData::reset()
{
    ATData::reset();
    if(mRibbonsDataFolder)
    {
    	mRibbonsDataFolder->reset();
    }

    if(mProcessedDataFolder)
    {
    	mProcessedDataFolder->reset();
    }

    if(mScriptsDataFolder)
    {
    	mScriptsDataFolder->reset();
    }
}

int ATIFData::getNumberOfStateTables(bool refresh)
{
    if(refresh)
    {
        populateStateTables();
    }
	return mStateTables.count();
}

bool ATIFData::populate(const bool& timeToDie)
{
    mStopPopulation = &timeToDie;
    if(!timeToDie)
    {
        populateRibbons();
        populateSessions();
        populateStateTables();
    }
    return true;
}

bool ATIFData::populateStateTables()
{
	mStateTables.clear();
    //All raw data is in the ribbons datafolder, populate it first

    if(!mScriptsDataFolder)
    {
        return false;
    }

	set<string> files  = mScriptsDataFolder->getFiles("statetable_ribbon*");
    //Add statetables to StateTables container
    for(set<string>::iterator it = files.begin(); it != files.end(); it++)
    {
		mStateTables.append(getFileNameNoPath((*it)));
    }

    return true;
}

bool ATIFData::populateRibbons()
{
	Log(lDebug) << "Populating ATIF Data from folder: " << mBasePath.toString();

    //Check that root folder exists
    if(!mBasePath.isDirectory())
    {
        Log(lWarning) << mBasePath.toString() << " is not a valid ATData basepath";
        return false;
    }

    //All raw data is in the ribbons datafolder, populate it first
	FolderInfo fInfo = mRibbonsDataFolder->scan();
    Log(lInfo) << "Found " <<fInfo.NrOfFolders << " folders and " << fInfo.NrOfFiles << " files";

    if(onStartingPopulating)
    {
        onStartingPopulating(this, nullptr);
    }

    FileFolders ribbonFolders = getRibbonFolders();

    mRibbons.clear();
	//Create ribbons
    for(int i = 0; i < ribbonFolders.count(); i++)
    {
        mRibbons.append(RibbonSP(new Ribbon(i, ribbonFolders[i]->getLastPartOfPath())));

        if(onProgressPopulating)
        {
            onProgressPopulating(this, nullptr);
        }
    }

    //For each ribbon, create sections
    //!For ATIF data, an assumption of the data
    //is that within each session, each channel contain the same # of Sections and frames
    for(int ribbonID = 0; ribbonID < ribbonFolders.count(); ribbonID++)
    {
        FileFolders sessionFolders = getSessionFolders(ribbonFolders[ribbonID]);

	    //Get first session folder
        FileFolderSP sessionFolder = sessionFolders.getFirst();
        if(sessionFolder)
        {
			Log(lDebug) << "Checking session folder: "<<sessionFolder->toString()<<" for sections.";
            FileFolderSP channelFolder = sessionFolder->getFirstSubFolder();
            if(channelFolder)
            {
                int nrOfSections = getNrOfSections(channelFolder);
                Log(lInfo) << "There are " << nrOfSections <<" sections in ribbon " << ribbonID;

                //Make sure section container is empty
                mRibbons[ribbonID]->clear();

                //Append 'empty' sections
                for(int i = 0; i < nrOfSections; i++)
                {
                    SectionSP s = SectionSP(new Section(i, *(mRibbons[ribbonID])));
					mRibbons[ribbonID]->appendSection(s);

                    if(onProgressPopulating)
                    {
                        onProgressPopulating(this, nullptr);
                    }

                    if(*mStopPopulation == true)
                    {
                        return false;
                    }
                }
            }
            else
            {
                Log(lError) << "There are no channel folders!";
                //Throw
            }
        }
    }
    return true;
}

bool ATIFData::populateSessions()
{
    FileFolders ribbonFolders = getRibbonFolders();

    //Each ribbon may go through several rounds (sessions) of imaging. Paths to individual tiles
    //are captured in Sessions, Channel objects
    //Now, populate tiles
    int tileCount(0);

    for(int i = 0; i < ribbonFolders.count(); i++)
    {
        FileFolders sessionFolders = getSessionFolders(ribbonFolders[i]);

	    //Get first session folder (
        FileFolderSP sessionFolder = sessionFolders.getFirst();
        while(sessionFolder)
        {
            string sessionLabel(getLastFolderInPath(sessionFolder->toString()));
            SessionSP session(mSessions.getSession(sessionLabel));

            if(!session)
            {
            	session = SessionSP(new Session(sessionLabel));
	          	mSessions.append(session);
            }

			Log(lDebug) << "Checking session folder: "<<sessionFolder->toString()<<" for channels.";
            FileFolderSP channelFolder = sessionFolder->getFirstSubFolder();

            while(channelFolder)
            {
				Log(lDebug) << "Checking channel folder: "<<channelFolder->toString()<<" for tiles.";
                ChannelSP channel(session->getChannel(channelFolder->getLastPartOfPath()));

                if(!channel)
                {
	                channel = ChannelSP(new Channel(channelFolder->getLastPartOfPath(), *session));
                    session->appendChannel(channel);
                }

                //The Session and Channel objects don't know anything about paths..
                const set<string>& files = channelFolder->getFiles("*.tif");
				Log(lDebug) << "Found "<<files.size()<<" tiles.";

                set<string>::const_iterator iter;
                iter = files.begin();
                while(iter != files.end())
                {
                	//Log(lDebug5) << "Found tile: " << *(iter);
                    Path p(*iter);
                    int secNr = getSectionID(p.getFileName()); //Section ID starts at 1, not 0;
                    int tileID = getTileID(p.getFileName());

                    if(secNr == -1 || tileID == -1)
                    {
                        stringstream msg;
                        msg << "Failed reading sectionID or TileID for file: " <<p.getFileName();
                        throw(FileSystemException(msg.str()));
                    }

                    //A tile need to know which section it belongs to
                    SectionSP section = mRibbons[i]->getSection(secNr);
                    if(section)
                    {
                        TileSP t = TileSP(new Tile(*channel, *(section.get()), tileID, p));
                        Log(lDebug3) << "Adding tile: " << t->getPath().toString();
                        //Associate the tile with the section
                        section->addTile(t);
                        tileCount++;
                        if(onProgressPopulating)
                        {
                            if(tileCount % 1000 == 0)
                            {
                            	onProgressPopulating(this, nullptr);
                            }
                        }

                        if(*mStopPopulation == true)
                        {
                            return false;
                        }
                    }
                    else
                    {
                        Log(lError) << "Error processing filePath: " <<p.toString();
                    }

                    iter++;
                }

                channelFolder = sessionFolder->getNextSubFolder();
            }
            //Move to next session folder
            sessionFolder = sessionFolders.getNext();
        }
    }

    return true;
}

FileFolders	ATIFData::getSessionFolders(FileFolderSP fldr)
{
	FileFolders subFolders = fldr->getSubFolders();
	FileFolders sessionFolders;

	for(int i = 0; i < subFolders.count(); i++)
    {
        if(contains("session", subFolders[i]->toString()))
        {
        	sessionFolders.append(subFolders[i]);
        }
    }
    return sessionFolders;
}

FileFolders ATIFData::getChannelFolders(FileFolderSP sessionFolder)
{
//    Log(lInfo) << "Retrieving Channel Folders for session: " << sessionFolder->toString() << " on ribbon: " << sessionFolder->getParent()->toString();
    return sessionFolder->getSubFolders();
}

int ATIFData::getNumberOfRibbonFolders()
{
    //Check how many Ribbon folders that are present
    //The Ribbon folder is assumed to be under basepath/raw/data/

    FileFolders fldrs = mRibbonsDataFolder->getSubFolders();

    int count(0);
	for(int i = 0; i < fldrs.count(); i++)
    {
        if(contains("Ribbon", fldrs[i]->toString()))
        {
            count++;
        }
    }
    return count;
}

FileFolderSP ATIFData::getRibbonsDataFolder()
{
    return mRibbonsDataFolder;
}

FileFolders ATIFData::getRibbonFolders()
{
    //First get the folder holding ribbon folder
	FileFolders ribbonFolders;
	FileFolders allSubFolders = mRibbonsDataFolder->getSubFolders();

	for(int i = 0; i < allSubFolders.count(); i++)
    {
        if(contains("Ribbon", allSubFolders[i]->toString()))
        {
	        ribbonFolders.append(allSubFolders[i]);
        }
    }

    return ribbonFolders;
}

FileFolderSP ATIFData::getRibbonFolder(int fldr)
{
    FileFolders fldrs = mRibbonsDataFolder->getSubFolders();
    int count(0);

	for(int i = 0; i < fldrs.count(); i++)
    {
        if(contains("Ribbon", fldrs[i]->toString()))
        {
            count++;
        }
        if(count == fldr)
        {
            return fldrs[i];
        }
    }

    return FileFolderSP();
}

bool ATIFData::validate()
{
    //Do some simple validation
	//Number of tiles for a particular section, for a particular ribbon, are equal across channels(sessions)
//    Ribbon* ribbon = atData->getFirstRibbon();
//    //Check Sessions and channels, i.e. actual data
//    Session* session =  atData->getFirstSession();
//    while(session)
//    {
//        Log(lInfo) << "Checking session " << session->getLabel();
//        //Get Channels in session
//        Channel* chan = atData->getFirstChannel(session);
//        while(chan)
//        {
//            Log(lInfo) << "Checking channel: " << chan->getLabel();
//            Ribbon* ribbon = atData->getFirstRibbon();
//            while(ribbon)
//            {
//                Section* section = ribbon->getFirstSection();
//                //Loop through frames
//                while(section)
//                {
//                    Tiles& tiles = section->getTiles(*chan);
//                    Log(lInfo) << "There are " << tiles.count() << " tiles in section: " << section->id()<< " channel: " << chan->getLabel() << " on ribbon: " << ribbon->getAlias();
//                    section = ribbon->getNextSection();
//                }
//
//                ribbon = atData->getNextRibbon();
//            }
//            chan = atData->getNextChannel(session);
//        }
//        session = atData->getNextSession();
//    }
//
//

    return true;
}



}
