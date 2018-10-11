#pragma hdrstop
#include "atTabbedProjectView.h"
#include "atATExplorerProject.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace at
{
using namespace dsl;
TabbedProjectView::TabbedProjectView(TPageControl* pc, ATExplorerProject& p)
:
Observer(&p),
mPC(pc),
mATExplorerProject(p)
{
    this->observe(&p);
    mTabSheet = unique_ptr<TTabSheet> (new TTabSheet(mPC));
    mTabSheet->PageControl = mPC;
    mTabSheet->Caption = p.getProjectName().c_str();
}

TabbedProjectView::~TabbedProjectView()
{
    Log(lDebug3) << "Destroying a TabbedProjectView..";
}

const ATExplorerProject* TabbedProjectView::getProject()
{
    return &mATExplorerProject;
}

TTabSheet* TabbedProjectView::getTabSheet()
{
    return mTabSheet.get();
}

//Views are managed by shared pointers so no need to call delete..
void TabbedProjectView::update(Subject* theChangedSubject, SubjectEvent se)
{
    if(se == SubjectEvent::SubjectBeingDestroyed)
    {
        //Go away..
        Log(lInfo) << "Subject being destroyed..";
    }
}

}

