#pragma hdrstop
#include "atPointMatchContextProject.h"
#include "dslXMLUtils.h"
#include "Poco/URI.h"
//---------------------------------------------------------------------------

namespace at
{

using namespace dsl;

PointMatchContextProject::PointMatchContextProject(const string& _url)
:
mLocalCacheRootFolder(""),
mRenderService(new RenderServiceParameters("", ""))
{
	//"http://ibs-forrestc-ux1.corp.alleninstitute.org:8988/render-ws/v1/owner/Deleted/project/Blag/stack/TEST_Totte_Renamed_AFF/z/3/box/-4515,-2739,9027,5472,0.1338/jpeg-image?minIntensity=0&maxIntensity=6000"
    //Extract owner,project and stack from url
    Poco::URI url(_url);
    string path (url.getPath());
	//  /render-ws/v1/owner/Deleted/project/Blag/stack/TEST_Totte_Renamed_AFF/z/3/box/-4515,-2739,9027,5472,0.1338/jpeg-image
    //0 /1        /2/3     /4      /5      /6   /7    /8                     /9/10/11/12                          /13
    StringList pairs(path, '/');

    if(pairs.count() != 14)
    {
        throw("Bad stuff...");
    }

    mOwner   			= pairs[4];
    mPointMatchContextProjectName 	= pairs[6];
    mSelectedStack 		= pairs[8];

	//mCurrentROI
//    mMinIntensity
//	mMaxIntensity
    mATEObjectType = (atePointMatchContextProject);
}

PointMatchContextProject::PointMatchContextProject(const string& name, RenderServiceParameters* s)
:
ATExplorerProject(name),
mOwner(""),
mLocalCacheRootFolder(""),
mPointMatchContextProjectName(""),
mSelectedStack(""),
mSelectedChannel(""),
mCurrentROI(0,0,500,500),
mMinIntensity(0),
mMaxIntensity(65535),
mRenderService(s)
{
	mATEObjectType = (atePointMatchContextProject);
}

PointMatchContextProject::PointMatchContextProject(const string& name, const string& owner, const string& project, const string& stack)
:
ATExplorerProject(name),
mOwner(owner),
mLocalCacheRootFolder(""),
mPointMatchContextProjectName(project),
mSelectedStack(stack),
mSelectedChannel(""),
mCurrentROI(0,0,500,500),
mMinIntensity(0),
mMaxIntensity(65535),
mRenderService(new RenderServiceParameters("", ""))
{
	mATEObjectType = (atePointMatchContextProject);
}

PointMatchContextProject::PointMatchContextProject(const PointMatchContextProject& rp)
:
ATExplorerProject(rp),
mRenderService(rp.mRenderService),
mCurrentROI(rp.mCurrentROI)
{
    mInfo	 	            = rp.mInfo;
    mOwner		            = rp.mOwner;
    mPointMatchContextProjectName      = rp.mPointMatchContextProjectName;
    mSelectedStack		    = rp.mSelectedStack;
	mSelectedChannel		= rp.mSelectedChannel;
    mRenderStacks		    = rp.mRenderStacks;
    mLocalCacheRootFolder 	= rp.mLocalCacheRootFolder;
    mCurrentROI             = rp.mCurrentROI;
    mMinIntensity		    = rp.mMinIntensity;
	mMaxIntensity		    = rp.mMaxIntensity;
    mRenderService          = rp.mRenderService;
}

PointMatchContextProject::~PointMatchContextProject()
{}

//Shallow copy..
PointMatchContextProject& PointMatchContextProject::operator=(const PointMatchContextProject& rhs)
{
	if(this != &rhs)
    {
        mInfo	 	            = rhs.mInfo;
        mOwner		            = rhs.mOwner;
        mPointMatchContextProjectName	    = rhs.mPointMatchContextProjectName;
        mSelectedStack		    = rhs.mSelectedStack;
        mRenderStacks		    = rhs.mRenderStacks;
        mLocalCacheRootFolder 	= rhs.mLocalCacheRootFolder;
        mCurrentROI             = rhs.mCurrentROI;
    	mMinIntensity			= rhs.mMinIntensity;
		mMaxIntensity			= rhs.mMaxIntensity;
        mRenderService          = rhs.mRenderService;
    }
    return *this;
}

string PointMatchContextProject::getTypeName() const
{
    return "PointMatchContextProject";
}

bool PointMatchContextProject::setRenderServiceParameters(RenderServiceParameters* rsp)
{
    mRenderService = rsp;
    return true;
}

void PointMatchContextProject::assignLocalCacheRootFolder(const string& rFolder)
{
    mLocalCacheRootFolder = rFolder;
}

RegionOfInterest& PointMatchContextProject::getCurrentRegionOfInterestReference()
{
    return mCurrentROI;
}

string PointMatchContextProject::getLocalCacheFolder() const
{
    return mLocalCacheRootFolder;
}

RenderServiceParameters* PointMatchContextProject::getRenderServiceParameters() const
{
    return mRenderService;
}

string PointMatchContextProject::getPointMatchContextProjectName() const
{
	return mPointMatchContextProjectName;
}

string PointMatchContextProject::getProjectOwner() const
{
	return mOwner;
}

bool PointMatchContextProject::setSelectedStackName(const string& stackName)
{
	mSelectedStack = stackName;
    return true;
}

bool PointMatchContextProject::setSelectedChannelName(const string& s)
{
	mSelectedChannel = s;
    return true;
}

bool PointMatchContextProject::setSelectedSection(int secNr)
{
	mCurrentROI.setZ(secNr);
    return true;
}

int PointMatchContextProject::getSelectedSection()
{
	return mCurrentROI.getZ();
}

string PointMatchContextProject::getSelectedStackName() const
{
	return mSelectedStack;
}

string PointMatchContextProject::getSelectedChannelName() const
{
	return mSelectedChannel;
}

//StringList PointMatchContextProject::getChannels()
//{
//    return mChannels;
//}

int& PointMatchContextProject::getMinIntensity()
{
    return mMinIntensity;
}

int& PointMatchContextProject::getMaxIntensity()
{
    return mMaxIntensity;
}

XMLElement* PointMatchContextProject::addToXMLDocumentAsChild(tinyxml2::XMLDocument& doc, XMLElement* parentNode)
{
    if(!mRenderService)
    {
        return NULL;
    }
    //Create XML for saving to file
    XMLElement* val(nullptr);

    val = doc.NewElement("renderhostname");
    val->SetText(mRenderService->getName().c_str());
    parentNode->InsertEndChild(val);

    val = doc.NewElement("renderhost");
    val->SetText(mRenderService->getHost().c_str());
    parentNode->InsertEndChild(val);

    val = doc.NewElement("renderhostport");
    val->SetText(mRenderService->getPortNrAsString().c_str());
    parentNode->InsertEndChild(val);

    val = doc.NewElement("renderhostversion");
    val->SetText(mRenderService->getVersion().c_str());
    parentNode->InsertEndChild(val);

    val = doc.NewElement("owner");
    val->SetText(mOwner.c_str());
    parentNode->InsertEndChild(val);

    val = doc.NewElement("project");
    val->SetText(mPointMatchContextProjectName.c_str());
    parentNode->InsertEndChild(val);

    val = doc.NewElement("selected_stack");
    val->SetText(mSelectedStack.c_str());
    parentNode->InsertEndChild(val);

    val = doc.NewElement("selected_channel");
    val->SetText(mSelectedChannel.c_str());
    parentNode->InsertEndChild(val);

    val = doc.NewElement("local_cache_folder");
    val->SetText(mLocalCacheRootFolder.c_str());
    parentNode->InsertEndChild(val);

    val = doc.NewElement("min_intensity");
    val->SetText(mMinIntensity);
    parentNode->InsertEndChild(val);

    val = doc.NewElement("max_intensity");
    val->SetText(mMaxIntensity);
    parentNode->InsertEndChild(val);

    mCurrentROI.addToXMLDocumentAsChild(doc, parentNode);

   	//Create XML for saving to file
   	XMLElement* tiffStacks = doc.NewElement("tiffstacks");
    Project* child = mChilds.getFirst();
    while(child != nullptr)
    {
        XMLElement* stackNode = child->addToXMLDocumentAsChild(doc, tiffStacks);
        child = mChilds.getNext();
    }

    parentNode->InsertEndChild(tiffStacks);
    return val;
}

bool PointMatchContextProject::loadFromXML(dsl::XMLNode* node)
{
    XMLElement* e(nullptr);

    e = node->FirstChildElement("renderhostname");
    if(e)
    {
    	mRenderService->setName(e->GetText() ? string(e->GetText()) : string(""));
    }

    e = node->FirstChildElement("renderhost");
    if(e)
    {
    	mRenderService->setHost(e->GetText() ? string(e->GetText()) : string(""));
    }

    e = node->FirstChildElement("renderhostport");
    if(e)
    {
    	mRenderService->setPortNr(e->GetText() ? dsl::toInt(e->GetText()) : 80);
    }

    e = node->FirstChildElement("renderhostversion");
    if(e)
    {
    	mRenderService->setVersion(e->GetText() ? string(e->GetText()) : string(""));
    }

    e = node->FirstChildElement("owner");
    if(e)
    {
    	mOwner = e->GetText() ? string(e->GetText()) : string("");
    }

    e = node->FirstChildElement("info");
    if(e)
    {
    	mInfo = e->GetText() ? string(e->GetText()) : string("");
    }

    e = node->FirstChildElement("project");
    if(e)
    {
    	mPointMatchContextProjectName = e->GetText() ? string(e->GetText()) : string("");
    }

    e = node->FirstChildElement("selected_stack");
    if(e)
    {
    	mSelectedStack = e->GetText() ? string(e->GetText()) : string("");
    }

    e = node->FirstChildElement("selected_channel");
    if(e)
    {
    	mSelectedChannel = e->GetText() ? string(e->GetText()) : string("");
    }

    e = node->FirstChildElement("local_cache_folder");
    if(e)
    {
    	mLocalCacheRootFolder = e->GetText() ? string(e->GetText()) : string("");
    }

    e = node->FirstChildElement("min_intensity");
    if(e)
    {
    	mMinIntensity = (e->GetText() ? dsl::toInt(e->GetText()) : 0);
    }

    e = node->FirstChildElement("max_intensity");
    if(e)
    {
    	mMaxIntensity = (e->GetText() ? dsl::toInt(e->GetText()) : 0);
    }

    e = node->FirstChildElement("roi");
    if(e)
    {
	    mCurrentROI.loadFromXML(e);
    }

	return true;
}

bool PointMatchContextProject::write()
{
	return false;
}

}
