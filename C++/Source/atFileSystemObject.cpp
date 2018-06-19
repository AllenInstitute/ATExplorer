#pragma hdrstop
#include "atFileSystemObject.h"
#include <Poco/DirectoryIterator.h>
#include "dslLogger.h"
#include "atFileFolder.h"
//---------------------------------------------------------------------------

using namespace Poco;
using namespace dsl;

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



