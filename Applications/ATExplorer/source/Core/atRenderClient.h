#ifndef atRenderClientH
#define atRenderClientH
#include <string>
#include "dslStringList.h"
#include "dslConstants.h"
#include <vector>
#include "atRenderBox.h"
#include "atRenderProject.h"
#include "atFetchImageThread.h"
//---------------------------------------------------------------------------

using std::vector;
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

using System::Classes::TMemoryStream;
using dsl::StringList;
using dsl::gEmptyString;
using std::string;

typedef void __fastcall (__closure *RCCallBack)(void);

class RenderClient
{
	public:
							                        RenderClient(Idhttp::TIdHTTP* c,
                        	                        						const string& baseURL 	    = gEmptyString,
                        	                        					  	const string& owner 	    = gEmptyString,
                        	                        					  	const string& project 	    = gEmptyString,
                                                                          	const string& stack 	    = gEmptyString,
                                                                          	const string& imageType     = "jpeg-image",
                                                                          	int z 					    = 0,
                                                                          	const RenderBox& box 	    = RenderBox(),
                                                                            double scale 			    = 0.01,
                                                                            int	minInt					= 0,
                                                                            int maxInt					= 65535,
                                                                            const string& cacheFolder 	= gEmptyString);

							                        ~RenderClient();

		bool							            init(				  	const string& owner 	    = gEmptyString,
                        	                        					  	const string& project 	    = gEmptyString,
                                                                          	const string& stack 	    = gEmptyString,
                                                                          	const string& imageType     = "jpeg-image",
                                                                          	int z 					    = 0,
                                                                          	const RenderBox& box 	    = RenderBox(),
                                                                            double scale 			    = 0.01,
                                                                            int	minInt					= 0,
                                                                            int maxInt					= 65535
                                                                            );

		void							            setBaseURL(const string& baseURL){mBaseURL = baseURL;}
		StringList						            getOwners();
        StringList						            getProjectsForOwner(const string& o);
        StringList						            getStacksForProject(const string& owner, const string& p);

		TMemoryStream*								getImageMemory();

		void				                        clearImageMemory();
		string				                        getURL();
		const char* 		                        getURLC(){return getURL().c_str();}
        TMemoryStream*		                        getImage(int z = 0);
        bool				                        getImageInThread(int z = 0);
        TMemoryStream*		                        reloadImage(int z = 0);
        string							            getURLForZ(int z);
        bool				                        checkCacheForCurrentURL();
        string				                        getImageLocalPathAndFileName();
        string							            getProjectName();
        string							            setLocalCacheFolder(const string& f);
        string							            getLocalCacheFolder(){return mLocalCacheFolder;}
        StringList						            getZs();
        vector<int>						            getValidZs();
		RenderBox 						            getBoxForZ(int z);
        RenderBox						            getOptimalXYBoxForZs(const vector<int>& zs = vector<int>(0));
	    vector<RenderBox>				            getBounds();
        RenderProject&					            getProject(){return mProject;}
        void										assignOnImageCallback(RCCallBack cb);
        void										copyImageData(MemoryStruct chunk);

    private:
    												//!This is the HTTP connection
		Idhttp::TIdHTTP* 	                        mC;

        											//!Memory to hold image data retrieved from server
		TMemoryStream* 		                        mImageMemory;

        											//!List of bounds
        vector<RenderBox>				            mLatestBounds;

    	int				                            mZ;
        double				                        mScale;
        string			                            mBaseURL;
        RenderProject					            mProject;
        string							            mLocalCacheFolder;
        string 			                            mImageType;
        RenderBox			                        mRenderBox;
        int								            mMinIntensity;
        int								            mMaxIntensity;
        RenderBox						            parseBoundsResponse(const string& s);
        FetchImageThread							mFetchImageThread;
};

string getImageCacheFileNameAndPathFromURL(const string& url, const string& cacheRootFolder);

#endif
