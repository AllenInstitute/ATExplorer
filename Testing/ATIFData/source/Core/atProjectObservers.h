#ifndef atProjectObserversH
#define atProjectObserversH
#include "atATObject.h"
#include "dslSubject.h"
#include <vector>
#include "atDummyProjectViewObserver.h"
#include "dslSharedPointer.h"
//---------------------------------------------------------------------------

namespace at
{

using dsl::Subject;
using dsl::SubjectEvent;
using std::vector;
using dsl::shared_ptr;

typedef shared_ptr<DummyProjectViewObserver> observer;

class PACKAGE ProjectObservers : public ATObject
{
    public:
                                            ProjectObservers();
                                            ~ProjectObservers();
        unsigned int                        count();
        void                                clear();

        void                                append(RenderProjectView* v);
        bool					            removeViewOnTabSheet(TTabSheet* s);
        bool                                removeViewForProject(Project* p);

        void 								update(Subject* theChangedSubject, SubjectEvent se);
        TTabSheet* 							getTabForProject(Project* p);
        bool                                removeObserver(DummyProjectViewObserver* o);

    protected:
        vector< observer > 					mViews;
};

}
#endif
