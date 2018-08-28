#ifndef atRenderServiceParametersH
#define atRenderServiceParametersH
#include "atATObject.h"

//---------------------------------------------------------------------------
namespace at
{

class PACKAGE RenderServiceParameters : public ATObject
{

        public:
                                        RenderServiceParameters(const string& bURL, int portNr = 80, const string& version = "/render-ws/v1");
                                        ~RenderServiceParameters();
            string                      asString();

            void                        setBaseURL(const string& u);
            string                      getBaseURL();

            void                        setPortNr(int p);
            int                         getPortNr();

            string                      getPortNrAsString();
            void                        setVersion(const string& v);
            string                      getVersion();

        protected:
            string                      mBaseURL;
            int		                    mPortNr;
            string                      mVersion;
};

}

#endif
