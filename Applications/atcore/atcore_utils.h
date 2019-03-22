#ifndef atcore_utilsH
#define atcore_utilsH
#include <string>
#include "atdata/atATIFData.h"
//---------------------------------------------------------------------------
using std::string;

using at::ATData;

string 	            fixPathEnding(const string& p);
void                onStartingPopulating(void* arg1, void* arg2, void* arg3);
void                onProgressPopulating(void* arg1, void* arg2, void* arg3);
void                onFinishedPopulating(void* arg1, void* arg2, void* arg3);
void                populate(ATData* data);


#endif
