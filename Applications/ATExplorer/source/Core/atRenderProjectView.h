#ifndef atRenderProjectViewH
#define atRenderProjectViewH
#include "dslObserver.h"
#include "TRenderProjectFrame.h"
#include <memory>
//---------------------------------------------------------------------------

namespace at
{

using std::unique_ptr;
using dsl::Subject;
using dsl::SubjectEvent;

class RenderProject;

class RenderProjectView : public dsl::Observer
{
        public:
                            		            RenderProjectView(TPageControl* pc, RenderProject* rp);
                            		            ~RenderProjectView();

        	virtual void                        update(Subject* theChangedSubject, SubjectEvent se = dsl::Ping);
            TTabSheet*                          getTabSheet();
            RenderProject*                      getRenderProject();

        protected:
            TPageControl*       				mPC;
            RenderProject*                      mRenderProject;
			unique_ptr<TTabSheet> 				mTabSheet;
       		unique_ptr<TRenderProjectFrame>    	mRenderProjectFrame;
};

}

#endif
