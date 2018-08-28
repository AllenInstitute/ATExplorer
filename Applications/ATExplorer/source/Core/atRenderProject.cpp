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

RenderProject::RenderProject(const string& name, const string& owner, const string& project, const string& stack)
:
ATExplorerProject(name),
mOwner(owner),
mProject(project),
mSelectedStack(stack),
mHasView(false),
mSelectedSection(-1)
{
	mATEObjectType = (ateRenderProject);
}

RenderProject::RenderProject(const string& _url)
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

    mOwner   		= pairs[4];
    mProject 		= pairs[6];
    mSelectedStack 	= pairs[8];
}

//Shallow copy..
RenderProject& RenderProject::operator=(const RenderProject& rhs)
{
	if(this != &rhs)
    {
        mInfo	 	        = rhs.mInfo;
        mOwner		        = rhs.mOwner;
        mProject	        = rhs.mProject;
        mSelectedStack		= rhs.mSelectedStack;
        mStacks				= rhs.mStacks;
    }
    return *this;
}

void RenderProject::init(const string& owner, const string& project, const string& stack)
{
	mOwner 				= owner;
    mProject 			= project;
    mSelectedStack 		= stack;
}

RenderProject::RenderProject(const RenderProject& rp)
: ATExplorerProject(rp)
{
    mInfo	 	        = rp.mInfo;
    mOwner		        = rp.mOwner;
    mProject	        = rp.mProject;
    mSelectedStack		= rp.mSelectedStack;
    mStacks				= rp.mStacks;
}

string RenderProject::getProject()
{
	return mProject;
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
    XMLElement* val = doc.NewElement("owner");
    val->SetText(mOwner.c_str());
    docRoot->InsertEndChild(val);

    val = doc.NewElement("project");
    val->SetText(mProject.c_str());
    docRoot->InsertEndChild(val);

    val = doc.NewElement("stack");
    val->SetText(mSelectedStack.c_str());
    docRoot->InsertEndChild(val);

    return val;
}

bool RenderProject::loadFromXML(dsl::XMLNode* node)
{
    XMLElement* e = node->FirstChildElement("owner");
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
    	mProject = e->GetText() ? string(e->GetText()) : string("");
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
