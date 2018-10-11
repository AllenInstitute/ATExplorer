#ifndef atTabbedProjectViewH
#define atTabbedProjectViewH
#include "dslObserver.h"
#include <memory>
//---------------------------------------------------------------------------

namespace at
{

using std::unique_ptr;
using dsl::Subject;
using dsl::SubjectEvent;

class ATExplorerProject;

//VCL frames can't do multiple inheritance. This class is necessary, for "observing" reasons..
//The view manages a VCL frame in descendants..
class PACKAGE TabbedProjectView : public dsl::Observer
{
    public:
                                            TabbedProjectView(TPageControl* pc, ATExplorerProject& rp);
                                            ~TabbedProjectView();

        virtual void                        update(Subject* theChangedSubject, SubjectEvent se = dsl::Ping);
        TTabSheet*                          getTabSheet();
        const ATExplorerProject*            getProject();

    protected:
        TPageControl*       				mPC;
        ATExplorerProject&                  mATExplorerProject;
        unique_ptr<TTabSheet> 				mTabSheet;
};

}

#endif
