#pragma hdrstop
#include "atUtils.h"
#include <algorithm>
#include "dslStringUtils.h"
//---------------------------------------------------------------------------

namespace at
{

using namespace std;
using namespace dsl;

string toPosixPath(const string& winpath, const string& prefixFolder)
{
    //Strip driveletter
    string pPath(stripToChar(winpath, ':'));
	std::replace(pPath.begin(), pPath.end(), '\\', '/');
    pPath = trimBack(pPath, '/');

    if(prefixFolder.size())
    {
        pPath = "/" + prefixFolder;
    }
    return pPath;
}

string stripToChar(const string& str, char theChar)
{
    // trim leading spaces
    size_t startpos = str.find_first_of(theChar);
    if(startpos != string::npos)
    {
	    string str2;
        str2 = str.substr(startpos + 1);
	    return str2;
    }
    else
    {
        return str;
    }
}

}

