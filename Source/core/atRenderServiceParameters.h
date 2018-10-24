#ifndef atRenderServiceParametersH
#define atRenderServiceParametersH
#include "atExplorerCoreExporter.h"
#include "atExplorerObject.h"
//---------------------------------------------------------------------------

namespace at
{

class ATE_CORE RenderServiceParameters : public ExplorerObject
{
    public:
                                    RenderServiceParameters(const string& name, const string& bURL, int portNr = 80, const string& version = "/render-ws/v1");
                                    ~RenderServiceParameters();

        string                      getName() const;
        void                        setName(const string& n);
        string                      asString() const;

        void                        setBaseURL(const string& u);
        string                      getBaseURL() const;

        void                        setPortNr(int p);
        int                         getPortNr() const;

        string                      getPortNrAsString() const;
        void                        setVersion(const string& v);
        string                      getVersion() const;
        bool                        compare(const RenderServiceParameters& rsp);


    protected:
                                    //!Label for the 'connection'
        string                      mName;
        string                      mBaseURL;
        int		                    mPortNr;
        string                      mVersion;
};

}

#endif
