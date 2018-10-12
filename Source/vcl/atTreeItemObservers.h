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

//!Observer: this is not a great design. A views subject, if deleted, is not removed from the Views container.
//!We need to make ProjectObservers an observer of the TreeItemObjects , too..

class PACKAGE TreeItemObservers : public dsl::Observer
{
    public:
                                            TreeItemObservers(TPageControl& pc);
                                            ~TreeItemObservers();

		bool 								createView(Subject* o);
        unsigned int                        count();
//		void 								append(shared_ptr<TabbedProjectView> v);
        bool					            removeViewOnTabSheet(TTabSheet* s);
        bool                                removeViewForSubject(Subject* p);
        TTabSheet* 							getTabForSubject(Subject* p);
        void                                closeAll();
		void 								update(Subject* s, SubjectEvent se);

    protected:
        TPageControl&                       mMainPC;
        Views								mViews;
};

}
#endif
