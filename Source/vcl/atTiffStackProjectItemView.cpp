#pragma hdrstop
#include "atTiffStackProjectItemView.h"
#include "atRenderProject.h"
#include "dslLogger.h"
#include "atATExplorer.h"
#include "atTiffStackProject.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace at
{

using namespace dsl;


TiffStackProjectItemView::TiffStackProjectItemView(TPageControl& pc, ATExplorer& e, TiffStackProject& p)
:
ProjectItemTabbedView(pc, p),
mATExplorer(e)
{
    this->mObserverTag = "TiffStackProjectItemView";

    mTiffStackProjectFrame = unique_ptr<TTiffStackProjectFrame>(new TTiffStackProjectFrame(p, &mPC));
    mTiffStackProjectFrame->Parent =  mTabSheet.get();
    mTiffStackProjectFrame->Align = alClient;
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

