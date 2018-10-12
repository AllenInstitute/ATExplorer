#pragma hdrstop
#include "atATIFDataProjectView.h"
#include "atRenderProject.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace at
{
using namespace dsl;
ATIFDataProjectView::ATIFDataProjectView(TPageControl& pc, ATIFDataProject& p)
:
TabbedProjectView(pc, p)
{
    this->mObserverTag = "ATIFDataProjectView";

    mATIFDataProjectFrame = unique_ptr<TATIFDataProjectFrame>(new TATIFDataProjectFrame(p, &mPC));
    mATIFDataProjectFrame->Parent =  mTabSheet.get();
    mATIFDataProjectFrame->Align = alClient;
}

ATIFDataProjectView::~ATIFDataProjectView()
{
    Log(lInfo) << "Closing ATIFDataProjectView..";
}

//Views are managed by shared pointers so no need to call delete..
void ATIFDataProjectView::update(Subject* theChangedSubject, SubjectEvent se)
{
    if(se == SubjectEvent::SubjectBeingDestroyed)
    {
        //Go away..
        Log(lInfo) << "Subject being destroyed..";
//        delete this;
    }
}

}

