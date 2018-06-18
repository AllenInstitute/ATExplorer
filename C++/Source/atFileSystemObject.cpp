#pragma hdrstop
#include "atFileSystemObject.h"
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



