#pragma hdrstop
#include "atProjectItemTabbedView.h"
#include "atATExplorerProject.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace at
{
using namespace dsl;
ProjectItemTabbedView::ProjectItemTabbedView(TPageControl* pc, ATExplorerProject* p)
:
Observer(p),
mPC(pc),
mATExplorerProject(p)
{
    this->observe(p);
    mTabSheet = unique_ptr<TTabSheet> (new TTabSheet(mPC));
    mTabSheet->PageControl = mPC;
    mTabSheet->Caption = p->getProjectName().c_str();
}

ProjectItemTabbedView::~ProjectItemTabbedView()
{
    Log(lDebug3) << "Destroying a ProjectItemTabbedView..";
}

ATExplorerProject* ProjectItemTabbedView::getProject()
{
    return mATExplorerProject;
}

TTabSheet* ProjectItemTabbedView::getTabSheet()
{
    return mTabSheet.get();
}

//Views are managed by shared pointers so no need to call delete..
void ProjectItemTabbedView::update(Subject* theChangedSubject, SubjectEvent se)
{
    if(se == SubjectEvent::SubjectBeingDestroyed)
    {
        //Go away..
        Log(lInfo) << "Subject being destroyed..";
    }
}

}

