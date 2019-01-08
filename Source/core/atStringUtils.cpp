#pragma hdrstop
#include "atStringUtils.h"
#include <algorithm>
#include "dslStringUtils.h"
//---------------------------------------------------------------------------

namespace at
{

using namespace std;
using namespace dsl;

string toString(jsmntok_t& key, const string& json)
{
    string val;
    unsigned int length = key.end - key.start;
    for(int i = 0; i < length; i++)
    {
        val.push_back(json[i+key.start]);
    }

    return val;
}

string toDockerMountPath(const string& winpath)
{
    //Strip driveletter
    string pPath(stripToChar(winpath, ':'));
	std::replace(pPath.begin(), pPath.end(), '\\', '/');
    pPath = trimBack(pPath, '/');

	vector<string> partd = splitStringAtWord(pPath, "data");

    if(partd.size() == 2)
    {
        return joinPath("/mnt", partd[1], '/');
    }
    else
    {
        return "";
    }
}

string toPosixPath(const string& winpath, const string& prefixFolder)
{
    //Strip driveletter
    string pPath(stripToChar(winpath, ':'));
	std::replace(pPath.begin(), pPath.end(), '\\', '/');
    pPath = trimBack(pPath, '/');

    if(prefixFolder.size())
    {
        pPath = prefixFolder + pPath;
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

