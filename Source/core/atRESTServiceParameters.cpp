#pragma hdrstop
#include "atRESTServiceParameters.h"
#include "dslStringUtils.h"
#include "dslIniFileProperties.h"
#include <sstream>
//---------------------------------------------------------------------------

using namespace std;
using namespace dsl;

namespace at
{

RESTServiceParameters::RESTServiceParameters(const string& host, int portNr, const string& version)
:
mName(""),
mHost(host),
mPort(portNr),
mVersion(version),
mProtocol("http"),
mAPI("/render-ws")
{}

RESTServiceParameters::~RESTServiceParameters()
{}


RESTServiceParameters& RESTServiceParameters::operator=(const RESTServiceParameters& rhs)
{
    mName = rhs.mName;
    mHost = rhs.mHost;
    mPort = rhs.mPort;
    mVersion = rhs.mVersion;
    mProtocol = rhs.mProtocol;
    mAPI = rhs.mAPI;
    return *this;
}


string RESTServiceParameters::getBaseURL() const
{
    stringstream s;
    s << mProtocol << "://" << mHost <<":" << mPort << mAPI << "/" <<mVersion;
    return s.str();
}

bool RESTServiceParameters::bindToPropertyContainer(PropertiesSP props)
{
    mProperties = props;

    //For reading/writing in ui elements
	bindPropertyToValue<string>(	"NAME", 	            "<no name>", 	mName);
	bindPropertyToValue<string>(	"HOST", 	            "localhost", 	mHost);
	bindPropertyToValue<int>(		"PORT", 	            80, 			mPort);
	bindPropertyToValue<string>(	"VERSION", 	            "v1", 			mVersion);
	bindPropertyToValue<string>(	"PROTOCOL",             "http", 		mProtocol);
//	bindPropertyToValue<int>(		"MAX_TILES_TO_RENDER", 	130, 			mMaxTilesToRender);
    return true;
}

PropertiesSP RESTServiceParameters::getProperties()
{
    return mProperties;
}

string RESTServiceParameters::getName() const
{
    return mName;
}

//This function will change the name of corresponding inisection, if any
void RESTServiceParameters::setName(const string& n)
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

void RESTServiceParameters::setHost(const string& u)
{
    mHost = u;
}

string RESTServiceParameters::getHost() const
{
    return mHost;
}

void RESTServiceParameters::setPortNr(int p)
{
    mPort = p;
}

int RESTServiceParameters::getPortNr() const
{
    return mPort;
}

string RESTServiceParameters::getPortNrAsString() const
{
    return dsl::toString(mPort);
}

//void RESTServiceParameters::setMaxTilesToRender(int p)
//{
//    mMaxTilesToRender = p;
//}
//
//int RESTServiceParameters::getMaxTilesToRender() const
//{
//    return mMaxTilesToRender;
//}

void RESTServiceParameters::setVersion(const string& v)
{
    mVersion = v;
}

string RESTServiceParameters::getVersion() const
{
    return mVersion;
}

void RESTServiceParameters::setProtocol(const string& v)
{
    mProtocol = v;
}

string RESTServiceParameters::getProtocol() const
{
    return mProtocol;
}

}
