#ifndef atRenderClientH
#define atRenderClientH
#include "dslStringList.h"
#include "dslConstants.h"
#include "atRegionOfInterest.h"
#include "atRenderProject.h"
#include "atFetchImageThread.h"
#include "atRenderLocalCache.h"
#include "atRenderServiceParameters.h"
#include "atRESTClient.h"
#include "atGenericListOfObjects.h"
#include <string>
#include <vector>
#include "renderAPI/atRenderPointMatchAPI.h"
#include "renderAPI/atRenderStackDataAPI.h"
#include "renderAPI/atServerConfigurationAPI.h"
//---------------------------------------------------------------------------


//Use CURL instead of Indy..
namespace Idhttp
{
	class TIdHTTP;
}

namespace System
{
	namespace Classes
	{
		class TMemoryStream;
	}
}

namespace at
{

class PointMatchCollection;
using std::vector;
using dsl::StringList;
using dsl::gEmptyString;
using std::string;

using System::Classes::TMemoryStream;
typedef boost::function<void(void*, void*)> RCCallBack;

//Derive from a RestClient class
class ATE_CORE RenderClient : public RESTClient
{
	public:
							                        RenderClient(shared_ptr<Idhttp::TIdHTTP> c = shared_ptr<Idhttp::TIdHTTP>(), const string& host="localhost", const string& name = "");
							                        ~RenderClient();
        void										assignOnImageCallback(RCCallBack cb);

                                                    //Todo, init with RenderLayer object
		bool							            init(
                                                         const string& imageType     	= "jpeg-image",
                                                         int z 					    	= 0,
                                                         double scale 			    	= 0.01,
                                                         int minInt						= 0,
                                                         int maxInt						= 65535
                                                         );

		void                     					setRenderServiceParameters(const RenderServiceParameters& rsp);
		const RenderServiceParameters*              getRenderServiceParameters();

        string                                      getBaseURL();
		StringList						            getServerProperties();

                                                    //Various Render API's
        RenderStackDataAPI                          StackDataAPI;
        RenderPointMatchAPI                         PointMatchAPI;
        ServerConfigurationAPI                      ServerConfigurationAPI;

		TMemoryStream*								getImageMemory();
		void				                        clearImageMemory();

        TMemoryStream*		                        getImage(int z = 0);
        bool				                        getImageInThread(int z , StringList& paras, const string& channel, const RenderLocalCache& cache, const RenderProject& rp);

        string							            getURLForZ(int z, const RenderProject& rp);
		RegionOfInterest 						    getLayerBoundsForZ(int z, RenderProject& rp);
        RegionOfInterest						    getOptimalXYBoxForZs(const vector<int>& zs = vector<int>(0));
	    vector<RegionOfInterest>				    getLayerBounds();
        shared_ptr<FetchImageThread>				mFetchImageThread;

    private:

        void                                        createRESTServiceParameters(const string& host);
		StringList 									getMatchCollectionAPIResponse(const string& owner, const string& matchCollection, const string& request);

        											//!Memory to hold image data retrieved from server
		TMemoryStream* 		                        mImageMemory;

        											//!List of bounds
        vector<RegionOfInterest>				    mLayerBounds;

    	int				                            mZ;
        double				                        mScale;
        string 			                            mImageType;
        int								            mMinIntensity;
        int								            mMaxIntensity;
};

}
#endif
