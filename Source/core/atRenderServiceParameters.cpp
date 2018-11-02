#pragma hdrstop
#include "atRenderServiceParameters.h"
#include "dslStringUtils.h"
#include <sstream>
//---------------------------------------------------------------------------

using namespace std;

namespace at
{

RenderServiceParameters::RenderServiceParameters()
:
mName(""),
mBaseURL(""),
mPortNr(-1),
mVersion("")
{}

RenderServiceParameters::RenderServiceParameters(const string& name, const string& b, int portNr, const string& version)
:
mName(name),
mBaseURL(b),
mPortNr(portNr),
mVersion(version)
{}

RenderServiceParameters::~RenderServiceParameters()
{}

string RenderServiceParameters::getName() const
{
    return mName;
}

bool RenderServiceParameters::compare(const RenderServiceParameters& rsp)
{
    return this->mName == rsp.getName();
}

void RenderServiceParameters::setName(const string& n)
{
    mName = n;
}

string RenderServiceParameters::asString() const
{
    stringstream s;
    s << mBaseURL << ":" << mPortNr << mVersion;
    return s.str();
}

void RenderServiceParameters::setBaseURL(const string& u)
{
    mBaseURL = u;
}

string RenderServiceParameters::getBaseURL() const
{
    return mBaseURL;
}

void RenderServiceParameters::setPortNr(int p)
{
    mPortNr = p;
}

int RenderServiceParameters::getPortNr() const
{
    return mPortNr;
}

string RenderServiceParameters::getPortNrAsString() const
{
    return dsl::toString(mPortNr);
}

void RenderServiceParameters::setVersion(const string& v)
{
    mVersion = v;
}

string RenderServiceParameters::getVersion() const
{
    return mVersion;
}

}
