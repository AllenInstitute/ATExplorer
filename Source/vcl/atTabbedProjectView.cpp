#pragma hdrstop
#include "atTabbedProjectView.h"
#include "atATExplorerProject.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace at
{
using namespace dsl;
TabbedProjectView::TabbedProjectView(TPageControl& pc, Subject& p)
:
Observer(&p),
mPC(pc)
{
    this->mObserverTag = "TabbedProjectView";
    this->observe(&p);
    mTabSheet = unique_ptr<TTabSheet> (new TTabSheet(&mPC));
    mTabSheet->PageControl = &mPC;
    mTabSheet->Caption = p.getTypeName().c_str();
}

TabbedProjectView::~TabbedProjectView()
{
    Log(lDebug3) << "Destroying a TabbedProjectView..";
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

