#pragma hdrstop
#include "atData.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
using namespace dsl;

ATData::ATData(const Path& bp)
:
mBasePath(bp, NULL)
{
}

bool ATData::validate()
{
	Log(lDebug) << "Implement in descendants";
}
