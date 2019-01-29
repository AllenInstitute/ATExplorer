#ifndef atGetOwnersRequestH
#define atGetOwnersRequestH
#include "atRenderRequest.h"
//---------------------------------------------------------------------------

namespace at
{

class ATE_CORE GetOwnersRequest : public RenderRequest
{

    public:
                        GetOwnersRequest(const string& baseURL);
                        ~GetOwnersRequest();

    protected:

    private:

};

}

#endif
