#ifndef atCLIUtilsH
#define atCLIUtilsH
#include <string>
#include "atdata/atATData.h"
//---------------------------------------------------------------------------

using std::string;
using at::ATData;

string 	            fixPathEnding(const string& p);
void                onStartingPopulating(void* arg1, void* arg2, void* arg3);
void                onProgressPopulating(void* arg1, void* arg2, void* arg3);
void                onFinishedPopulating(void* arg1, void* arg2, void* arg3);
void                populate(ATData* data);


#endif
