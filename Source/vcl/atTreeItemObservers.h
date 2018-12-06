#ifndef atTreeItemObserversH
#define atTreeItemObserversH
#include "atExplorerObject.h"
#include "dslSubject.h"
#include <vector>
#include "dslSharedPointer.h"
#include "dslObserver.h"
#include "atATExplorer.h"
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
class ProjectItemTabbedView;

typedef shared_ptr<ProjectItemTabbedView> ProjectItemTabbedViewSP;
typedef vector< ProjectItemTabbedViewSP > Views;

//!The TreeItemObservers class is a container for 'Views'
//!It is responsible for creation of the views and management of related PageControl Tabs
class PACKAGE TreeItemObservers : public dsl::Observer
{
    public:
                                            TreeItemObservers(TPageControl& pc, ATExplorer& e);
                                            ~TreeItemObservers();
		ProjectItemTabbedView*   			getFirst();
		ProjectItemTabbedView*   			getNext();
        TTabSheet* 							getTabForSubject(Subject* p);
        bool                                selectTabWithView(ProjectItemTabbedView* v);

		ProjectItemTabbedView*		  		createView(Subject* o);
        unsigned int                        count();

        bool					            removeView(ProjectItemTabbedView* v);
        bool					            removeViewOnTabSheet(TTabSheet* s);
        bool                                removeViewForSubject(Subject* p);
        void                                closeAll();
		void 								update(Subject* s, SubjectEvent se);

    protected:
        TPageControl&                       MainPC;
        ATExplorer&                         mExplorer;
        Views								mViews;
        Views::iterator                     mViewsIterator;
};

}
#endif
