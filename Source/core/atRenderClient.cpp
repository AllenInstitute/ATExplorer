#pragma hdrstop
#include <System.Classes.hpp>
#include <IdHTTP.hpp>
#include <sstream>
#include <vector>
#include "atRenderClient.h"
#include "dslStringUtils.h"
#include "dslUtils.h"
//#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "dslPoint.h"
#include "dslMathUtils.h"
#include "dslFileUtils.h"
//---------------------------------------------------------------------------


using std::wstring;

string stdstring(const String& str)
{
    wstring test(str.c_str());
    return dsl::stdstr(test);
}

namespace at
{

using namespace std;
using namespace dsl;

const int HTTP_RESPONSE_OK = 200;

RenderClient::RenderClient(RenderProject& rp, Idhttp::TIdHTTP* c, const RenderServiceParameters& p, const string& cacheFolder)
:
mC(c),
mRenderProject(rp),
mRenderServiceURL(p),
mCache(cacheFolder, mRenderProject),
mFetchImageThread(*this),
mImageType("jpeg-image")
{
	mImageMemory = new TMemoryStream();
}

bool RenderClient::init(const string& imageType,
						int z, double scale, int minInt, int maxInt)
{
    mImageType = (imageType);
    mZ = (z);
	mScale = (scale);
	mMinIntensity = (minInt);
	mMaxIntensity = (maxInt);
    setLocalCacheFolder(mRenderProject.getLocalCacheFolder());
    return true;
}

RenderClient::~RenderClient()
{
	delete mImageMemory;
}

RenderServiceParameters RenderClient::getRenderServiceParameters()
{
    return mRenderServiceURL;
}

void RenderClient::setSelectedStackName(const string& sName)
{
    mRenderProject.setSelectedStackName(sName);
}

string RenderClient::getCacheRoot()
{
    return mCache.getBasePath();
}
double RenderClient::getLowestResolutionInCache(const RegionOfInterest& roi)
{
    return mCache.getLowestResolutionInCache(mRenderProject, roi);
}

void RenderClient::setBaseURL(const string& baseURL)
{
	mRenderServiceURL.setBaseURL(baseURL);
}

const char* RenderClient::getURLC()
{
	return getURL().c_str();
}

string RenderClient::getLocalCacheFolder()
{
	return mCache.getBasePath();
}

RenderProject& RenderClient::getProject()
{
	return mRenderProject;
}

string RenderClient::getBaseURL()
{
	return mRenderServiceURL.getBaseURL();
}

RenderProject RenderClient::getRenderProject()
{
	return mRenderProject;
}

void RenderClient::setRenderProject(const RenderProject& rp)
{
	mRenderProject = rp;
}

void RenderClient::assignOnImageCallback(RCCallBack cb)
{
	mFetchImageThread.onImage = cb;
}

StringList RenderClient::getROIFoldersForCurrentStack()
{
    //Create basepath
    stringstream path;
    path << joinPath(mCache.getBasePath(), mRenderProject.getProjectOwner(), mRenderProject.getRenderProjectName(), mRenderProject.getSelectedStackName());

    return getSubFoldersInFolder(path.str(), false);
}

Idhttp::TIdHTTP* RenderClient::getConnection()
{
    return mC;
}

void RenderClient::assignConnection(Idhttp::TIdHTTP* c)
{
    mC = c;
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
    return mRenderProject;
}

void RenderClient::setLocalCacheFolder(const string& f)
{
	mCache.setBasePath(f);
}

StringList RenderClient::getOwners()
{
    stringstream sUrl;
    sUrl << mRenderServiceURL.getBaseURL() <<":"<< mRenderServiceURL.getPortNr() << mRenderServiceURL.getVersion();
    sUrl << "/owners";
    Log(lDebug5) << "Fetching owners: "<<sUrl.str();
    StringList owners;

    try
    {

        TStringStream* zstrings = new TStringStream;;
        mC->Get(sUrl.str().c_str(), zstrings);

        if( mC->ResponseCode == HTTP_RESPONSE_OK)
        {
            string s = stdstring(zstrings->DataString);
            s = stripCharacters("\"[]", s);
            owners.appendList(StringList(s, ','));
        }
    }
    catch(...)
    {
    	Log(lError) << "Failed fetching owners";
    }

    owners.sort();
    return owners;
}

StringList RenderClient::getProjectsForOwner(const string& o)
{
    stringstream sUrl;
    sUrl << mRenderServiceURL.asString();
    sUrl << "/owner/" << o;
    sUrl << "/stackIds";
    Log(lDebug5) << "Fetching projects for owner: "<<sUrl.str();

    StringList projects;
    TStringStream* zstrings = new TStringStream;;
    mC->Get(sUrl.str().c_str(), zstrings);

    if( mC->ResponseCode == HTTP_RESPONSE_OK)
    {
        string s = stdstring(zstrings->DataString);
        s = stripCharacters("\"[]{}", s);
        Log(lDebug5) << "Render Response: "<<s;
        //Parse result
        StringList t1(s,',');

        //Go trough list and get unique projects
        for(int i = 0; i < t1.count(); i++)
        {
        	string line = t1[i];
            if(startsWith("project", t1[i]))
            {
            	StringList l(t1[i], ':');
                if(l.count() == 2)
                {
                	if(!projects.contains(l[1]))
                    {
                		projects.append(l[1]);
                    }
                }
            }
        }
    }
    else
    {
        Log(lError) << "Failed fetching projects";
    }

    projects.sort();
    return projects;
}

bool RenderClient::getImageInThread(int z, StringList& paras)
{
	mZ = z;

	if(!mImageMemory)
    {
		mImageMemory = new TMemoryStream();
    }

	mFetchImageThread.setup(getURLForZ(z), mCache.getBasePath());
    mFetchImageThread.addParameters(paras);
	mFetchImageThread.start(true);
    return true;
}

TMemoryStream* RenderClient::getImageMemory()
{
	return mImageMemory;
}

TMemoryStream* RenderClient::reloadImage(int z)
{
	mZ = z;
	if(!mImageMemory)
    {
		mImageMemory = new TMemoryStream();
    }
	//First check if we already is having this data
    Log(lDebug3) << "Reloading Image";

    try
    {
        mC->Get(getURLC(), mImageMemory);
    }
    catch(...)
    {
        Log(lError) << "There was an uncaught ERROR!";
    }

    //Save to cache (in a thread)
    if(createFolder(getFilePath(getImageLocalCachePathAndFileName())))
    {
        mImageMemory->SaveToFile(getImageLocalCachePathAndFileName().c_str());
    }

    return mImageMemory;
}

RegionOfInterest RenderClient::getLayerBoundsForZ(int z)
{
    stringstream sUrl;
    sUrl << mRenderServiceURL.asString();
    sUrl << "/owner/" 		<< mRenderProject.getProjectOwner();
    sUrl << "/project/" 	<< mRenderProject.getRenderProjectName();
    sUrl << "/stack/"		<<mRenderProject.getSelectedStackName();
    sUrl <<"/z/"<<z   	 	<<"/bounds";

    Log(lDebug5) << "Fetching from server using URL: "<<sUrl.str();
    TStringStream* zstrings = new TStringStream;;
    mC->Get(sUrl.str().c_str(), zstrings);
	RegionOfInterest b;

    if( mC->ResponseCode == HTTP_RESPONSE_OK)
    {
        string s = stdstring(zstrings->DataString);
        b = parseBoundsResponse(s);
    }
    else
    {
        Log(lError) << "Failed fetching renderbox";
    }

    b.setZ(z);
    return b;
}

RegionOfInterest RenderClient::getOptimalXYBoxForZs(const vector<int>& zs)
{
	mLayerBounds.clear();
    double xMin(0), xMax(0), yMin(0), yMax(0);
    for(int z = 0; z < zs.size(); z++)
    {
        stringstream sUrl;
        sUrl << mRenderServiceURL.asString();
        sUrl << "/owner/"  	<< mRenderProject.getProjectOwner();
        sUrl << "/project/" << mRenderProject.getRenderProjectName();
        sUrl << "/stack/"	<<mRenderProject.getSelectedStackName()<<"/z/"<<zs[z]<<"/bounds";

        //	    Log(lDebug5) << "Fetching from server using URL: "<<sUrl.str();
        TStringStream* zstrings = new TStringStream;;
        mC->Get(sUrl.str().c_str(), zstrings);

        if( mC->ResponseCode == HTTP_RESPONSE_OK)
        {
            string s = stdstring(zstrings->DataString);
            RegionOfInterest sec_bounds = parseBoundsResponse(s);
            sec_bounds.setZ(zs[z]);
			mLayerBounds.push_back(sec_bounds);

            if(z == 0)
            {
                xMin = sec_bounds.getX1();
                yMin = sec_bounds.getY1();
                xMax = sec_bounds.getX2();
                yMax = sec_bounds.getY2();
            }
            else
            {
                if(sec_bounds.getX1() < xMin)
                {
                    xMin = sec_bounds.getX1();
                    Log(lDebug) << "XMin ("<<xMin<<") from section: " <<zs[z];
                }

                if(sec_bounds.getY1() < yMin)
                {
                    yMin = sec_bounds.getY1();
                    Log(lDebug) << "YMin ("<<yMin<<") from section: " <<zs[z];
                }

                if(sec_bounds.getX2() > xMax)
                {
                    xMax = sec_bounds.getX2();
                    Log(lDebug) << "XMax ("<<xMax<<") from section: " <<zs[z];
                }

                if(sec_bounds.getY2() > yMax)
                {
                    yMax = sec_bounds.getY2();
                    Log(lDebug) << "yMax ("<<yMax<<") from section: " <<zs[z];
                }
            }
        }
        else
        {
            Log(lError) << "Failed fetching zs";
        }
    }
    return RegionOfInterest(xMin, yMin, xMax-xMin, yMax -yMin);
}

vector<RegionOfInterest> RenderClient::getLayerBounds()
{
	return mLayerBounds;
}

string RenderClient::getImageLocalCachePath()
{
	return getImageLocalCachePathFromURL(getURL(), mCache.getBasePath());
}

string RenderClient::getImageLocalCachePathAndFileNameForZ(int z)
{
	string url(getURLForZ(z));
    return getImageLocalCacheFileNameAndPathFromURL(url, mCache.getBasePath());
}

string RenderClient::getImageLocalCachePathAndFileName()
{
	return getImageLocalCacheFileNameAndPathFromURL(getURL(), mCache.getBasePath());
}

bool RenderClient::checkCacheForCurrentURL()
{
	return fileExists(getImageLocalCachePathAndFileName());
}

void RenderClient::clearImageMemory()
{
	delete mImageMemory;
    mImageMemory = NULL;
}

string RenderClient::getURLForZ(int z)
{
	stringstream sUrl;
    RegionOfInterest& roi = mRenderProject.getCurrentRegionOfInterestReference();
    sUrl << mRenderServiceURL.asString();
    sUrl << "/owner/" 		<< mRenderProject.getProjectOwner();
    sUrl << "/project/" 	<< mRenderProject.getRenderProjectName();
    sUrl << "/stack/"		<< mRenderProject.getSelectedStackName();
    sUrl << "/z/"			<<z;
    sUrl << "/box/"			<<roi.getX1()<<","<<roi.getY1() << "," << (int) roi.getWidth() << ","<< (int) roi.getHeight() << ","<<mScale;
    sUrl << "/"<<mImageType;
	sUrl << "?minIntensity="<<mMinIntensity;
	sUrl << "&maxIntensity="<<mMaxIntensity;

	return sUrl.str();
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
	StringList zs;
	stringstream sUrl;
    sUrl << mRenderServiceURL.asString();
    sUrl << "/owner/"    << mRenderProject.getProjectOwner();
    sUrl << "/project/" << 	mRenderProject.getRenderProjectName();
    sUrl << "/stack/"	<<	mRenderProject.getSelectedStackName();
    sUrl <<"/zValues";

    Log(lDebug3) << "Get Valid Z: "<<sUrl.str();

    try
    {
        TStringStream* zstrings = new TStringStream;;
        mC->Get(sUrl.str().c_str(), zstrings);


        if( mC->ResponseCode == HTTP_RESPONSE_OK)
        {
            string s = stdstring(zstrings->DataString);
            s = stripCharacters("[]", s);
            zs.appendList(StringList(s,','));
        }
        else
        {
            Log(lError) << "Failed fetching zs";
        }

        vector<int> zInts;
        for(int i = 0; i < zs.count(); i++)
        {
            zInts.push_back(toInt(zs[i]));
        }

        return zInts;
    }
    catch(...)
    {
    	Log(lError) << "There was an uncaught error";
    }
    return vector<int>();
}

bool RenderClient::renameStack(const string& currentStackName, const string& newName)
{
	stringstream sUrl;
    sUrl << mRenderServiceURL.asString();
    sUrl << "/owner/"    << mRenderProject.getProjectOwner();
    sUrl << "/project/" << 	mRenderProject.getRenderProjectName();
    sUrl << "/stack/"	<<	mRenderProject.getSelectedStackName();

//    TStringStream* strings = new TStringStream;;
//    mC->Put()
    return true;
}

RegionOfInterest RenderClient::parseBoundsResponse(const string& _s)
{
	RegionOfInterest bounds;
    string s = stripCharacters("{}", _s);
    StringList l(s, ',');
    if(l.size() == 6)
    {
    	StringList xMin(l[0], ':');
    	StringList yMin(l[1], ':');
    	StringList xMax(l[3], ':');
    	StringList yMax(l[4], ':');

        bounds.setX1(toDouble(xMin[1]));
        bounds.setY1(toDouble(yMin[1]));
        bounds.setX2(toDouble(xMax[1]));
        bounds.setY2(toDouble(yMax[1]));
    }
    else
    {
    	Log(lError) << "Bad bounds format..";
    }
    return bounds;
}

StringList RenderClient::getStacksForProject(const string& owner, const string& project)
{
    stringstream sUrl;
    sUrl << mRenderServiceURL.asString();
    sUrl << "/owner/"<<owner;
    sUrl << "/stackIds";
    Log(lDebug5) << "Fetching stackId data using URL: "<<sUrl.str();

    StringList stacks;
    TStringStream* zstrings = new TStringStream;;
    try
    {
        mC->Get(sUrl.str().c_str(), zstrings);

        if( mC->ResponseCode == HTTP_RESPONSE_OK)
        {
            string s = stdstring(zstrings->DataString);
            s = stripCharacters("\"[]}", s);
            Log(lDebug3) << "Got Render Data String: " << s;

            //Parse result
            StringList t1(s,'{');

            //Go trough list and get unique stacks
            for(int i = 0; i < t1.count(); i++)
            {
                string line = t1[i];
                if(contains(project, t1[i]))
                {
                    StringList l(t1[i], ',');
                    if(l.count() == 3)
                    {
                        StringList l2(l[2], ':');
                        if(l2.count() == 2 && !stacks.contains(l[2]))
                        {
                            stacks.append(l2[1]);
                        }
                    }
                }
            }
        }
    }
    catch(...)
    {
        Log(lError) << "Failed fetching owners";
    }

    stacks.sort();
    return stacks;
}

}
