#pragma hdrstop
#include <System.Classes.hpp>
#include <IdHTTP.hpp>
#include <sstream>
#include <vector>
#include "atRenderClient.h"
#include "dslStringUtils.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "dslPoint.h"
#include "dslMathUtils.h"
//---------------------------------------------------------------------------
using namespace std;
using namespace dsl;

const int HTTP_RESPONSE_OK = 200;

RenderClient::RenderClient(Idhttp::TIdHTTP* c,  const string& baseURL, const string& owner,
                            const string& project, const string& stack,
                            const string& imageType, int z, const RenderBox& box, double scale, int minInt, int maxInt, const string& cacheFolder)
:
mC(c),
mBaseURL(baseURL),
mProject(project, owner, project, stack),
mImageType(imageType),
mZ(z),
mRenderBox(box),
mScale(scale),
mMinIntensity(minInt),
mMaxIntensity(maxInt),
mLocalCacheFolder(cacheFolder),
mFetchImageThread(*this)
{
	mImageMemory = new TMemoryStream();
}

bool RenderClient::init(const string& owner, const string& project,
		const string& stack, const string& imageType, int z, const RenderBox& box, double scale, int minInt, int maxInt)
{
    mProject.setupForStack(owner, project, stack);
    mImageType = (imageType);
    mZ = (z);
    mRenderBox = (box);
	mScale = (scale);
	mMinIntensity = (minInt);
	mMaxIntensity = (maxInt);
}

