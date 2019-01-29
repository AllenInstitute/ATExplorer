#ifndef atRenderRequestH
#define atRenderRequestH
#include "atRESTRequest.h"
#include "atRenderClient.h"
//---------------------------------------------------------------------------

namespace at
{


class ATE_CORE RenderRequest : public RESTRequest
{

    public:
                                            RenderRequest(const string& baseURL);
        virtual                             ~RenderRequest();

    protected:

};

}


#endif
