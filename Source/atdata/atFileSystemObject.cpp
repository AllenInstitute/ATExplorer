#pragma hdrstop
#include "atFileSystemObject.h"
#include <Poco/DirectoryIterator.h>
#include "dslLogger.h"
#include "atFileFolder.h"
//---------------------------------------------------------------------------

using namespace Poco;
using namespace dsl;

namespace at
{

FileSystemObject::FileSystemObject(const Path& name)
:
mPath(name)
{}

Poco::Path& FileSystemObject::getPath()
{
	return mPath;
}

//FileFolderSP FileSystemObject::getParent()
//{
//	return mParent;
//}
//

bool FileSystemObject::isDirectory()
{
    return mPath.isDirectory();
}

string FileSystemObject::toString()
{
    return mPath.toString();
}

}

