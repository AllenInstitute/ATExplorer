#pragma hdrstop
#include "atExplorerCore.h"
//#include "dslStringUtils.h"
//#include "dslWin32Utils.h"

namespace at
{

//using namespace dsl;
const string MAJOR_VERSION = "0";
const string MINOR_VERSION = "5";

string getAPIVersion()
{
    return MAJOR_VERSION + "." + MINOR_VERSION;
}

}



//Module entry point..
extern "C" int _libmain(unsigned long reason)
{
	return 1;
}





