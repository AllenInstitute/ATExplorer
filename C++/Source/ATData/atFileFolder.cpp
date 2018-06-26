#pragma hdrstop
#include "atFileFolder.h"
#include "atExceptions.h"
#include <Poco/DirectoryIterator.h>
#include "dslLogger.h"
#include "dslFileUtils.h"
//---------------------------------------------------------------------------

namespace at
{

using namespace Poco;
using namespace dsl;

FolderInfo populateFolderStructure(FileFolder& path);

FileFolder::FileFolder(const Path& path, FileFolder* parent)
:
FileSystemObject(path, parent)
{
    Poco::File dir(path);
    if(!dir.exists())
    {
        stringstream msg;
        msg << "The path: " << path.toString() <<" is not an existing directory.";
        throw(FileSystemException(msg));
    }

    if (parent)
    {
        parent->addSubFolder(this);
    }
}

FileFolder::~FileFolder()
{}

FolderInfo FileFolder::scan()
{
  	return populateFolderStructure(*this);
}

string FileFolder::getLastPartOfPath()
{
    return mPath[mPath.depth() - 1];
}

//Return part n of the path
string FileFolder::directoryName(int n)
{
    if(n < mPath.depth())
    {
        return mPath[n];
    }
    else
    {
        return "";
    }
}

FileFolder* FileFolder::getFirstSubFolder()
{
    return mSubFolders.getFirst();
}

FileFolder* FileFolder::getNextSubFolder()
{
    return mSubFolders.getNext();
}

FileFolder* FileFolder::getSubFolder(const Path& p)
{
    Path subPath(p);
    FileFolder* subfolder(NULL);

    for(int i = 0; i < mSubFolders.size(); i++)
    {
        Path thisPath(mPath);
        FileFolder* subFldr = dynamic_cast<FileFolder*>(mSubFolders[i]);

        thisPath.pushDirectory(subPath.directory(0));
        if(subFldr && subFldr->toString() == thisPath.toString())
        {
            //If matched and path is deeper, return recursive call to getSubFolder
            if(subPath.depth() > 1)
            {
                subPath.popFrontDirectory();
                return subFldr->getSubFolder(subPath);
            }
            else
            {
                return subFldr;
            }
        }
    }
    return NULL;
}

FileFolders FileFolder::getSubFolders(const Path& subPath)
{
    //if a subPath is provided, return subfolders of that..

	FileFolders subFolders;
    int count(mSubFolders.size());
    if(!count)
    {
        return subFolders;
    }

    for(int i = 0; i < count; i++)
    {
        //Checking
        //Log(lDebug) << "Checking: " << mSubFolders[i]->toString();
        if(mSubFolders[i]->isDirectory())
        {
            FileSystemObject* fObj = mSubFolders[i];
            FileFolder* folder = dynamic_cast<FileFolder*>(fObj);
            subFolders.push_back(folder);
        }
    }
    return subFolders;
}

StringList FileFolder::getSubFoldersAsList()
{
    StringList li;
    FileFolders subs = getSubFolders();

    for(int i = 0; i < subs.size(); i++)
    {
        StringList parts(subs[i]->toString(), '\\');
        li.append(parts[parts.size() - 1]);
    }
    return li;
}

bool FileFolder::isPresent(FileSystemObject* child)
{
    for(int i = 0; i < mSubFolders.size(); i++)
    {
        if(mSubFolders[i] == child)
        {
            return true;
        }
    }
    return false;
}

const set<string>& FileFolder::getFiles(const string& globPattern)
{
    mFiles.clear();
    string fullPath(getPath().toString());

    //Get all files in folder with extension ext
    Glob::glob(joinPath(fullPath, globPattern), mFiles, Glob::GLOB_CASELESS);
    return mFiles;
}

void FileFolder::addSubFolder(FileFolder* child)
{
    if(!isPresent(child))
    {
		mSubFolders.push_back(child);
    }
}

void FileFolder::removeChild(FileSystemObject* child)
{
//    if(!contain(child))
//    {
//		mSubFolders.push_back(child);
//    }
}


FolderInfo populateFolderStructure(FileFolder& folder)
{
    FolderInfo info(0, 0);
	DirectoryIterator end;
    //Log(lDebug3) << "Checking folder: " << folder.getPath().toString();
  	for (DirectoryIterator it(folder.getPath()); it != end; ++it)
  	{

    	if(it->isDirectory())
    	{
            //Found a folder
            info.first++;
            Path ffPath(it->path() + gPathSeparator);

            FileFolder *ff = new FileFolder(ffPath, &folder);
	        Log(lDebug5) << "Adding child: "<<it->path();
            //folder.addSubFolder(ff);

            //Recursive call ------
      		FolderInfo i = populateFolderStructure(*ff);
            info.first  += i.first;
            info.second += i.second;
    	}
        else if(it->isFile())
        {
            info.second++;
        }
  	}
    return info;
}

}