RenderClient::~RenderClient()
{
	delete mImageMemory;
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

//string RenderClient::getProjectName()
//{
//	return mProject.getProjectName();
//}

string RenderClient::setLocalCacheFolder(const string& f)
{
	mLocalCacheFolder = f;
    return mLocalCacheFolder;
}

StringList RenderClient::getOwners()
{
    stringstream sUrl;
    sUrl << mBaseURL;
    sUrl << "/owners";
    Log(lDebug5) << "Fetching owners using URL: "<<sUrl.str();

    StringList owners;
    TStringStream* zstrings = new TStringStream;;
    mC->Get(sUrl.str().c_str(), zstrings);

    if( mC->ResponseCode == HTTP_RESPONSE_OK)
    {
        string s = stdstr(zstrings->DataString);
        s = stripCharacters("\"[]", s);
        owners.appendList(StringList(s, ','));
    }
    else
    {
        Log(lError) << "Failed fetching owners";
    }

    owners.sort();
    return owners;
}

StringList RenderClient::getProjectsForOwner(const string& o)
{
    stringstream sUrl;
    sUrl << mBaseURL;
    sUrl << "/owner/"<<o;
    sUrl << "/stackIds";
    Log(lDebug5) << "Fetching stackId data using URL: "<<sUrl.str();

    StringList projects;
    TStringStream* zstrings = new TStringStream;;
    mC->Get(sUrl.str().c_str(), zstrings);

    if( mC->ResponseCode == HTTP_RESPONSE_OK)
    {
        string s = stdstr(zstrings->DataString);
        s = stripCharacters("\"[]{}", s);
        Log(lInfo) << s;
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

void RenderClient::assignOnImageCallback(RCCallBack cb)
{
	mFetchImageThread.onImage = cb;
}

bool RenderClient::getImageInThread(int z)
{
	mZ = z;

	if(!mImageMemory)
    {
		mImageMemory = new TMemoryStream();
    }

	mFetchImageThread.setup(getURLForZ(z), mLocalCacheFolder);
	mFetchImageThread.start(true);
    return true;
}

TMemoryStream* RenderClient::getImage(int z)
{
	mZ = z;

	if(!mImageMemory)
    {
		mImageMemory = new TMemoryStream();
    }

	//First check if we already is having this data
    if(checkCacheForCurrentURL())
    {
        Log(lInfo) << "Fetching from cache";
    	mImageMemory->LoadFromFile(getImageLocalPathAndFileName().c_str());
	    return mImageMemory;
    }
    else
    {
        Log(lInfo) << "Fetching from server";

        try
        {
	    	mC->Get(getURLC(), mImageMemory);

            //Save to cache (in a thread)
            if(createFolder(getFilePath(getImageLocalPathAndFileName())))
            {
                mImageMemory->SaveToFile(getImageLocalPathAndFileName().c_str());
            }
            return mImageMemory;
        }
        catch(...)
        {
        	Log(lError) << "There was an uncaught ERROR!";
            delete mImageMemory;
            mImageMemory = NULL;
        }
    }
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
    Log(lInfo) << "Fetching from server";

    try
    {
        mC->Get(getURLC(), mImageMemory);
    }
    catch(...)
    {
        Log(lError) << "There was an uncaught ERROR!";
    }

    //Save to cache (in a thread)
    if(createFolder(getFilePath(getImageLocalPathAndFileName())))
    {
        mImageMemory->SaveToFile(getImageLocalPathAndFileName().c_str());
    }

    return mImageMemory;
}

RenderBox RenderClient::getBoxForZ(int z)
{
    stringstream sUrl;
    sUrl << mBaseURL;
    sUrl << "/owner/" 		<< mProject.getProjectOwner();
    sUrl << "/project/" 	<< mProject.getProject();
    sUrl << "/stack/"		<<mProject.getCurrentStackName();
    sUrl <<"/z/"<<z   	 	<<"/bounds";

    Log(lDebug5) << "Fetching from server using URL: "<<sUrl.str();
    TStringStream* zstrings = new TStringStream;;
    mC->Get(sUrl.str().c_str(), zstrings);
	RenderBox b;

    if( mC->ResponseCode == HTTP_RESPONSE_OK)
    {
        string s = stdstr(zstrings->DataString);
        b = parseBoundsResponse(s);
    }
    else
    {
        Log(lError) << "Failed fetching renderbox";
    }

    b.setZ(z);
    return b;
}

RenderBox RenderClient::getOptimalXYBoxForZs(const vector<int>& zs)
{
	mLatestBounds.clear();
    double xMin(0), xMax(0), yMin(0), yMax(0);
    for(int z = 0; z < zs.size(); z++)
    {
        stringstream sUrl;
        sUrl << mBaseURL;
        sUrl << "/owner/" 		<< mProject.getProjectOwner();
        sUrl << "/project/" << mProject.getProject();
        sUrl << "/stack/"	<<mProject.getCurrentStackName()<<"/z/"<<zs[z]<<"/bounds";

        //	    Log(lDebug5) << "Fetching from server using URL: "<<sUrl.str();
        TStringStream* zstrings = new TStringStream;;
        mC->Get(sUrl.str().c_str(), zstrings);

        if( mC->ResponseCode == HTTP_RESPONSE_OK)
        {
            string s = stdstr(zstrings->DataString);
            RenderBox sec_bounds = parseBoundsResponse(s);
            sec_bounds.setZ(zs[z]);
			mLatestBounds.push_back(sec_bounds);

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

    return RenderBox(xMin, yMin, xMax-xMin, yMax -yMin);
}

vector<RenderBox> RenderClient::getBounds()
{
	return mLatestBounds;
}

string RenderClient::getImageLocalPathAndFileName()
{
	return getImageCacheFileNameAndPathFromURL(getURL(), mLocalCacheFolder);
}

bool RenderClient::checkCacheForCurrentURL()
{
	return fileExists(getImageLocalPathAndFileName());
}

void RenderClient::clearImageMemory()
{
	delete mImageMemory;
    mImageMemory = NULL;
}

string RenderClient::getURLForZ(int z)
{
	stringstream sUrl;
    sUrl << mBaseURL;
    sUrl << "/owner/" 		<< mProject.getProjectOwner();
    sUrl << "/project/" << mProject.getProject();
    sUrl << "/stack/"	<<mProject.getCurrentStackName();
    sUrl << "/z/"<<z;
    sUrl << "/box/"<<mRenderBox.getX1()<<","<<mRenderBox.getY1() << "," << mRenderBox.getWidth() << ","<<mRenderBox.getHeight() << ","<<mScale;
    sUrl << "/jpeg-image";
	sUrl << "?minIntensity="<<mMinIntensity;
	sUrl << "&maxIntensity="<<mMaxIntensity;
	return sUrl.str();
}

string RenderClient::getURL()
{
	//("http://ibs-forrestc-ux1.corp.alleninstitute.org:8080/render-ws/v1/owner/Sharmishtaas/project/M259292_Scnn1aTg2_1/stack/{0}/
    //z/{1}/box/5000,9000,1300,1300,{2}/tiff-image");
	stringstream sUrl;
    sUrl << mBaseURL;
    sUrl << "/owner/" 	<< mProject.getProjectOwner();
    sUrl << "/project/" << mProject.getProject();
    sUrl << "/stack/"	<<mProject.getCurrentStackName();
    sUrl << "/z/"<<mZ;
    sUrl << "/box/"<<round(mRenderBox.getX1())<<","<<round(mRenderBox.getY1()) << "," << round(mRenderBox.getWidth()) << ","<<round(mRenderBox.getHeight()) << ","<<mScale;
    sUrl << "/jpeg-image";
	sUrl << "?minIntensity="<<mMinIntensity;
	sUrl << "&maxIntensity="<<mMaxIntensity;
	return sUrl.str();
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
    sUrl << mBaseURL;
    sUrl << "/owner/"    << mProject.getProjectOwner();
    sUrl << "/project/" << 	mProject.getProject();
    sUrl << "/stack/"	<<	mProject.getCurrentStackName();
    sUrl <<"/zValues";

    Log(lInfo) << "Fetching from server using URL: "<<sUrl.str();

    try
    {
        TStringStream* zstrings = new TStringStream;;
        mC->Get(sUrl.str().c_str(), zstrings);


        if( mC->ResponseCode == HTTP_RESPONSE_OK)
        {
            string s = stdstr(zstrings->DataString);
    //        Log(lInfo) << "Response: "<<s;
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
}

RenderBox RenderClient::parseBoundsResponse(const string& _s)
{
	RenderBox bounds; //XminXMaxYMinYMax
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
    sUrl << mBaseURL;
    sUrl << "/owner/"<<owner;
    sUrl << "/stackIds";
    Log(lDebug5) << "Fetching stackId data using URL: "<<sUrl.str();

    StringList stacks;
    TStringStream* zstrings = new TStringStream;;
    mC->Get(sUrl.str().c_str(), zstrings);

    if( mC->ResponseCode == HTTP_RESPONSE_OK)
    {
        string s = stdstr(zstrings->DataString);
        s = stripCharacters("\"[]}", s);
        Log(lInfo) << s;
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
    else
    {
        Log(lError) << "Failed fetching owners";
    }

    stacks.sort();
    return stacks;
}

