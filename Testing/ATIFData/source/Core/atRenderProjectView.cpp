#pragma hdrstop
#include "atRenderProjectView.h"
#include "atRenderProject.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace at
{
using namespace dsl;
RenderProjectView::RenderProjectView(TPageControl* pc, RenderProject* rp, const string& imPath)
:
TabbedProjectView(pc, rp)
{
    mTabSheet->Caption = rp->getProjectName().c_str();
    mRenderProjectFrame = unique_ptr<TRenderProjectFrame>(new TRenderProjectFrame(*rp, imPath, mPC));
    mRenderProjectFrame->Parent =  mTabSheet.get();
    mRenderProjectFrame->Align = alClient;
}

RenderProjectView::~RenderProjectView()
{
    Log(lDebug3) << "Closing RenderProjectView..";
}

}

