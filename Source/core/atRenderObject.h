#ifndef atRenderObjectH
#define atRenderObjectH
#include "atExplorerObject.h"
#include "atRenderClient.h"
//---------------------------------------------------------------------------

namespace at
{
class ATE_CORE RenderObject : public ExplorerObject
{
    public:
                        				RenderObject(shared_ptr<RenderClient> rc = shared_ptr<RenderClient>() );
                        				~RenderObject();

    protected:
		shared_ptr<RenderClient> 		mRenderService;
};

}

namespace at
{

RenderObject::RenderObject(shared_ptr<RenderClient> rs)
:
mRenderService(rs)
{}

RenderObject::~RenderObject()
{}

}

#endif
