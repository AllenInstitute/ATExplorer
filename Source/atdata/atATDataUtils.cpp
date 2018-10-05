#pragma hdrstop
#include "atATDataUtils.h"
#include "atExceptions.h"
#include "atFileFolder.h"
#include "dslLogger.h"
#include "Poco/Glob.h"
//---------------------------------------------------------------------------

namespace at
{

using namespace dsl;
using namespace Poco;


int getSectionID(const string& filePath)
{
    string fName(getFileNameNoPath(filePath));
    StringList parts(fName,'_');

    //Find the part that is starting with 'S', and not at the beginning of filename
    if(parts.size() > 3)
    {
        for(int i = 1; i < parts.size(); i++)
        {
            if(parts[i].size() == 5 && parts[i].at(0) == 'S')
            {
                //Extract number
                //Log(lDebug) << parts[i];
                return toInt(parts[i].substr(1));
            }
        }
    }
    else
    {
        //This is something else.. Discard
        return -1;
    }
}

int getTileID(const string& filePath)
{
    string fName(getFileNameNoPath(filePath));
    StringList parts(fName,'_');

    //Find the part that is starting with 'F', and not at the beginning of filename
    if(parts.size() > 3)
    {
        for(int i = 1; i < parts.size(); i++)
        {
            if(parts[i].size() == 5 && parts[i].at(0) == 'F')
            {
                //Extract number
                //Log(lDebug) << parts[i];
                return toInt(parts[i].substr(1));
            }
        }
    }
    else
    {
        //This is something else.. Discard
        return -1;
    }
}

int getNrOfSections(FileFolderSP channelFolder)
{
    if(!channelFolder)
    {
        throw(FileSystemException("channelFolder is NULL"));
    }

    //Glob tif files
    set<string> files;

    string path(channelFolder->getPath().toString());

    Glob::glob(path + "*.tif", files);
    Log(lDebug) << "Found: " << files.size() << " tif files";

    //The files set holds files from a "channel folder"
    //A simple algorithm to count sections..

    int count(0);
    int tempCount(0);

    //Find file with largest *S???#* pattern, e.g. S0045
 	for(set<string>::const_iterator iter = files.begin() ; iter != files.end() ; ++iter)
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
            //This is something else.. Discard
        }
 	}
    return count + 1; //As first section is numbered S0000
}

}
