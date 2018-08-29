#include <vcl.h>
#pragma hdrstop
#include "atRenderServiceParameters.h"
#include "dslStringUtils.h"
#include <sstream>
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace std;
namespace at
{

RenderServiceParameters::RenderServiceParameters(const string& b, int portNr, const string& version)
:
mBaseURL(b),
mPortNr(portNr),
mVersion(version)
{}

RenderServiceParameters::~RenderServiceParameters()
{}

string RenderServiceParameters::asString()
{
    stringstream s;
    s << mBaseURL << ":" << mPortNr << mVersion;
    return s.str();
}

void RenderServiceParameters::setBaseURL(const string& u)
{
    mBaseURL = u;
}

string RenderServiceParameters::getBaseURL()
{
    return mBaseURL;
}

void RenderServiceParameters::setPortNr(int p)
{
    mPortNr = p;
}

int RenderServiceParameters::getPortNr()
{
    return mPortNr;
}

string RenderServiceParameters::getPortNrAsString()
{
    return dsl::toString(mPortNr);
}

void RenderServiceParameters::setVersion(const string& v)
{
    mVersion = v;
}

string RenderServiceParameters::getVersion()
{
    return mVersion;
}

}
