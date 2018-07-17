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

FileFolder* FileFolders::getNext()
{
    if(mFolderIterator == end())
    {
        return NULL;
    }

    mFolderIterator++;

    if(mFolderIterator == end())
    {
        return NULL;
    }
    else
    {
        return *(mFolderIterator);
    }
}

}

