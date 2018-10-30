#pragma hdrstop
#include "atProjectItemTabbedView.h"
#include "atATExplorerProject.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace at
{
using namespace dsl;
ProjectItemTabbedView::ProjectItemTabbedView(TPageControl& pc, Subject& p)
:
Observer(&p),
mPC(pc)
{
    this->mObserverTag = "ProjectItemTabbedView";
    this->observe(&p);
    mTabSheet = unique_ptr<TTabSheet> (new TTabSheet(&mPC));
    mTabSheet->PageControl = &mPC;
    mTabSheet->Caption = p.getTypeName().c_str();
}

ProjectItemTabbedView::~ProjectItemTabbedView()
{
    Log(lDebug3) << "Destroying a ProjectItemTabbedView..";
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

