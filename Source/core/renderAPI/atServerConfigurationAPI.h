#ifndef atServerConfigurationAPIH
#define atServerConfigurationAPIH
#include "atExplorerObject.h"
#include "dslStringList.h"
#include "atGenericListOfPointers.h"
#include "atRenderAPI.h"
//---------------------------------------------------------------------------

namespace at
{

using dsl::StringList;
class RenderClient;
class ATE_CORE ServerConfigurationAPI : public RenderAPI
{

    public:
                        			                        ServerConfigurationAPI(RenderClient& rc);
                        			                        ~ServerConfigurationAPI();

                                                            //Pointmatch API's
		string										        getServerProperties();

    protected:
};

}

#endif
