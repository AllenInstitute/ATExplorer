#ifndef atATIFDataProjectItemViewH
#define atATIFDataProjectItemViewH
#include "dslObserver.h"
#include "atProjectItemTabbedView.h"
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
class PACKAGE ATIFDataProjectItemView : public ProjectItemTabbedView
{
    public:
                                            ATIFDataProjectItemView(TPageControl& pc, ATIFDataProject& rp);
        virtual            		            ~ATIFDataProjectItemView();
        virtual void                        update(Subject* theChangedSubject, SubjectEvent se = dsl::Ping);

    protected:
        unique_ptr<TATIFDataProjectFrame>  	mATIFDataProjectFrame;
};

}

#endif
