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

//VCL frames can't do multiple inheritance. This class is therefore necessary, for "observing" reasons..
//The view manages the VCL frame..
class PACKAGE RenderProjectView : public dsl::Observer
{
    public:
                                            RenderProjectView(TPageControl* pc, RenderProject* rp, const string& imPath);
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
