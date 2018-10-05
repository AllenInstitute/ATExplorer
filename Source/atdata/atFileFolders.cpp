#pragma hdrstop
#include "atFileFolders.h"
#include "atFileFolder.h"
namespace at
{

FileFolders::FileFolders()
{}

FileFolders::~FileFolders()
{}

FileFolderSP FileFolders::operator[](int i)
{
    return mFolders.at(i);
}

FileFolderSP FileFolders::operator[](int i) const
{
    return mFolders.at(i);
}

FileFolders::FileFolders(const FileFolders& ffs)
{
    for(int i = 0; i < ffs.count(); i++)
    {
        FileFolderSP ff = ffs[i];
        append(ff);
    }
}

FileFolders& FileFolders::operator=(const FileFolders& rhs)
{

    return *this;
}

void FileFolders::reset()
{
    mFolders.clear();
}

void FileFolders::append(FileFolderSP ff)
{
    mFolders.push_back(ff);
}

FileFolderSP FileFolders::getFirst()
{
    mFolderIterator = mFolders.begin();
    return *(mFolderIterator);
}

FileFolderSP FileFolders::getNext()
{
    if(mFolderIterator == mFolders.end())
    {
        return FileFolderSP();
    }

    mFolderIterator++;
    return (mFolderIterator == mFolders.end()) ? FileFolderSP() : *(mFolderIterator);
}

}

