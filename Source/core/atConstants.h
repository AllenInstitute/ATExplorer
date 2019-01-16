#ifndef atConstantsH
#define atConstantsH
#include "atCoreExporter.h"
#include <string>
//---------------------------------------------------------------------------

#if __cplusplus <= 199711L
  #define nullptr NULL
#endif

namespace at
{
  
using std::string;
typedef unsigned int uint;
AT_CORE extern const string gRenderVersion;

}
#endif
