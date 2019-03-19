#pragma hdrstop
#include "atFileFolder.h"
#include "atATEExceptions.h"
#include "Poco/DirectoryIterator.h"
#include "Poco/GLob.h"
#include "dslLogger.h"
#include "dslFileUtils.h"
//---------------------------------------------------------------------------

namespace at
{

using namespace Poco;
using namespace dsl;

FolderInfo populateFolderStructure(FileFolderSP path);

FileFolder::FileFolder(const Path& path, FileFolderSP parent)
:
FileSystemObject(path)
{
    Poco::File dir(path);
    if(!dir.exists())
    {
        stringstream msg;
        msg << "The path: " << path.toString() <<" is not an existing directory.";
        Log(lError) << msg.str();
        throw(FileSystemException(msg));
    }

//    if (parent)                           `
//    {
//        parent->addSubFolder(shared_from_this());
//    }
}

FileFolder::~FileFolder()
{
    Log(lDebug) << "DTOR FileFolder" << mPath.toString();
}

void FileFolder::reset()
{
    mSubFolders.reset();
    mFiles.clear();
}

FolderInfo FileFolder::scan()
{
	mFolderInfo = populateFolderStructure(shared_from_this());
  	return mFolderInfo;
}

FolderInfo FileFolder::getFolderInfo()
{
    return mFolderInfo;
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

FileFolderSP FileFolder::getFirstSubFolder()
{
    return mSubFolders.getFirst();
}

FileFolderSP FileFolder::getNextSubFolder()
{
    return mSubFolders.getNext();
}

FileFolderSP FileFolder::getSubFolder(const Path& p)
{
    Path subPath(p);
    FileFolderSP subfolder();

    for(int i = 0; i < mSubFolders.count(); i++)
    {
        Path thisPath(mPath);
        FileFolderSP subFldr = (mSubFolders[i]);

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
    return FileFolderSP();
}

FileFolders FileFolder::getSubFolders(const Path& subPath)
{
    //if a subPath is provided, return subfolders of that..
	FileFolders subFolders;
    int count(mSubFolders.count());
    if(!count)
    {
        return subFolders;
    }

    for(int i = 0; i < count; i++)
    {
        //Log(lDebug) << "Checking: " << mSubFolders[i]->toString();
        if(mSubFolders[i]->isDirectory())
        {
            FileFolderSP folder = mSubFolders[i];
            subFolders.append(folder);
        }
    }
    return subFolders;
}

StringList FileFolder::getSubFoldersAsList()
{
    StringList li;
    FileFolders subs = getSubFolders();

    for(int i = 0; i < subs.count(); i++)
    {
        StringList parts(subs[i]->toString(), '\\');
        li.append(parts[parts.count() - 1]);
    }
    return li;
}

bool FileFolder::isPresent(FileSystemObject* child)
{
    for(int i = 0; i < mSubFolders.count(); i++)
    {
        if(mSubFolders[i].get() == child)
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

void FileFolder::addSubFolder(FileFolderSP child)
{
    if(!isPresent(child.get()))
    {
		mSubFolders.append(child);
    }
}

bool FileFolder::removeChild(FileSystemObject* child)
{
    return false;
}

FolderInfo populateFolderStructure(FileFolderSP folder)
{
    FolderInfo info(0, 0);
	DirectoryIterator end;
    //Log(lDebug3) << "Checking folder: " << folder.getPath().toString();
  	for (DirectoryIterator it(folder->getPath()); it != end; ++it)
  	{
    	if(it->isDirectory())
    	{
            //Found a folder
            info.NrOfFolders++;
            Path ffPath(it->path() + gPathSeparator);
            FileFolderSP ff (new FileFolder(ffPath));

            folder->addSubFolder(ff);
	        Log(lDebug5) << "Adding child: "<<it->path();

            //Recursive call ------
      		FolderInfo i = populateFolderStructure(ff);
            info.NrOfFolders  += i.NrOfFolders;
            info.NrOfFiles += i.NrOfFiles;
    	}
        else if(it->isFile())
        {
            //Check extension
            string p(it->path());
            if(getFileExtension(p) == "tif")
            {
            	info.NrOfFiles++;
            }
        }
  	}
    return info;
}

}
