#pragma hdrstop
#include "atRenderLocalCache.h"
#include "Poco/Path.h"
#include "dslLogger.h"
#include "dslStringList.h"
#include "dslFileUtils.h"
//---------------------------------------------------------------------------
namespace at
{

using namespace Poco;
using namespace dsl;

RenderLocalCache::RenderLocalCache(const string& cr)//, RenderProject* rp)
:
mCacheRoot(cr)
{}

RenderLocalCache::~RenderLocalCache()
{}

string RenderLocalCache::getFileNameForZ(int z, const RenderProject& rp) const
{
    string zStr(toString(z));
    string name(getImageLocalCachePathAndFileName(rp, zStr));
    return name;
}

string RenderLocalCache::getImageLocalCachePath(const RenderProject& rp) const
{
    const RegionOfInterest roi = rp.getRegionOfInterest();
    stringstream s;
    s 	<< mCacheRoot << "\\"<<rp.getProjectOwner()
    	<<"\\"<<rp.getRenderProjectName()
        <<"\\"<<rp.getSelectedStackName()
        <<"\\"<<roi.getX1()<<","<<roi.getY1()<<","<<roi.getWidth()<<","<<roi.getHeight();

    return s.str();
}

bool RenderLocalCache::checkPresence(const RenderProject& rp, int z, const string& imageType)
{
    return fileExists(getImageLocalCachePathAndFileName(rp, toString(z), imageType));
}

string RenderLocalCache::getRenderProjectLocalDataRoot(const RenderProject& rp) const
{
    stringstream s;
    //Construct filePath
    s 	<< mCacheRoot << "\\"<<rp.getProjectOwner()
    	<<"\\"<<rp.getRenderProjectName();
    return s.str();
}

string RenderLocalCache::getImageLocalCachePathAndFileName(const RenderProject& rp, const string& z, const string& imageType) const
{
    stringstream s;
    const RegionOfInterest roi = rp.getRegionOfInterest();
    string theZ = z.size() > 0 ? z : toString(roi.getZ());
    //Construct filePath
	//  /render-ws/v1/owner/Deleted/project/Blag/stack/TEST_Totte_Renamed_AFF/z/3/box/-4515,-2739,9027,5472,0.1338/jpeg-image
    s << mCacheRoot << "\\"<<rp.getProjectOwner()
      <<"\\"<<rp.getRenderProjectName()
      <<"\\"<<rp.getSelectedStackName()
      <<"\\"<<roi.getX1()<<","<<roi.getY1()<<","<<roi.getWidth()<<","<<roi.getHeight()<<"\\"
      <<theZ<<"_"<< rp.getMinIntensity()<<"_"<<rp.getMaxIntensity()<<"_"<<roi.getScale();

        //Channels
        StringList channels = rp.getSelectedChannelName();
        for(int i = 0; i < channels.count(); i++)
        {
            s << "_" << channels[i];
        }

        if(imageType == "jpeg-image")
        {
            s << ".jpg";
        }
        else if(imageType == "png-image")
        {
			s << ".png";
        }
        else if(imageType == "tiff16-image")
        {
			s << ".tiff";
        }

    return s.str();
}

void RenderLocalCache::setBasePath(const string& bp)
{
    mCacheRoot = bp;
}

double RenderLocalCache::getLowestResolutionInCache(const RenderProject& rp, const RegionOfInterest& roi) const
{
    string path;
    path = joinPath(mCacheRoot, rp.getProjectOwner() ,rp.getRenderProjectName(), rp.getSelectedStackName(), roi.getFolderName());

    Log(lInfo) << "Finding files in folder: " << path;
    StringList cf(getFilesInFolder(path, "jpg"));

    double minS(1);
    for(int i = 0; i < cf.count(); i++)
    {
        StringList fNameParts(getFileNameNoPath(cf[i]), '_');

        //Last part is the scale
        if(fNameParts.count() == 5)
        {
            double value = toDouble(fNameParts[3]);
            if(value < minS)
            {
                minS = value;
            }
        }

    }
    return minS;
}

string RenderLocalCache::getBasePath() const
{
    return mCacheRoot;
}
}

