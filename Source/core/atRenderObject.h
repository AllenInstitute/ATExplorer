#ifndef atRenderObjectH
#define atRenderObjectH
#include "atExplorerObject.h"
//#include "atRenderClient.h"
//---------------------------------------------------------------------------

namespace at
{

class RenderClient;

class ATE_CORE RenderObject : public ExplorerObject
{
    public:
                        				RenderObject(RenderClient* rc = NULL);
        virtual           				~RenderObject();

                                        //!Every RenderObject can be fetched from the server
                                        //!This function is synchronous..
        virtual bool                    fetch() = 0;

    protected:
    	RenderClient* 					mRenderService;
};

}


#endif
