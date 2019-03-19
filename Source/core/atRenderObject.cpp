#pragma hdrstop
#include "atRenderObject.h"
#include "atRenderClient.h"
//---------------------------------------------------------------------------


namespace at
{

RenderObject::RenderObject(RenderClient* rs)
:
mRenderClient(rs)
{}

RenderObject::~RenderObject()
{}

}
