#ifndef atRenderHostsH
#define atRenderHostsH
#include "atExplorerObject.h"
#include <vector>
#include "dslSharedPointer.h"
//---------------------------------------------------------------------------

namespace at
{
using std::vector;

class RenderServiceParameters;

typedef shared_ptr<RenderServiceParameters> RenderServiceParametersSP;

class ATE_CORE RenderHosts : public ExplorerObject
{
    public:
                                                    RenderHosts();
                                                    ~RenderHosts();
        bool                                        addHost(RenderServiceParametersSP h);
        bool                                        removeHost(const string& name);
       	RenderServiceParametersSP                   getFirst();
       	RenderServiceParametersSP                   getNext();
        bool                                        containsHost(const string& name);


    protected:
    	vector<RenderServiceParametersSP>			mHosts;
		vector<RenderServiceParametersSP>::iterator mHostIterator;

};

}

#endif
