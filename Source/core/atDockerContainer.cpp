#pragma hdrstop
#include "atDockerContainer.h"
#include "dslStringUtils.h"
#include "dslIniFileProperties.h"
#include <sstream>
//---------------------------------------------------------------------------

using namespace std;
using namespace dsl;

namespace at
{

DockerContainer::DockerContainer()
:
mName("")
{}

DockerContainer::DockerContainer(const string& name)
:
mName(name)
{}

DockerContainer::~DockerContainer()
{}

bool DockerContainer::bindToPropertyContainer(PropertiesSP props)
{
    mProperties = props;

    //For reading/writing in ui elements
	bindPropertyToValue<string>(	"NAME", "	<no name>", 			mName);
    return true;
}

PropertiesSP DockerContainer::getProperties()
{
    return mProperties;
}

string DockerContainer::getName() const
{
    return mName;
}

//This function will change the name of corresponding inisection, if any
void DockerContainer::setName(const string& n)
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
            sec->mName = "DOCKER_CONTAINER_" + n;
            IniKey* key = sec->getKey("NAME");
            if(key)
            {
                key->mValue = n;
            }
        }
        ini->setSectionName("DOCKER_CONTAINER_" + n);
    }
    mName = n;
}

}
