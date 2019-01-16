#ifndef atStringUtilsH
#define atStringUtilsH
#include "atExplorerCoreExporter.h"
#include <string>
#include "dslConstants.h"
#include "atJSMN.h"
//---------------------------------------------------------------------------

using std::string;
namespace at
{
string ATE_CORE toDockerMountPath(const string& winpath);

//!Convert C:\bla\bla\ to /prefixFolder/bla/bla
string ATE_CORE toPosixPath(const string& winpath, const string& prefixFolder = dsl::gEmptyString);
string ATE_CORE stripToChar(const string& str, char theChar);
string ATE_CORE toString(jsmntok_t& key, const string& json);

}
#endif
