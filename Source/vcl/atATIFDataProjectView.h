#ifndef atATIFDataProjectViewH
#define atATIFDataProjectViewH
#include "dslObserver.h"
#include "atTabbedProjectView.h"
#include "TATIFDataProjectFrame.h"
#include <memory>
//---------------------------------------------------------------------------

namespace at
{

using std::unique_ptr;
using dsl::Subject;
using dsl::SubjectEvent;

class ATIFDataProject;

//VCL frames can't do multiple inheritance. This class is therefore necessary, for "observing" reasons..
//The view manages the VCL frame..
class PACKAGE ATIFDataProjectView : public TabbedProjectView
{
    public:
                                            ATIFDataProjectView(TPageControl& pc, ATIFDataProject& rp);
        virtual            		            ~ATIFDataProjectView();
        virtual void                        update(Subject* theChangedSubject, SubjectEvent se = dsl::Ping);

    protected:
        unique_ptr<TATIFDataProjectFrame>  	mATIFDataProjectFrame;
};

}

#endif
