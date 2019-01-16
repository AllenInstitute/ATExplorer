#pragma hdrstop
#include "atPointMatchCollectionProjectItemView.h"
#include "atPointMatchCollectionProject.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace at
{

using namespace dsl;
PointMatchCollectionProjectItemView::PointMatchCollectionProjectItemView(TPageControl& pc, ATExplorer& e, PointMatchCollectionProject& rp)
:
ProjectItemTabbedView(pc, rp)
{
    mTabSheet->Caption = rp.getProjectName().c_str();
    mPointMatchCollectionFrame = unique_ptr<TPointMatchCollectionFrame>(new TPointMatchCollectionFrame(e, rp, &mPC));
    mPointMatchCollectionFrame->Parent =  mTabSheet.get();
    mPointMatchCollectionFrame->Align = alClient;
}

PointMatchCollectionProjectItemView::~PointMatchCollectionProjectItemView()
{
    Log(lDebug3) << "Closing PointMatchCollectionProjectItemView..";
}

}

