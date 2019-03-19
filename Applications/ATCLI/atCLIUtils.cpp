#pragma hdrstop
#include "atCLIUtils.h"
#include "dslLogger.h"
using namespace dsl;
//---------------------------------------------------------------------------
string fixPathEnding(const string& p)
{
    string path(p);
    //Poco path requires a path to end with path delimiter
    if(p.size() && (p[p.size() -1] != '\\' || p[p.size() -1] != '/'))
    {
    #if defined(WIN32)
        path.push_back('\\');
    }
    #else
        path.push_back('/');
    #endif
    return path;
}

//Arg1 -> AtData
void onStartingPopulating(void* arg1, void* arg2, void* arg3)
{
    Log(lInfo) << "Starting populating data..";
}

//Arg1 -> AtData
void onProgressPopulating(void* arg1, void* arg2, void* arg3)
{
    ATData* data = (ATData*)arg1;
    Log(lInfo) << "Progress...";
    if(data)
    {
        Log(lInfo) << "Sections: " <<data->getNumberOfSections();
    }
}

//Arg1 -> AtData
void onFinishedPopulating(void* arg1, void* arg2, void* arg3)
{
    ATData* data = (ATData*)arg1;
    Log(lInfo) << "Finished populating data";
   	Log(lInfo) << data->getInfo();
}


