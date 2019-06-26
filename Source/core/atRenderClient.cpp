#pragma hdrstop
#include "atRenderClient.h"
#include <System.Classes.hpp>
#include <IdHTTP.hpp>
#include <sstream>
#include <vector>

#include "dslStringUtils.h"
#include "dslUtils.h"
#include "dslLogger.h"
#include "math/dslMathUtils.h"
#include "dslFileUtils.h"
#include "atJSMN.h"

#include "atStringUtils.h"
#include "atATEExceptions.h"
#include "atRESTRequest.h"
#include "renderAPI/atGetOwnersResponse.h"
#include "atRESTResponse.h"
//---------------------------------------------------------------------------

using std::wstring;

namespace at
{

using namespace std;
using namespace dsl;

const int HTTP_RESPONSE_OK = 200;

RenderClient::RenderClient(shared_ptr<Idhttp::TIdHTTP> c, const string& host, const string& name)
:
RESTClient(c, host),
StackDataAPI(*this),
PointMatchAPI(*this),
ServerConfigurationAPI(*this),
mFetchImageThread(shared_ptr<FetchImageThread>())
{
	mServiceParameters = new RenderServiceParameters(host);
}

RenderClient::~RenderClient()
{
    delete mServiceParameters;
}

void RenderClient::createRESTServiceParameters(const string& host)
{
	mServiceParameters = new RenderServiceParameters(host);
}

bool RenderClient::init(const string& imageType, double scale, int minInt, int maxInt)
{
    mImageType = (imageType);
//    mZ = (z);
	mScale = (scale);
	mMinIntensity = (minInt);
	mMaxIntensity = (maxInt);
    return true;
}

string RenderClient::getBaseURL()
{
    if(mServiceParameters)
    {
        return mServiceParameters->getBaseURL();
    }

    return "";
}

void RenderClient::setRenderServiceParameters(const RenderServiceParameters& rp)
{
    (*mServiceParameters) = rp;
}

const RenderServiceParameters* RenderClient::getRenderServiceParameters()
{
    return dynamic_cast<RenderServiceParameters*>(mServiceParameters);
}

void RenderClient::assignOnImageCallback(RCCallBack cb)
{
    if(!mFetchImageThread)
    {
        Log(lWarning) << "Image thread is NULL";
        return;
    }
	mFetchImageThread->onImage = cb;
}

bool RenderClient::getImageInThread(const string& z, StringList& paras, const string& channel, const RenderLocalCache& cache, const RenderProject& rp)
{

    if(!mFetchImageThread)
    {
        mFetchImageThread = shared_ptr<FetchImageThread> (new FetchImageThread(rp, *this, cache));
    }

    if(mFetchImageThread && mFetchImageThread->isRunning())
    {
        Log(lWarning) << "Image thread is not finished";
    }

	if(!mImageMemory)
    {
		mImageMemory = new TMemoryStream();
    }

	mFetchImageThread->setup(getURLForZ(toInt(z), rp), cache.getBasePath(), z);
    mFetchImageThread->addParameters(paras);
    mFetchImageThread->setChannel(channel);
	mFetchImageThread->start(true);
    return true;
}

TMemoryStream* RenderClient::getImageMemory()
{
	return mImageMemory;
}

//Move to stack API
RegionOfInterest RenderClient::getLayerBoundsForZ(int z, RenderProject& rp)
{
    return StackDataAPI.getLayerBoundsForZ(rp, z);
}

vector<RegionOfInterest> RenderClient::getLayerBounds()
{
	return mLayerBounds;
}

void RenderClient::clearImageMemory()
{
	delete mImageMemory;
    mImageMemory = NULL;
}

string RenderClient::getURLForZ(int z, const RenderProject& rp)
{
	stringstream sUrl;
    const RegionOfInterest& roi = rp.getRegionOfInterest();
    sUrl << mServiceParameters->getBaseURL();
    sUrl << "/owner/" 		<< rp.getProjectOwner();
    sUrl << "/project/" 	<< rp.getRenderProjectName();
    sUrl << "/stack/"		<< rp.getSelectedStackName();
    sUrl << "/z/"			<<z;
    sUrl << "/box/"			<<roi.getX1()<<","<<roi.getY1() << "," << (int) roi.getWidth() << ","<< (int) roi.getHeight() << ","<<mScale;
    sUrl << "/"<<mImageType;
	sUrl << "?minIntensity="<<mMinIntensity;
	sUrl << "&maxIntensity="<<mMaxIntensity;

	return sUrl.str();
}

RegionOfInterest RenderClient::getOptimalXYBoxForZs(const vector<int>& zs)
{
//	mLayerBounds.clear();
//    double xMin(0), xMax(0), yMin(0), yMax(0);
//    for(int z = 0; z < zs.size(); z++)
//    {
//        stringstream sUrl;
//        sUrl << mServiceParameters->getBaseURL();
//        sUrl << "/owner/"  	<< mRenderProject.getProjectOwner();
//        sUrl << "/project/" << mRenderProject.getRenderProjectName();
//        sUrl << "/stack/"	<<mRenderProject.getSelectedStackName()<<"/z/"<<zs[z]<<"/bounds";
//
//        //	    Log(lDebug5) << "Fetching from server using URL: "<<sUrl.str();
//        TStringStream* zstrings = new TStringStream;;
//        mC->Get(sUrl.str().c_str(), zstrings);
//
//        if( mC->ResponseCode == HTTP_RESPONSE_OK)
//        {
//            string s = stdstring(zstrings->DataString);
//            RegionOfInterest sec_bounds = parseBoundsResponse(s);
//            sec_bounds.setZ(zs[z]);
//			mLayerBounds.push_back(sec_bounds);
//
//            if(z == 0)
//            {
//                xMin = sec_bounds.getX1();
//                yMin = sec_bounds.getY1();
//                xMax = sec_bounds.getX2();
//                yMax = sec_bounds.getY2();
//            }
//            else
//            {
//                if(sec_bounds.getX1() < xMin)
//                {
//                    xMin = sec_bounds.getX1();
//                    Log(lDebug) << "XMin ("<<xMin<<") from section: " <<zs[z];
//                }
//
//                if(sec_bounds.getY1() < yMin)
//                {
//                    yMin = sec_bounds.getY1();
//                    Log(lDebug) << "YMin ("<<yMin<<") from section: " <<zs[z];
//                }
//
//                if(sec_bounds.getX2() > xMax)
//                {
//                    xMax = sec_bounds.getX2();
//                    Log(lDebug) << "XMax ("<<xMax<<") from section: " <<zs[z];
//                }
//
//                if(sec_bounds.getY2() > yMax)
//                {
//                    yMax = sec_bounds.getY2();
//                    Log(lDebug) << "yMax ("<<yMax<<") from section: " <<zs[z];
//                }
//            }
//        }
//        else
//        {
//            Log(lError) << "Failed fetching zs";
//        }
//    }
//    return RegionOfInterest(xMin, yMin, xMax-xMin, yMax -yMin);
}


}
