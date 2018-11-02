#pragma hdrstop
#include "atATExplorer.h"
//---------------------------------------------------------------------------

namespace at
{

ATExplorer::ATExplorer()
{
}

ATExplorer::~ATExplorer()
{}

void ATExplorer::appendRenderService(RenderServiceParameters  rs)
{
    return mRenderServices.append(rs);
}

RenderServiceParameters  ATExplorer::getFirstRenderService()
{
    return mRenderServices.getFirst();
}

RenderServiceParameters  ATExplorer::getNextRenderService()
{
    return mRenderServices.getNext();
}

}
