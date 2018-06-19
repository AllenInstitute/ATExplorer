#pragma hdrstop
#include "atFileFolder.h"
#include "atExceptions.h"
#include <Poco/DirectoryIterator.h>
#include "dslLogger.h"
#include "dslFileUtils.h"
//---------------------------------------------------------------------------

using namespace Poco;
using namespace dsl;
void populateFolderStructure(FileFolder& path);

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
    //Parse base folder recursively, add folders (not file paths)
    if(parent == NULL)
    {
    	populateFolderStructure(*this);
    }
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


FileFolder* FileFolder::getSubFolder(const Path& p)
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


void populateFolderStructure(FileFolder& path)
{
	DirectoryIterator end;
  	for (DirectoryIterator it(path.getPath()); it != end; ++it)
  	{

    	if(it->isDirectory())
    	{
            Path ffPath(it->path() + gPathSeparator);
//            Path ffPath(it->path());
            FileFolder *ff = new FileFolder(ffPath, &path);
	        Log(lDebug5) << "Adding child: "<<it->path();
            path.addChild(ff);

            //Recursive call ------
      		populateFolderStructure(*ff);
    	}
  	}
}

