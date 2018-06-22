//---------------------------------------------------------------------------
#pragma hdrstop
#include "atFileFolders.h"

namespace at
{

FileFolders::FileFolders()
{}

FileFolders::~FileFolders()
{}


FileFolder* FileFolders::getFirst()
{
    mFolderIterator = begin();
    return *(mFolderIterator);
}
}

