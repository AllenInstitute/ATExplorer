#include <vcl.h>
#pragma hdrstop
#include "atRenderLocalCache.h"
#include "Poco/Path.h"
#include "dslLogger.h"
#include "dslStringList.h"
#include "dslFileUtils.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace at
{

using namespace Poco;
using namespace dsl;

RenderLocalCache::RenderLocalCache(const string& cr, const RenderProject& rp)
:
mCacheRoot(cr),
mRP(rp)
{}

RenderLocalCache::~RenderLocalCache()
{}

void RenderLocalCache::setRenderProject(const RenderProject& rp)
{
    mRP = rp;
}

void RenderLocalCache::setBasePath(const string& bp)
{
    mCacheRoot = bp;
}

double RenderLocalCache::getLowestResolutionInCache(const RenderProject& rp, const RegionOfInterest& roi)
{
    mRP = rp;
    string path;
    path = joinPath(mCacheRoot, mRP.getProjectOwner() ,mRP.getRenderProjectName(), mRP.getSelectedStackName(), roi.getFolderName());

    Log(lInfo) << "Finding files in folder: " << path;
    StringList cf(getFilesInFolder(path, "jpg"));

    double minS(1);
    for(int i = 0; i < cf.count(); i++)
    {
        StringList fNameParts(getFileNameNoPath(cf[i]), '_');

        //Last part is the scale
        if(fNameParts.count() == 4)
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

string RenderLocalCache::getBasePath()
{
    return mCacheRoot;
}
}

