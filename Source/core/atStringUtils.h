#ifndef atStringUtilsH
#define atStringUtilsH
#include "atExplorerCoreExporter.h"
#include <string>
#include "dslConstants.h"
//---------------------------------------------------------------------------

using std::string;
namespace at
{
//!Convert C:\bla\bla\ to /prefixFolder/bla/bla
string ATE_CORE toPosixPath(const string& winpath, const string& prefixFolder = dsl::gEmptyString);
string ATE_CORE stripToChar(const string& str, char theChar);

}
#endif
