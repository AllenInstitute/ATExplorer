#include <vcl.h>
#pragma hdrstop
#include "atRenderProject.h"
#include "dslXMLUtils.h"
#include "Poco/URI.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

namespace at
{

using namespace dsl;

RenderProject::RenderProject(const string& _url)
:
mRenderService("")
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
    mRenderProjectName 	= pairs[6];
    mSelectedStack 		= pairs[8];
	mATEObjectType = (ateRenderProject);
}

RenderProject::RenderProject(const string& name, const string& owner, const string& project, const string& stack)
:
ATExplorerProject(name),
mOwner(owner),
mRenderProjectName(project),
mSelectedStack(stack),
mSelectedSection(-1),
mRenderService("")
{
	mATEObjectType = (ateRenderProject);
}

RenderProject::RenderProject(const RenderServiceParameters& rs, const string& name, const string& owner, const string& project)
:
mRenderService(rs),
ATExplorerProject(name),
mOwner(owner),
mRenderProjectName(project),
mSelectedStack(""),
mSelectedSection(-1)
{
	mATEObjectType = (ateRenderProject);
}

//Shallow copy..
RenderProject& RenderProject::operator=(const RenderProject& rhs)
{
	if(this != &rhs)
    {
        mInfo	 	        = rhs.mInfo;
        mOwner		        = rhs.mOwner;
        mRenderProjectName	= rhs.mRenderProjectName;
        mSelectedStack		= rhs.mSelectedStack;
        mStacks				= rhs.mStacks;
    }
    return *this;
}

void RenderProject::init(const string& owner, const string& project, const string& stack)
{
	mOwner 				= owner;
    mRenderProjectName 	= project;
    mSelectedStack 		= stack;
}

RenderProject::RenderProject(const RenderProject& rp)
:
ATExplorerProject(rp),
mRenderService(rp.mRenderService)
{
    mInfo	 	        = rp.mInfo;
    mOwner		        = rp.mOwner;
    mRenderProjectName  = rp.mRenderProjectName;
    mSelectedStack		= rp.mSelectedStack;
    mStacks				= rp.mStacks;
}

RenderProject::~RenderProject()
{

}

RenderServiceParameters RenderProject::getRenderServiceParameters()
{
    return mRenderService;
}

string RenderProject::getRenderProjectName()
{
	return mRenderProjectName;
}

string RenderProject::getProjectOwner()
{
	return mOwner;
}

string RenderProject::getSelectedStackName()
{
	return mSelectedStack;
}

XMLElement* RenderProject::addToXMLDocumentAsChild(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
{
    //Create XML for saving to file
    XMLElement* val(nullptr);

    val = doc.NewElement("renderhost");
    val->SetText(mRenderService.getBaseURL().c_str());
    docRoot->InsertEndChild(val);

    val = doc.NewElement("renderhostport");
    val->SetText(mRenderService.getPortNrAsString().c_str());
    docRoot->InsertEndChild(val);

    val = doc.NewElement("renderhostversion");
    val->SetText(mRenderService.getVersion().c_str());
    docRoot->InsertEndChild(val);

    val = doc.NewElement("owner");
    val->SetText(mOwner.c_str());
    docRoot->InsertEndChild(val);

    val = doc.NewElement("project");
    val->SetText(mRenderProjectName.c_str());
    docRoot->InsertEndChild(val);

    val = doc.NewElement("stack");
    val->SetText(mSelectedStack.c_str());
    docRoot->InsertEndChild(val);

    return val;
}

bool RenderProject::loadFromXML(dsl::XMLNode* node)
{
    XMLElement* e(nullptr);


    e = node->FirstChildElement("renderhost");
    if(e)
    {
    	mRenderService.setBaseURL(e->GetText() ? string(e->GetText()) : string(""));
    }

    e = node->FirstChildElement("renderhostport");
    if(e)
    {
    	mRenderService.setPortNr(e->GetText() ? dsl::toInt(e->GetText()) : 80);
    }

    e = node->FirstChildElement("renderhostversion");
    if(e)
    {
    	mRenderService.setVersion(e->GetText() ? string(e->GetText()) : string(""));
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
    	mRenderProjectName = e->GetText() ? string(e->GetText()) : string("");
    }

    e = node->FirstChildElement("stack");
    if(e)
    {
    	mSelectedStack = e->GetText() ? string(e->GetText()) : string("");
    }
	return true;
}

bool RenderProject::write()
{
	return false;
}

}
