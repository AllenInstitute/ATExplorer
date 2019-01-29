#pragma hdrstop
#include "atRenderServiceParameters.h"
#include "dslStringUtils.h"
#include "dslIniFileProperties.h"
#include <sstream>
//---------------------------------------------------------------------------

using namespace std;
using namespace dsl;

namespace at
{

RenderServiceParameters::RenderServiceParameters()
:
RESTServiceParameters("",-1,"v1"),
mMaxTilesToRender(125)
{}

RenderServiceParameters::RenderServiceParameters(const string& host, int portNr, const string& version)
:
RESTServiceParameters(host, portNr, version),
mMaxTilesToRender(125)
{}

RenderServiceParameters::~RenderServiceParameters()
{}



void RenderServiceParameters::setMaxTilesToRender(int p)
{
    mMaxTilesToRender = p;
}

int RenderServiceParameters::getMaxTilesToRender() const
{
    return mMaxTilesToRender;
}

}
