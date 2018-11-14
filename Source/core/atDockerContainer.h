#ifndef atDockerContainerH
#define atDockerContainerH
#include "atExplorerObject.h"
#include "dslProperties.h"
//---------------------------------------------------------------------------

namespace at
{

using dsl::PropertiesSP;

class ATE_CORE DockerContainer : public ExplorerObject
{
    public:
                                    DockerContainer();
                                    DockerContainer(const string& name);
                                    ~DockerContainer();

	    PropertiesSP                getProperties();
        bool                        bindToPropertyContainer(PropertiesSP props);


        string                      getName() const;
        void                        setName(const string& n);

                                    //!Container for reading/writing to file/UI
        PropertiesSP                mProperties;

    protected:
                                    //!Name for the container
        string                      mName;

        template<typename T>
        void                        bindPropertyToValue(const string& propLabel, const T& value, T& reference);
};

template< typename T >
void DockerContainer::bindPropertyToValue(const string& propLabel, const T& value, T& reference)
{
    Property<T>* p = dynamic_cast< Property<T>* > (mProperties->getProperty(propLabel));
	if(!p)
    {
    	p = new Property<T>(value, propLabel);
    }
    mProperties->add(p);
    p->setValueReference(reference, true);
}


}

#endif
