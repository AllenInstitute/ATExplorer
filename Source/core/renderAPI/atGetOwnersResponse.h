#ifndef atGetOwnersResponseH
#define atGetOwnersResponseH
#include "atRESTResponse.h"

//---------------------------------------------------------------------------
namespace at
{

class ATE_CORE GetOwnersRESTResponse : public RESTResponse
{
    public:
    											GetOwnersRESTResponse(const string& response);

        virtual bool                            parse();
        StringList                              getOwners();

    protected:

};

}

#endif
