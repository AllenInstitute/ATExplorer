#pragma hdrstop
#include "atIFData.h"
#include "dslLogger.h"
#include "Poco/Glob.h"
#include "dslConstants.h"
#include <set>
//---------------------------------------------------------------------------

using namespace dsl;
using namespace std;
using namespace Poco;

ATIFData::ATIFData(const Path& p, bool val)
:
ATData(p),
ribbonFolderSubPath(joinPath("raw", "data\\"))
{
    if(val)
    {
        validate();
    }
}

bool ATIFData::validate()
{
	Log(lDebug) << "Validating AT Data in folder: " << mBasePath.toString();

    //Check that root folder exists
    if(!mBasePath.isDirectory())
    {
        Log(lWarning) << mBasePath.toString() << " is not a valid ATData basepath";
        return false;
    }

    //Validate Ribbon folder in base folder
    int nrOfRibbonFolders(getNumberOfRibbonFolders());
    for(int i = 0 ; i < nrOfRibbonFolders; i++)
    {
        //Check number of sessions
        FileFolder* ribbonFolder = getRibbonFolder(i+1);
        if(ribbonFolder)
        {
            Log(lInfo) << "Checking Ribbon folder: " << ribbonFolder->toString();
        }

	    //Could spawn some threads for this...
    }

    return true;
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
    //Ribbon folder is assumed to be under basepath/raw/data/

    Path subPath(joinPath("raw", "data\\"));
    FileFolder* fldr = mBasePath.getSubFolder(subPath);

    if(!fldr)
    {
        Log(lError) << "Failed to get folder containing ribbon data";
        return -1;
    }

    FileFolders fldrs = fldr->getSubFolders();

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
    return mBasePath.getSubFolder(ribbonFolderSubPath);
}

FileFolders ATIFData::getRibbonFolders()
{
    //First get the folder holding ribbon folder
	FileFolders ribbonFolders;
    FileFolder* ribbonFolder = getRibbonsDataFolder();

    if(!ribbonFolder)
    {
        Log(lError) << "Failed to get folder containing ribbon data";
        return ribbonFolders;
    }

	FileFolders allSubFolders = ribbonFolder->getSubFolders();

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
    FileFolders fldrs = mBasePath.getSubFolders();
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
