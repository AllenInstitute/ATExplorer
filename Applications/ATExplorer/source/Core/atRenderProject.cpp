#pragma hdrstop
#include "atRenderProject.h"
#include "dslXMLUtils.h"
//---------------------------------------------------------------------------

using namespace dsl;



RenderProject::RenderProject(const string& name, const string& owner, const string& project, const string& stack)
:
VolumeCreatorProject(name),
mOwner(owner),
mProject(project),
mStack(stack)
{
	mVCObjectType = (vcoRenderProject);
}


void RenderProject::setupForStack(const string& owner, const string& project, const string& stack)
{
	mOwner 		= owner;
    mProject 	= project;
    mStack 		= stack;
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
    val->SetText(mStack.c_str());
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
    	mStack = e->GetText() ? string(e->GetText()) : string("");
    }


	return true;
}

bool RenderProject::write()
{
	return false;
}

