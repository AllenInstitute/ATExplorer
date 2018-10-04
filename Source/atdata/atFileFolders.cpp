#pragma hdrstop
#include "atFileFolders.h"
#include "atFileFolder.h"
namespace at
{

FileFolders::FileFolders()
{}

FileFolders::~FileFolders()
{
    for(int i = 0; i < mFolders.size(); i++)
    {
        delete mFolders[i];
    }
}


FileFolder* FileFolders::operator[](int i)
{
    return mFolders.at(i);
}

FileFolder* FileFolders::operator[](int i) const
{
    return mFolders.at(i);
}

FileFolders::FileFolders(const FileFolders& ffs)
{
    for(int i = 0; i < ffs.count(); i++)
    {
        FileFolder* ff = ffs[i];
        append(new FileFolder(ff));
    }
}

FileFolders& FileFolders::operator=(const FileFolders& rhs)
{

    return *this;
}

void FileFolders::reset()
{
    for(int i = 0; i < mFolders.size(); i++)
    {
        delete mFolders[i];
    }
    mFolders.clear();
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

