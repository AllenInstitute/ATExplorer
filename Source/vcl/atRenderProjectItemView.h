#ifndef atRenderProjectItemViewH
#define atRenderProjectItemViewH
#include "atProjectItemTabbedView.h"
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
class PACKAGE RenderProjectItemView : public ProjectItemTabbedView
{
    public:
                                            RenderProjectItemView(TPageControl& pc, RenderProject& rp, const string& imPath = gEmptyString);
        virtual                             ~RenderProjectItemView();

    protected:
        unique_ptr<TRenderProjectFrame>    	mRenderProjectFrame;
};

}

#endif
