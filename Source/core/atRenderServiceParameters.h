#ifndef atRenderServiceParametersH
#define atRenderServiceParametersH
#include "atExplorerCoreExporter.h"
#include "atExplorerObject.h"
#include "dslProperties.h"
//---------------------------------------------------------------------------


namespace at
{

using dsl::PropertiesSP;

class ATE_CORE RenderServiceParameters : public ExplorerObject
{
    public:
                                    RenderServiceParameters();
                                    RenderServiceParameters(const string& name, const string& host, int portNr = 80, const string& version = "/render-ws/v1");
                                    ~RenderServiceParameters();

	    PropertiesSP                getProperties();
        bool                        bindToPropertyContainer(PropertiesSP props);

        string                      getName() const;
        void                        setName(const string& n);
        string                      asString() const;

        void                        setHost(const string& u);
        string                      getHost() const;

        void                        setPortNr(int p);
        int                         getPortNr() const;

        string                      getPortNrAsString() const;

        void                        setVersion(const string& v);
        string                      getVersion() const;

        void                        setProtocol(const string& v);
        string                      getProtocol() const;

        bool                        compare(const RenderServiceParameters& rsp);

    protected:
                                    //!Container for reading/writing
        PropertiesSP                mProperties;

                                    //!Label for the 'connection'
        string                      mName;
        string                      mHost;  //This is used for the URI path as well.. may be improved later on..with a path
        int		                    mPortNr;
        string                      mVersion;
        string                      mProtocol;

};

}

#endif
