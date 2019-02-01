#ifndef atRenderObjectH
#define atRenderObjectH
#include "atExplorerObject.h"
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
                                        //!This function is synchronous, for now..
        virtual bool                    fetch() = 0;

    protected:
    	RenderClient* 					mRenderClient;
};

}


#endif
