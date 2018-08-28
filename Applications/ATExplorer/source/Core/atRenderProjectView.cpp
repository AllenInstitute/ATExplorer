#pragma hdrstop
#include "atRenderProjectView.h"
#include "atRenderProject.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace at
{
using namespace dsl;
RenderProjectView::RenderProjectView(TPageControl* pc, RenderProject* rp)
:
Observer(rp),
mPC(pc)
{
        this->observe(rp);
        mTabSheet = unique_ptr<TTabSheet> (new TTabSheet(mPC));
        mTabSheet->PageControl = mPC;
        mTabSheet->Caption = rp->getProjectName().c_str();
        mRenderProjectFrame = unique_ptr<TRenderProjectFrame>(new TRenderProjectFrame(rp, mPC));
        mRenderProjectFrame->Parent =  mTabSheet.get();
}

RenderProjectView::~RenderProjectView()
{}

TTabSheet* RenderProjectView::getTabSheet()
{
    return mTabSheet.get();
}

void RenderProjectView::update(Subject* theChangedSubject, SubjectEvent se)
{
    if(se == SubjectEvent::SubjectBeingDestroyed)
    {
        //Go away..
        Log(lInfo) << "Subject being destroyed..";
        delete this;
    }
}

}

