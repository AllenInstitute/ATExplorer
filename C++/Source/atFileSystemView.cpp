#pragma hdrstop
#include "atFileSystemView.h"
//---------------------------------------------------------------------------

bool FileSystemBase::isDirectory()
{
    return mPath.isDirectory();
}

string FileSystemBase::toString()
{
    return mPath.toString();
}

FileSystemBase::FileSystemBase(const Path& name, FileFolder *parent)
:
mPath(name), mParent(parent)
{
    if (parent)
    {
        parent->addChild(this);
    }
}

FileFolder::FileFolder(const Path& name, FileFolder* parent)
:
FileSystemBase(name, parent)
{
    //Parse current folder, i.e. add child paths


}

bool FileFolder::isPresent(FileSystemBase* child)
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

void FileFolder::addChild(FileSystemBase* child)
{
    if(!isPresent(child))
    {
		mFileFolderContent.push_back(child);
    }
}


void FileFolder::removeChild(FileSystemBase* child)
{
//    if(!contain(child))
//    {
//		mFileFolderContent.push_back(child);
//    }
}



