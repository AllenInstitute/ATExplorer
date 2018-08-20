#pragma hdrstop
#include "ateAppUtilities.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace dsl;
namespace at
{

AppUtilities::AppUtilities()
:
ApplicationUtilities("ATExplorer", "\\Software\\Allen Institute\\ATExplorer", "0.5.0")
{
}

AppUtilities::~AppUtilities()
{
    Log(lInfo) << "In ATExplorers AppUtilities destructor..";
}


}
