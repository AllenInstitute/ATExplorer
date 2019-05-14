#pragma hdrstop
#include "atTiffStackProjectItemView.h"
#include "atRenderProject.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace at
{

using namespace dsl;

TiffStackProjectItemView::TiffStackProjectItemView(ATExplorer& e, TPageControl& pc, ATIFDataProject& p)
:
ProjectItemTabbedView(pc, p),
mATExplorer(e)
{
    this->mObserverTag = "TiffStackProjectItemView";

    mATIFDataProjectFrame = unique_ptr<TATIFDataProjectFrame>(new TATIFDataProjectFrame(mATExplorer, p, &mPC));
    mATIFDataProjectFrame->Parent =  mTabSheet.get();
    mATIFDataProjectFrame->Align = alClient;
    mTabSheet->Caption = p.getProjectName().c_str();
}

TiffStackProjectItemView::~TiffStackProjectItemView()
{
    Log(lInfo) << "Closing TiffStackProjectItemView..";
}

//Views are managed by shared pointers so no need to call delete..
void TiffStackProjectItemView::update(Subject* theChangedSubject, SubjectEvent se)
{
    if(se == SubjectEvent::SubjectBeingDestroyed)
    {
        //Go away..
        Log(lInfo) << "Subject being destroyed..";
//        delete this;
    }
}

}

