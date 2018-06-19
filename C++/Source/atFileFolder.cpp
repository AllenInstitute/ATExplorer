#pragma hdrstop
#include "atFileFolder.h"
#include <Poco/DirectoryIterator.h>
#include "dslLogger.h"
//---------------------------------------------------------------------------

using namespace Poco;
using namespace dsl;
void populateFolderStructure(FileFolder& path);

FileFolder::FileFolder(const Path& path, FileFolder* parent)
:
FileSystemObject(path, parent)
{
    //Parse base folder recursively, add folders (not file paths)
    if(parent == NULL)
    {
    	populateFolderStructure(*this);
    }
}

FileFolders FileFolder::getSubFolders()
{
    int count(mFileFolderContent.size());
	FileFolders subFolders;
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
            Path ffPath(it->path() + "\\");
//            Path ffPath(it->path());
            FileFolder *ff = new FileFolder(ffPath, &path);
	        Log(lDebug5) << "Adding child: "<<it->path();
            path.addChild(ff);

            //Recursive call ------
      		populateFolderStructure(*ff);
    	}
  	}
}

