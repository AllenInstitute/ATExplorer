#pragma hdrstop
#include "atRenderRequest.h"
#include "atRenderClient.h"
//---------------------------------------------------------------------------


namespace at
{

RenderRequest::RenderRequest(const string& baseURL)
:
RESTRequest(baseURL)
{}

RenderRequest::~RenderRequest()
{}

}



