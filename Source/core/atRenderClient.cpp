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
#include "atExceptions.h"
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
mFetchImageThread(*this)
{
	mServiceParameters = new RenderServiceParameters(host);
}

RenderClient::~RenderClient()
{
//	delete mImageMemory;
    delete mServiceParameters;
}

void RenderClient::createRESTServiceParameters(const string& host)
{
	mServiceParameters = new RenderServiceParameters(host);
}

//RESTResponse* RenderClient::execute(RESTRequest& request)
//{
//    if(dynamic_cast<RenderStackDataAPI*>(request.getRequestorObject()))
//    {
//    	return StackDataAPI.execute(request);
//    }
////
////        return new GetOwnersRESTResponse(r);
////    }
//
//    //Create response object
//    string r = executeRequest(request);
//    return new RESTResponse(r);
//}

bool RenderClient::init(const string& imageType,
						int z, double scale, int minInt, int maxInt)
{
    mImageType = (imageType);
    mZ = (z);
	mScale = (scale);
	mMinIntensity = (minInt);
	mMaxIntensity = (maxInt);
//    setLocalCacheFolder(mRenderProject.getLocalCacheFolder());
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

string RenderClient::request(const string& r)
{
//    try
//    {
//        TStringStream* zstrings = new TStringStream;;
//        mC->Get(r.c_str(), zstrings);
//
//        if(mC->ResponseCode != HTTP_RESPONSE_OK)
//        {
//            Log(lError) << "The request \"" << r << "\" failed";
//            return string("");
//        }
//
//        string json = stdstring(zstrings->DataString);
//	    return json;
//    }
//    catch(...)
//    {
//        Log(lError) << "Handle error..";
//        return "";
//    }
}

void RenderClient::setRenderServiceParameters(RenderServiceParameters* rp)
{
    mServiceParameters = rp;
}

const RenderServiceParameters* RenderClient::getRenderServiceParameters()
{
    return dynamic_cast<RenderServiceParameters*>(mServiceParameters);
}

void RenderClient::setSelectedStackName(const string& sName)
{
//    mRenderProject.setSelectedStackName(sName);
}

string RenderClient::getCacheRoot()
{
//    return mCache.getBasePath();
}

double RenderClient::getLowestResolutionInCache(const RegionOfInterest& roi)
{
//    return mCache.getLowestResolutionInCache(mRenderProject, roi);
}

const char* RenderClient::getURLC()
{
	return getURL().c_str();
}

string RenderClient::getLocalCacheFolder()
{
//	return mCache.getBasePath();
}

RenderProject& RenderClient::getProject()
{
//	return mRenderProject;
}

RenderProject RenderClient::getRenderProject()
{
//	return mRenderProject;
}

void RenderClient::setRenderProject(const RenderProject& rp)
{
//	mRenderProject = rp;
}

void RenderClient::assignOnImageCallback(RCCallBack cb)
{
	mFetchImageThread.onImage = cb;
}

StringList RenderClient::getROIFoldersForCurrentStack()
{
//    //Create basepath
//    stringstream path;
//    path << joinPath(mCache.getBasePath(), mRenderProject.getProjectOwner(), mRenderProject.getRenderProjectName(), mRenderProject.getSelectedStackName());
//
//    return getSubFoldersInFolder(path.str(), false);
}

Idhttp::TIdHTTP* RenderClient::getConnection()
{
//    return mC;
}

void RenderClient::assignConnection(Idhttp::TIdHTTP* c)
{
//    mC = c;
}

void RenderClient::copyImageData(MemoryStruct chunk)
{
	try
    {
//	    mImageMemory->Clear();
//        mImageMemory->Position = 0;
//		mImageMemory->ReadBuffer(&chunk.memory[0], chunk.size);
    }
    catch(const EReadError& e)
    {
    	Log(lError) << "Failed to read memory buffer";
    }
}

RenderProject RenderClient::getCurrentProject()
{
//    return mRenderProject;
}

void RenderClient::setLocalCacheFolder(const string& f)
{
//	mCache.setBasePath(f);
}


StringList RenderClient::getChannelsInStack(const string& stackName)
{
//	//http://localhost/render-ws/v1/owner/ATExplorer/project/M33/stack/STI_FF_Session1?api_key=stacks
//    if(!mServiceParameters)
//    {
//        return StringList();
//    }
//
//    stringstream sUrl;
//    sUrl << mServiceParameters->getBaseURL();
//    sUrl << "/owner/" 	<<	mRenderProject.getProjectOwner();
//    sUrl << "/project/" <<	mRenderProject.getRenderProjectName();
//    sUrl << "/stack/" 	<<	stackName << "?api_key=stacks";
//    Log(lDebug5) << "Fetching channels: "<<sUrl.str();
//
//    try
//    {
//        TStringStream* zstrings = new TStringStream;;
//        mLastRequestURL = sUrl.str();
//        mC->Get(mLastRequestURL.c_str(), zstrings);
//
//        if( mC->ResponseCode != HTTP_RESPONSE_OK)
//        {
//            Log(lError) << "Bad HTTP RESPONSE when getching channel names";
//	        return StringList();
//        }
//
//        string s = stdstring(zstrings->DataString);
//
//        //Parse JSON
//        jsmn_parser parser;
//        jsmn_init(&parser);
//
//        int r = jsmn_parse(&parser, s.c_str(), s.size(), NULL, 0);
//        if(r)
//        {
//            jsmn_init(&parser);
//            jsmntok_t* tokens = new jsmntok_t[r];
//            r = jsmn_parse(&parser, s.c_str(), s.size(), &tokens[0], r);
//            if(r)
//            {
//                //find string token "channelNames"
//                for(int i = 0; i < r; i++)
//                {
//                    jsmntok_t tok = tokens[i];
//                    if(tok.type == JSMN_STRING)
//                    {
//                        string sToken = toString(tok, s);
//                        if(sToken == "channelNames")
//                        {
//                            //Next one is an ARRAY object holding the channels..
//                            //parse it into a string
//                            jsmntok_t chs_tok = tokens[i + 1];
//
//                            string chs = toString(chs_tok, s);
//                            chs = stripCharacters(" []\"", chs);
//                            //Get them all as a string..
//                            StringList channels(chs, ',');
//                            channels.sort();
//                            return channels;
//                        }
//                    }
//                }
//            }
//        }
//
//    	Log(lError) << "Failed fetching channels";
//        return StringList();
//    }
//    catch(...)
//    {
//    	Log(lError) << "Failed fetching channels";
//        return StringList();
//    }
}


StringList RenderClient::getServerProperties()
{
//    stringstream sUrl;
//    sUrl << mServiceParameters->getBaseURL();
//    sUrl << "/serverProperties";
//    Log(lDebug5) << "Fetching Server Properties: "<<sUrl.str();
//    StringList response;
//
//    try
//    {
//        TStringStream* zstrings = new TStringStream;;
//        mLastRequestURL = sUrl.str();
//        mC->Get(mLastRequestURL.c_str(), zstrings);
//
//        if( mC->ResponseCode == HTTP_RESPONSE_OK)
//        {
//            string s = stdstring(zstrings->DataString);
//            response.appendList(StringList(s, ','));
//        }
//    }
//    catch(...)
//    {
//    	Log(lError) << "Failed fetching response";
//    }
//
//    return response;
}

bool RenderClient::getImageInThread(int z, StringList& paras)
{
//	mZ = z;
//
//	if(!mImageMemory)
//    {
//		mImageMemory = new TMemoryStream();
//    }
//
//	mFetchImageThread.setup(getURLForZ(z), mCache.getBasePath());
//    mFetchImageThread.addParameters(paras);
//    mFetchImageThread.setChannel(mRenderProject.getSelectedChannelName());
//	mFetchImageThread.start(true);
    return true;
}

TMemoryStream* RenderClient::getImageMemory()
{
	return mImageMemory;
}

TMemoryStream* RenderClient::reloadImage(int z)
{
//	mZ = z;
//	if(!mImageMemory)
//    {
//		mImageMemory = new TMemoryStream();
//    }
//	//First check if we already is having this data
//    Log(lDebug3) << "Reloading Image";
//
//    try
//    {
//        mC->Get(getURLC(), mImageMemory);
//    }
//    catch(...)
//    {
//        Log(lError) << "There was an uncaught ERROR!";
//    }
//
//    //Save to cache (in a thread)
//    if(createFolder(getFilePath(getImageLocalCachePathAndFileName())))
//    {
//        mImageMemory->SaveToFile(getImageLocalCachePathAndFileName().c_str());
//    }
//
//    return mImageMemory;
}

RegionOfInterest RenderClient::getLayerBoundsForZ(int z)
{
//    stringstream sUrl;
//    sUrl << mServiceParameters->getBaseURL();
//    sUrl << "/owner/" 		<< mRenderProject.getProjectOwner();
//    sUrl << "/project/" 	<< mRenderProject.getRenderProjectName();
//    sUrl << "/stack/"		<<mRenderProject.getSelectedStackName();
//    sUrl <<"/z/"<<z   	 	<<"/bounds";
//
//    Log(lDebug5) << "Fetching from server using URL: "<<sUrl.str();
//    TStringStream* zstrings = new TStringStream;;
//    mC->Get(sUrl.str().c_str(), zstrings);
//	RegionOfInterest b;
//
//    if( mC->ResponseCode == HTTP_RESPONSE_OK)
//    {
//        string s = stdstring(zstrings->DataString);
//        b = parseBoundsResponse(s);
//    }
//    else
//    {
//        Log(lError) << "Failed fetching renderbox";
//    }
//
//    b.setZ(z);
//    return b;
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

vector<RegionOfInterest> RenderClient::getLayerBounds()
{
	return mLayerBounds;
}

string RenderClient::getImageLocalCachePath()
{
//	return getImageLocalCachePathFromURL(getURL(), mCache.getBasePath());
}

string RenderClient::getImageLocalCachePathAndFileNameForZ(int z, const string& chs)
{
//	string url(getURLForZ(z));
//    return getImageLocalCacheFileNameAndPathFromURL(url, mCache.getBasePath(), chs);
}

string RenderClient::getImageLocalCachePathAndFileName()
{
//	return getImageLocalCacheFileNameAndPathFromURL(getURL(), mCache.getBasePath(), mRenderProject.getSelectedChannelName());
}

bool RenderClient::checkCacheForCurrentURL()
{
//	return fileExists(getImageLocalCachePathAndFileName());
}

void RenderClient::clearImageMemory()
{
	delete mImageMemory;
    mImageMemory = NULL;
}

string RenderClient::getURLForZ(int z)
{
//	stringstream sUrl;
//    RegionOfInterest& roi = mRenderProject.getCurrentRegionOfInterestReference();
//    sUrl << mServiceParameters->getBaseURL();
//    sUrl << "/owner/" 		<< mRenderProject.getProjectOwner();
//    sUrl << "/project/" 	<< mRenderProject.getRenderProjectName();
//    sUrl << "/stack/"		<< mRenderProject.getSelectedStackName();
//    sUrl << "/z/"			<<z;
//    sUrl << "/box/"			<<roi.getX1()<<","<<roi.getY1() << "," << (int) roi.getWidth() << ","<< (int) roi.getHeight() << ","<<mScale;
//    sUrl << "/"<<mImageType;
//	sUrl << "?minIntensity="<<mMinIntensity;
//	sUrl << "&maxIntensity="<<mMaxIntensity;
//
//	return sUrl.str();
}

string RenderClient::getURL()
{
    return getURLForZ(mZ);
}

StringList RenderClient::getZs()
{
	StringList validZs = getValidZs();

    StringList missingZs;
    int nrOfMissingZs = 0;

    for(int i = 0; i < validZs.count(); i++)
    {
    	if(toInt(validZs[i]) != (i + nrOfMissingZs))
        {
        	missingZs.append(dsl::toString(i + nrOfMissingZs));
			nrOfMissingZs++;
        }
    }

    StringList all;
    all.append(validZs.asString(','));
	all.append(missingZs.asString(','));
	return all;
}

vector<int> RenderClient::getValidZs()
{
//	StringList zs;
//	stringstream sUrl;
//    sUrl << mServiceParameters->getBaseURL();
//    sUrl << "/owner/"    << mRenderProject.getProjectOwner();
//    sUrl << "/project/" << 	mRenderProject.getRenderProjectName();
//    sUrl << "/stack/"	<<	mRenderProject.getSelectedStackName();
//    sUrl <<"/zValues";
//
//    Log(lDebug3) << "Get Valid Z: "<<sUrl.str();
//
//    try
//    {
//        TStringStream* zstrings = new TStringStream;;
//        mC->Get(sUrl.str().c_str(), zstrings);
//
//
//        if( mC->ResponseCode == HTTP_RESPONSE_OK)
//        {
//            string s = stdstring(zstrings->DataString);
//            s = stripCharacters("[]", s);
//            zs.appendList(StringList(s,','));
//        }
//        else
//        {
//            Log(lError) << "Failed fetching zs";
//        }
//
//        vector<int> zInts;
//        for(int i = 0; i < zs.count(); i++)
//        {
//            zInts.push_back(toInt(zs[i]));
//        }
//
//        return zInts;
//    }
//    catch(...)
//    {
//    	Log(lError) << "There was an uncaught error";
//    }
//    return vector<int>();
}

bool RenderClient::renameStack(const string& currentStackName, const string& newName)
{
//	stringstream sUrl;
//    sUrl << mServiceParameters->getBaseURL();
//    sUrl << "/owner/"    << mRenderProject.getProjectOwner();
//    sUrl << "/project/" << 	mRenderProject.getRenderProjectName();
//    sUrl << "/stack/"	<<	mRenderProject.getSelectedStackName();
//
////    TStringStream* strings = new TStringStream;;
////    mC->Put()
//    return true;
}

RegionOfInterest RenderClient::parseBoundsResponse(const string& _s)
{
//	RegionOfInterest bounds;
//    string s = stripCharacters("{}", _s);
//    StringList l(s, ',');
//    if(l.size() == 6)
//    {
//    	StringList xMin(l[0], ':');
//    	StringList yMin(l[1], ':');
//    	StringList xMax(l[3], ':');
//    	StringList yMax(l[4], ':');
//
//        bounds.setX1(toDouble(xMin[1]));
//        bounds.setY1(toDouble(yMin[1]));
//        bounds.setX2(toDouble(xMax[1]));
//        bounds.setY2(toDouble(yMax[1]));
//    }
//    else
//    {
//    	Log(lError) << "Bad bounds format..";
//    }
//    return bounds;
}

string RenderClient::getLastRequestURL()
{
    return mLastRequestURL;
}


}
