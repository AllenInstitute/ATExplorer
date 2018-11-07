#pragma hdrstop
#include "atRenderServiceParameters.h"
#include "dslStringUtils.h"
#include <sstream>
//---------------------------------------------------------------------------

using namespace std;
using namespace dsl;
namespace at
{

RenderServiceParameters::RenderServiceParameters()
:
mName(""),
mHost(""),
mPortNr(-1),
mVersion(""),
mProtocol("http")
{}

RenderServiceParameters::RenderServiceParameters(const string& name, const string& b, int portNr, const string& version)
:
mName(name),
mHost(b),
mPortNr(portNr),
mVersion(version),
mProtocol("http")
{}

RenderServiceParameters::~RenderServiceParameters()
{}

string RenderServiceParameters::getName() const
{
    return mName;
}

bool RenderServiceParameters::bindToPropertyContainer(PropertiesSP props)
{
    mProperties = props;
    //For reading/writing in ui elements
    Property<string>* name = dynamic_cast< Property<string>* > (props->getProperty("NAME"));
	if(name)
    {
       	name->setValueReference(mName, true);
    }
    else
    {
//        props.add()
    }

    Property<string>* host = dynamic_cast< Property<string>* > (props->getProperty("HOST"));
    if(host)
    {
       host->setValueReference(mHost, true);
    }
    else
    {
//        props.add()
    }
}

PropertiesSP RenderServiceParameters::getProperties()
{
    return mProperties;
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
    s << mHost << ":" << mPortNr << mVersion;
    return s.str();
}

void RenderServiceParameters::setHost(const string& u)
{
    mHost = u;
}

string RenderServiceParameters::getHost() const
{
    return mHost;
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

void RenderServiceParameters::setProtocol(const string& v)
{
    mProtocol = v;
}

string RenderServiceParameters::getProtocol() const
{
    return mProtocol;
}

}
