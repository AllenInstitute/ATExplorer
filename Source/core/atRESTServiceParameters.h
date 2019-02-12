#ifndef atRESTServiceParametersH
#define atRESTServiceParametersH
#include "atExplorerObject.h"
#include "dslProperties.h"
//---------------------------------------------------------------------------


namespace at
{

using dsl::PropertiesSP;
const string v1("v1");

class ATE_CORE RESTServiceParameters : public ExplorerObject
{
    public:
                                    RESTServiceParameters();
                                    RESTServiceParameters(const string& host, int portNr = 80, const string& version = v1);
                                    ~RESTServiceParameters();

        string                      getBaseURL() const;

	    PropertiesSP                getProperties();
        bool                        bindToPropertyContainer(PropertiesSP props);

        string                      getName() const;
        void                        setName(const string& n);

        void                        setHost(const string& u);
        string                      getHost() const;

        void                        setPortNr(int p);
        int                         getPortNr() const;
        string                      getPortNrAsString() const;

        void                        setMaxTilesToRender(int v);
        int                         getMaxTilesToRender() const;

        void                        setVersion(const string& v);
        string                      getVersion() const;

        void                        setProtocol(const string& v);
        string                      getProtocol() const;

                                    //!Container for reading/writing to file/UI
        PropertiesSP                mProperties;

    protected:

                                    //!Label for the 'connection'
        string                      mName;
        string                      mHost;  //This is used for the URI path as well.. may be improved later on..with a path
        int		                    mPort;
        string                      mVersion;
        string                      mProtocol;
        const string                mAPI;
        int                         mMaxTilesToRender;
        template<typename T>
        void                        bindPropertyToValue(const string& propLabel, const T& value, T& reference);
};

template< typename T >
void RESTServiceParameters::bindPropertyToValue(const string& propLabel, const T& value, T& reference)
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
