#pragma hdrstop
#include "atFileFolder.h"
#include "atExceptions.h"
#include <Poco/DirectoryIterator.h>
#include "dslLogger.h"
#include "dslFileUtils.h"
//---------------------------------------------------------------------------

using namespace Poco;
using namespace dsl;

namespace at
{
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

shared_ptr<FileFolder> FileFolder::getSubFolder(const Path& p)
{
    Path subPath(p);
    FileFolder* subfolder(NULL);

    for(int i = 0; i < mFileFolderContent.size(); i++)
    {
        Path thisPath(mPath);
        FileFolder* subFldr = dynamic_cast<FileFolder*>(mFileFolderContent[i]);

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
                return shared_ptr<FileFolder>(subFldr);
            }
        }
    }
    return shared_ptr<FileFolder>();
}

FileFolders FileFolder::getSubFolders(const Path& subPath)
{
    //if a subPath is provided, return subfolders of that..

	FileFolders subFolders;
    int count(mFileFolderContent.size());
    if(!count)
    {
        return subFolders;
    }

    for(int i = 0; i < count; i++)
    {
        //Checking
        //Log(lDebug) << "Checking: " << mFileFolderContent[i]->toString();
        if(mFileFolderContent[i]->isDirectory())
        {
            FileSystemObject* fObj = mFileFolderContent[i];
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
    for(int i = 0; i < mFileFolderContent.size(); i++)
    {
        if(mFileFolderContent[i] == child)
        {
            return true;
        }
    }
    return false;
}

void FileFolder::addChild(FileSystemObject* child)
{
    if(!isPresent(child))
    {
		mFileFolderContent.push_back(child);
    }
}


void FileFolder::removeChild(FileSystemObject* child)
{
//    if(!contain(child))
//    {
//		mFileFolderContent.push_back(child);
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
            folder.addChild(ff);

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
