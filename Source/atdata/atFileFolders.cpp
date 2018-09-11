//---------------------------------------------------------------------------
#pragma hdrstop
#include "atFileFolders.h"

namespace at
{

FileFolders::FileFolders()
{}

FileFolders::~FileFolders()
{}

FileFolder* FileFolders::operator[](int i)
{
    return mFolders[i];
}

void FileFolders::append(FileFolder* ff)
{
    mFolders.push_back(ff);
}

FileFolder* FileFolders::getFirst()
{
    mFolderIterator = mFolders.begin();
    return *(mFolderIterator);
}

FileFolder* FileFolders::getNext()
{
    if(mFolderIterator == mFolders.end())
    {
        return NULL;
    }

    mFolderIterator++;
    return (mFolderIterator == mFolders.end()) ? NULL : *(mFolderIterator);
}

}

