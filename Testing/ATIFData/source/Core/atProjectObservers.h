#ifndef atProjectObserversH
#define atProjectObserversH
#include "atATObject.h"
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
//!We need to make ProjectObservers an observer of the projects, too..

class PACKAGE ProjectObservers : public ATObject
{
    public:
                                            ProjectObservers();
                                            ~ProjectObservers();
//        virtual void                        update(Subject* theChangedSubject, SubjectEvent se = dsl::Ping);
        unsigned int                        count();
		void 								append(shared_ptr<TabbedProjectView> v);
        bool					            removeViewOnTabSheet(TTabSheet* s);
        bool                                removeViewForProject(Project* p);
        TTabSheet* 							getTabForProject(Project* p);
        void                                closeAll();

    protected:
        Views								mViews;
};

}
#endif
