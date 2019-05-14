#ifndef atTextItemViewH
#define atTextItemViewH
#include "dslObserver.h"
#include "atProjectItemTabbedView.h"
#include "TTiffStackProjectFrame.h"
#include <memory>
//---------------------------------------------------------------------------

namespace at
{

using std::unique_ptr;
using dsl::Subject;
using dsl::SubjectEvent;

class TiffStackProject;

//VCL frames can't do multiple inheritance. This class (creating the frame) is necessary, for "observing" reasons..
//The view manages the VCL frame..
class PACKAGE TiffStackProjectItemView : public ProjectItemTabbedView
{
    public:
                                            TiffStackProjectItemView(ATExplorer& e, TPageControl& pc, ATIFDataProject& rp);
        virtual            		            ~TiffStackProjectItemView();
        virtual void                        update(Subject* theChangedSubject, SubjectEvent se = dsl::Ping);

    protected:
        unique_ptr<TATIFDataProjectFrame>  	mATIFDataProjectFrame;
        ATExplorer&                         mATExplorer;
};

}

#endif
