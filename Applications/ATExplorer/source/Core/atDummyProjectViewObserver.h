#ifndef atDummyProjectViewObserverH
#define atDummyProjectViewObserverH
#include "dslObserver.h"
//---------------------------------------------------------------------------

namespace dsl
{
    class Project;
}
namespace at
{

using dsl::Observer;
using dsl::Project;
using dsl::Subject;
using dsl::SubjectEvent;

class RenderProjectView;
class ProjectObservers;

//!The DummyProjectViewObserver is a helper class to
//the container holding project observers, ProjectObservers.
//Its main purpose is to remove items from the container as they are
//destroyed. It does that by being itself an observer and thus
//subscribes to subject (projects) events
class DummyProjectViewObserver : public dsl::Observer
{
    public:
							        DummyProjectViewObserver(ProjectObservers& o, RenderProjectView& rpv);
							        ~DummyProjectViewObserver();

    	virtual void                update(Subject* theChangedSubject, SubjectEvent se = dsl::Ping);
        RenderProjectView*          getView();

    private:
        ProjectObservers&           mHost;
        RenderProjectView&          mRPV;
};

}
#endif
