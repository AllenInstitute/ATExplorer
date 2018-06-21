#pragma hdrstop
#include "atIFData.h"
#include "dslLogger.h"
#include "Poco/Glob.h"
#include "dslConstants.h"
#include <set>
//---------------------------------------------------------------------------

namespace at
{
using namespace dsl;
using namespace std;
using namespace Poco;

ATIFData::ATIFData(const Path& p, bool pop)
:
mBasePath(p),
mRibbonsFolderPath(joinPath(mBasePath.toString(),  (joinPath("raw", "data\\")))),
mRibbonsDataFolder(mRibbonsFolderPath),
mProcessedDataFolder(joinPath(mBasePath.toString(), "processed")),
mScriptsDataFolder(joinPath(mBasePath.toString(), "scripts"))
{
    if(pop)
    {
        populate();
    }
}

bool ATIFData::populate()
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
    for(int i = 0; i < ribbonFolders.size(); i++)
    {
        mRibbons.push_back(new Ribbon(i, ribbonFolders[i]->getLastPartOfPath()));
    }


    return true;
}

bool ATIFData::validate()
{

    return false;
}

FileFolders	ATIFData::getSessionFolders(FileFolder* fldr)
{
	FileFolders subFolders = fldr->getSubFolders();
	FileFolders sessionFolders;

	for(int i = 0; i < subFolders.size(); i++)
    {
        if(contains("session", subFolders[i]->toString()))
        {
        	sessionFolders.push_back(subFolders[i]);
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
	for(int i = 0; i < fldrs.size(); i++)
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

	for(int i = 0; i < allSubFolders.size(); i++)
    {
        if(contains("Ribbon", allSubFolders[i]->toString()))
        {
	        ribbonFolders.push_back(allSubFolders[i]);
        }
    }

    return ribbonFolders;
}

FileFolder* ATIFData::getRibbonFolder(int fldr)
{
    FileFolders fldrs = mRibbonsDataFolder.getSubFolders();
    int count(0);

	for(int i = 0; i < fldrs.size(); i++)
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
