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

int getNrOfSections(const set<string>& files);

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

    //For each ribbon, create sections
    //!For ATIF data, an assumption of the data
    //is that within each session, each channel contain the same # of Sections and frames
    for(int i = 0; i < ribbonFolders.count(); i++)
    {
        FileFolders sessionFolders = getSessionFolders(ribbonFolders[i]);
	    //Get first session folder
        FileFolder* sessionFolder = sessionFolders.getFirst();

        if(sessionFolder)
        {
			Log(lDebug) << "Checking session folder: "<<sessionFolder->toString()<<" for sections.";
            FileFolder* channelFolder = sessionFolder->getFirstSubFolder();
            if(channelFolder)
            {
				//Glob the tif files
                set<string> files;
			    Glob::glob(channelFolder->getPath().toString() + "*.tif", files);
                Log(lDebug) << "Found: " << files.size() << " tif files";
                int nrOfSections = getNrOfSections(files);
                Log(lInfo) << "There are:" << nrOfSections <<" sections in ribbon" << i+1;

                //Allocate ribbon sections
                mRibbons[i]->allocateSections(nrOfSections);
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


int getNrOfSections(const set<string>& files)
{
    //A simple algorithm to count sections..

    int count(0);
    int tempCount(0);

    //Find file with largest *S00#* pattern
 	for( set<string>::const_iterator iter = files.begin() ; iter != files.end() ; ++iter )
 	{
     	string fName(getFileNameNoPath((*iter)));
        StringList parts(fName,'_');
        //Find part starting with 'S', and not at the beginning of filename

        if(parts.size() > 3)
        {
            for(int i = 1; i < parts.size(); i++)
            {
                if(parts[i].size() == 5 && parts[i].at(0) == 'S')
                {
                    //Extract number
                    //Log(lDebug) << parts[i];
                    tempCount = toInt(parts[i].substr(1));
                    if(tempCount > count)
                    {
                        count = tempCount;
                    }
                }
            }
        }
        else
        {
            //Discard
        }
 	}
    return count + 1; //As first sectino is numbered S0000
}
}
