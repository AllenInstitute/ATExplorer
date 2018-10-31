#pragma hdrstop
#include "atTextFile.h"
//---------------------------------------------------------------------------

namespace at
{

TextFile::TextFile(const string& fName, const string& alias)
:
mFileNameWithPath(fName),
mAlias(alias)
{}

TextFile::~TextFile()
{}

string TextFile::getFileNameWithPath()
{
    return mFileNameWithPath;
}

string TextFile::getAlias()
{
    return mAlias;
}

void   TextFile::setAlias(const string& a)
{
    mAlias = a;
}

}

