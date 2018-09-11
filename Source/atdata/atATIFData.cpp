#pragma hdrstop
#include "atATIFData.h"
#include "dslLogger.h"
#include "dslConstants.h"
#include "atATDataUtils.h"
#include "atSession.h"
#include "atExceptions.h"
#include "atTile.h"
//---------------------------------------------------------------------------

namespace at
{

using namespace dsl;
using namespace std;
using namespace Poco;

ATIFData::ATIFData(const string& basePath, bool pop)
:
ATData(basePath),
mRibbonsFolderPath(joinPath(mBasePath.toString(),  (joinPath("raw", "data\\")))),
mRibbonsDataFolder(mRibbonsFolderPath),
mProcessedDataFolder(joinPath(mBasePath.toString(), "processed")),
mScriptsDataFolder(joinPath(mBasePath.toString(), 	"scripts"))
{
    if(pop)
    {
        populate();
    }
}

ATDataFileFormat ATIFData::getFileFormat()
{
    return mFileFormat;
}

ATIFData::ATIFData(const Path& basePath, bool pop)
:
ATData(basePath),
mRibbonsFolderPath(joinPath(mBasePath.toString(),  (joinPath("raw", "data\\")))),
mRibbonsDataFolder(mRibbonsFolderPath),
mProcessedDataFolder(joinPath(mBasePath.toString(), "processed")),
mScriptsDataFolder(joinPath(mBasePath.toString(), 	"scripts"))
{
    if(pop)
    {
        populate();
    }
}

bool ATIFData::populate()
{
    populateRibbons();
	populateSessions();
    return true;
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
	FolderInfo fInfo = mRibbonsDataFolder.scan();
    Log(lInfo) << "Found " <<fInfo.first << " folders and " << fInfo.second << " files";

    FileFolders ribbonFolders = getRibbonFolders();

	//Create ribbons
    for(int i = 0; i < ribbonFolders.count(); i++)
    {
        mRibbons.append(new Ribbon(i+1, ribbonFolders[i]->getLastPartOfPath()));
    }

    //For each ribbon, create sections
    //!For ATIF data, an assumption of the data
    //is that within each session, each channel contain the same # of Sections and frames
    for(int ribbonID = 0; ribbonID < ribbonFolders.count(); ribbonID++)
    {
        FileFolders sessionFolders = getSessionFolders(ribbonFolders[ribbonID]);

	    //Get first session folder
        FileFolder* sessionFolder = sessionFolders.getFirst();
        if(sessionFolder)
        {
			Log(lDebug) << "Checking session folder: "<<sessionFolder->toString()<<" for sections.";
            FileFolder* channelFolder = sessionFolder->getFirstSubFolder();
            if(channelFolder)
            {
                int nrOfSections = getNrOfSections(channelFolder);
                Log(lInfo) << "There are " << nrOfSections <<" sections in ribbon " << ribbonID + 1;

                //Make sure section container is empty
                mRibbons[ribbonID]->clear();

                //Append 'empty' sections
                for(int i = 0; i < nrOfSections; i++)
                {
                    Section* s = new Section(i, *(mRibbons[i]));
					mRibbons[ribbonID]->appendSection(s);
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

    //Each ribbon may go through several rounds (sessions) of imaging. Paths to individual frames
    //are captured in Sessions, Channel objects
    //Now, populate tiles
    for(int i = 0; i < ribbonFolders.count(); i++)
    {
        FileFolders sessionFolders = getSessionFolders(ribbonFolders[i]);

	    //Get first session folder (
        FileFolder* sessionFolder = sessionFolders.getFirst();
        while(sessionFolder)
        {
            Session* session = new Session(sessionFolder->toString());//, *(mRibbons[i]));
          	mSessions.push_back(session);

			Log(lDebug) << "Checking session folder: "<<sessionFolder->toString()<<" for channels.";
            FileFolder* channelFolder = sessionFolder->getFirstSubFolder();

            while(channelFolder)
            {
				Log(lDebug) << "Checking channel folder: "<<channelFolder->toString()<<" for tiles.";
                Channel* channel = new Channel(channelFolder->getLastPartOfPath(), session);
                session->appendChannel(channel);

                //The Session and Channel objects don't know anything about paths..
                const set<string>& files = channelFolder->getFiles("*.tif");
				Log(lDebug) << "Found "<<files.size()<<" tiles.";
                set<string>::const_iterator iter;
                iter = files.begin();
                while(iter != files.end())
                {
                	//Log(lDebug5) << "Found tile: " << *(iter);
                    Path p(*iter);
                    int secNr = getSectionID(p.getFileName()) + 1; //Section ID starts at 1, not 0;
                    int tileID = getTileID(p.getFileName()) + 1;

                    if(secNr == -1 || tileID == -1)
                    {
                        stringstream msg;
                        msg << "Failed reading sectionID or TileID for file: " <<p.getFileName();
                        throw(FileSystemException(msg.str()));
                    }

                    //A tile need to know which section it belongs to
                    Section* section = mRibbons[i]->getSection(secNr);
                	Tile* t = new Tile(*channel, *section, tileID, p);
                	channel->appendTile(t);

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

FileFolders	ATIFData::getSessionFolders(FileFolder* fldr)
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

FileFolders ATIFData::getChannelFolders(FileFolder* sessionFolder)
{
    Log(lInfo) << "Retrieving Channel Folders for session: " << sessionFolder->toString() << " on ribbon: " << sessionFolder->getParent()->toString();
    return sessionFolder->getSubFolders();
}

int ATIFData::getNumberOfRibbonFolders()
{
    //Check how many Ribbon folders that are present
    //The Ribbon folder is assumed to be under basepath/raw/data/

    FileFolders fldrs = mRibbonsDataFolder.getSubFolders();

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

FileFolder* ATIFData::getRibbonsDataFolder()
{
    return &mRibbonsDataFolder;
}

FileFolders ATIFData::getRibbonFolders()
{
    //First get the folder holding ribbon folder
	FileFolders ribbonFolders;
	FileFolders allSubFolders = mRibbonsDataFolder.getSubFolders();

	for(int i = 0; i < allSubFolders.count(); i++)
    {
        if(contains("Ribbon", allSubFolders[i]->toString()))
        {
	        ribbonFolders.append(allSubFolders[i]);
        }
    }

    return ribbonFolders;
}

FileFolder* ATIFData::getRibbonFolder(int fldr)
{
    FileFolders fldrs = mRibbonsDataFolder.getSubFolders();
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

    return NULL;
}



}
