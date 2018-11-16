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
mName(""),
mHost(""),
mPort(-1),
mVersion("v1"),
mProtocol("http"),
mAPI("/render-ws"),
mMaxTilesToRender(125)
{}

RenderServiceParameters::RenderServiceParameters(const string& name, const string& host, int portNr, const string& version)
:
mName(name),
mHost(host),
mPort(portNr),
mVersion(version),
mProtocol("http"),
mMaxTilesToRender(125),
mAPI("/render-ws")
{}

RenderServiceParameters::~RenderServiceParameters()
{}


string RenderServiceParameters::getBaseURL() const
{
    stringstream s;
    s << mProtocol << "://" << mHost <<":" << mPort << mAPI << "/" <<mVersion;
    return s.str();
}

bool RenderServiceParameters::bindToPropertyContainer(PropertiesSP props)
{
    mProperties = props;

    //For reading/writing in ui elements
	bindPropertyToValue<string>(	"NAME", 	            "<no name>", 	mName);
	bindPropertyToValue<string>(	"HOST", 	            "localhost", 	mHost);
	bindPropertyToValue<int>(		"PORT", 	            80, 			mPort);
	bindPropertyToValue<string>(	"VERSION", 	            "v1", 			mVersion);
	bindPropertyToValue<string>(	"PROTOCOL",             "http", 		mProtocol);
	bindPropertyToValue<int>(		"MAX_TILES_TO_RENDER", 	130, 			mMaxTilesToRender);
    return true;
}

PropertiesSP RenderServiceParameters::getProperties()
{
    return mProperties;
}

string RenderServiceParameters::getName() const
{
    return mName;
}

//This function will change the name of corresponding inisection, if any
void RenderServiceParameters::setName(const string& n)
{
    //Change inifile section
	IniFileProperties* ini = dynamic_cast<IniFileProperties*> (mProperties.get());
    if(ini)
    {
    	string currentSectionName = ini->getSectionName();

        //Create section if it does not exist
	    IniSection* sec = ini->getIniFile()->getSection(currentSectionName, true);
        if(sec)
        {
            sec->mName = "RENDER_SERVICE_" + n;
            IniKey* key = sec->getKey("NAME");
            if(key)
            {
                key->mValue = n;
            }
        }
        ini->setSectionName("RENDER_SERVICE_" + n);
    }
    mName = n;
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
    mPort = p;
}

int RenderServiceParameters::getPortNr() const
{
    return mPort;
}

string RenderServiceParameters::getPortNrAsString() const
{
    return dsl::toString(mPort);
}

void RenderServiceParameters::setMaxTilesToRender(int p)
{
    mMaxTilesToRender = p;
}

int RenderServiceParameters::getMaxTilesToRender() const
{
    return mMaxTilesToRender;
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
