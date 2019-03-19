#pragma hdrstop
#include "atRenderLayer.h"
#include "dslStringList.h"
#include "dslNameValue.h"
#include "dslFileUtils.h"
#include <sstream>

//---------------------------------------------------------------------------
namespace at
{

using namespace dsl;

RenderLayer::RenderLayer(const string& url, const string& localCacheRootFolder)
:
mURL(url),
mRenderProject(url),
mCache(localCacheRootFolder),
mScheme(mURL.getScheme()),
mAuthority(mURL.getAuthority()),
mHost(mURL.getHost()),
mPort(mURL.getPort()),
mPath(mURL.getPath()),   //"/render-ws/v1/owner/Deleted/project/Blag/stack/TEST_Totte_Renamed_AFF/z/5/box/-4515,-2739,9027,5472,0.1338/jpeg-image"
mQuery(mURL.getQuery()), //"minIntensity=0&maxIntensity=6000"
mFragment(mURL.getFragment()),
mPathEtc(mURL.getPathEtc())
{
    //Parse it..
    //Get min and max intensity from query
    StringList intensities(mQuery, '&');
    if(intensities.count() == 2)
    {
        NameValue<int> min(intensities[0]);
        NameValue<int> max(intensities[1]);
        mMinIntensity = min.getValue();
        mMaxIntensity = max.getValue();
    }

    //Get Z and box from the path
    string path (mURL.getPath());
	//  /render-ws/v1/owner/Deleted/project/Blag/stack/TEST_Totte_Renamed_AFF/z/3/box/-4515,-2739,9027,5472,0.1338/jpeg-image
    //0 /1        /2/3     /4      /5      /6   /7    /8                     /9/10/11/12                          /13
    StringList pairs(path, '/');

    if(pairs.count() != 14)
    {
        throw("Bad stuff...");
    }

    mZ 	= toInt(pairs[10]);
    mRegionOfInterest = RegionOfInterest(pairs[12]);
    mScale = mRegionOfInterest.getScale();
    mImageType = pairs[13];
}

RenderLayer::RenderLayer(RenderProject& rp, const RegionOfInterest& roi, const string& localCacheRootFolder)
:
mRenderProject(rp),
mRegionOfInterest(roi),
mCache(localCacheRootFolder)
{}

bool RenderLayer::existInCache(const string& f)
{
//    return fileExists(getImageLocalCachePathAndFileName(f, mChannels));
}

string RenderLayer::getURL()
{
    return "";
}

int RenderLayer::getZ()
{
    return mZ;
}

RegionOfInterest RenderLayer::getRegionOfInterest()
{
    return mRegionOfInterest;
}

int RenderLayer::getMinIntensity()
{
    return mMinIntensity;
}

int RenderLayer::getMaxIntensity()
{
    return mMaxIntensity;
}

RenderProject RenderLayer::getRenderProject()
{
    return mRenderProject;
}

}

