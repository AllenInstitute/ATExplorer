#pragma hdrstop
#include "atATIFDataProjectView.h"
#include "atRenderProject.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace at
{
using namespace dsl;
ATIFDataProjectView::ATIFDataProjectView(TPageControl* pc, ATIFDataProject* rp)
:
Observer(rp),
mPC(pc),
mATIFDataProject(rp)
{
    this->observe(rp);

    mTabSheet = unique_ptr<TTabSheet> (new TTabSheet(mPC));
    mTabSheet->PageControl = mPC;
    mTabSheet->Caption = rp->getProjectName().c_str();
    mATIFDataProjectFrame = unique_ptr<TATIFDataProjectFrame>(new TATIFDataProjectFrame(*rp, mPC));
    mATIFDataProjectFrame->Parent =  mTabSheet.get();
    mATIFDataProjectFrame->Align = alClient;
}

ATIFDataProjectView::~ATIFDataProjectView()
{
    Log(lDebug3) << "Closing ATIFDataProjectView..";
}

ATIFDataProject* ATIFDataProjectView::getATIFDataProject()
{
    return mATIFDataProject;
}

TTabSheet* ATIFDataProjectView::getTabSheet()
{
    return mTabSheet.get();
}

void ATIFDataProjectView::update(Subject* theChangedSubject, SubjectEvent se)
{
    if(se == SubjectEvent::SubjectBeingDestroyed)
    {
        //Go away..
        Log(lInfo) << "Subject being destroyed..";
        delete this;
    }
}

}

