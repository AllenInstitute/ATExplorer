#ifndef atTreeItemObserversH
#define atTreeItemObserversH
#include "atExplorerObject.h"
#include "dslSubject.h"
#include <vector>
#include "dslSharedPointer.h"
#include "dslObserver.h"
//---------------------------------------------------------------------------

namespace dsl
{
    class Project;
}

namespace at
{

using std::vector;
using dsl::Subject;
using dsl::SubjectEvent;
using dsl::Project;
class TabbedProjectView;

typedef vector< shared_ptr<TabbedProjectView > > Views;

//!The TreeItemObservers class is a container for 'Views'
//!It is responsible for creation of the views and management of related PageControl Tabs
class PACKAGE TreeItemObservers : public dsl::Observer
{
    public:
                                            TreeItemObservers(TPageControl& pc);
                                            ~TreeItemObservers();

        TTabSheet* 							getTabForSubject(Subject* p);
        bool                                selectTabWithView(TabbedProjectView* v);

		TabbedProjectView*					createView(Subject* o);

        unsigned int                        count();
//		void 								append(shared_ptr<TabbedProjectView> v);
        bool					            removeViewOnTabSheet(TTabSheet* s);
        bool                                removeViewForSubject(Subject* p);

        void                                closeAll();
		void 								update(Subject* s, SubjectEvent se);

    protected:
        TPageControl&                       MainPC;
        Views								mViews;
};

}
#endif
