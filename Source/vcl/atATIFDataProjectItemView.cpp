#pragma hdrstop
#include "atATIFDataProjectItemView.h"
#include "atRenderProject.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace at
{

using namespace dsl;

ATIFDataProjectItemView::ATIFDataProjectItemView(ATExplorer& e, TPageControl& pc, ATIFDataProject& p)
:
ProjectItemTabbedView(pc, p),
mATExplorer(e)
{
    this->mObserverTag = "ATIFDataProjectItemView";

    mATIFDataProjectFrame = unique_ptr<TATIFDataProjectFrame>(new TATIFDataProjectFrame(mATExplorer, p, &mPC));
    mATIFDataProjectFrame->Parent =  mTabSheet.get();
    mATIFDataProjectFrame->Align = alClient;
    mTabSheet->Caption = p.getProjectName().c_str();
}

ATIFDataProjectItemView::~ATIFDataProjectItemView()
{
    Log(lInfo) << "Closing ATIFDataProjectItemView..";
}

//Views are managed by shared pointers so no need to call delete..
void ATIFDataProjectItemView::update(Subject* theChangedSubject, SubjectEvent se)
{
    if(se == SubjectEvent::SubjectBeingDestroyed)
    {
        //Go away..
        Log(lInfo) << "Subject being destroyed..";
//        delete this;
    }
}

}

