#pragma hdrstop
#include "atFileFolder.h"
#include <Poco/DirectoryIterator.h>
#include "dslLogger.h"
//---------------------------------------------------------------------------

using namespace Poco;
using namespace dsl;

populateFolderStructure(FileFolder& path)
{
	DirectoryIterator end;
  	for (DirectoryIterator it(path.getPath()); it != end; ++it)
  	{

    	if(it->isDirectory())
    	{
            Log(lDebug5) << "Checking folder: "<<it->path();
            Path ffPath(it->path());
            FileFolder *ff = new FileFolder(ffPath, &path);
            path.addChild(ff);

            //Recursive call ------
      		populateFolderStructure(*ff);
    	}
  	}
}


bool FileSystemObject::isDirectory()
{
    return mPath.isDirectory();
}

string FileSystemObject::toString()
{
    return mPath.toString();
}

FileSystemObject::FileSystemObject(const Path& name, FileFolder *parent)
:
mPath(name), mParent(parent)
{
    if (parent)
    {
        parent->addChild(this);
    }
}

FileFolder::FileFolder(const Path& path, FileFolder* parent)
:
FileSystemObject(path, parent)
{
    //Parse base folder recursively, add folders (not file paths)
    populateFolderStructure(*this);
}

FileFolders FileFolder::getSubFolders()
{
	FileFolders fldrs;

    for(int i = 0; i < mFileFolderContent.size(); i++)
    {
        if(mFileFolderContent[i]->isDirectory())
        {
            FileSystemObject* fObj = mFileFolderContent[i];
            FileFolder* folder = dynamic_cast<FileFolder*>(fObj);
            fldrs.push_back(folder);
        }
    }
    return fldrs;
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



