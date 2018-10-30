#pragma hdrstop
#include "atRenderProjectItemView.h"
#include "atRenderProject.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace at
{
using namespace dsl;
RenderProjectItemView::RenderProjectItemView(TPageControl& pc, RenderProject& rp, const string& imPath)
:
ProjectItemTabbedView(pc, rp)
{
    mTabSheet->Caption = rp.getProjectName().c_str();
    mRenderProjectFrame = unique_ptr<TRenderProjectFrame>(new TRenderProjectFrame(rp, imPath, &mPC));
    mRenderProjectFrame->Parent =  mTabSheet.get();
    mRenderProjectFrame->Align = alClient;
}

RenderProjectItemView::~RenderProjectItemView()
{
    Log(lDebug3) << "Closing RenderProjectItemView..";
}

}

