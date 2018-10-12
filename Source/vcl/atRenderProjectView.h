#ifndef atRenderProjectViewH
#define atRenderProjectViewH
#include "atTabbedProjectView.h"
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
class PACKAGE RenderProjectView : public TabbedProjectView
{
    public:
                                            RenderProjectView(TPageControl& pc, RenderProject& rp, const string& imPath = gEmptyString);
        virtual                             ~RenderProjectView();

    protected:
        unique_ptr<TRenderProjectFrame>    	mRenderProjectFrame;
};

}

#endif
