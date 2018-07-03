#pragma hdrstop
#include "atRenderProjectItem.h"
#include "dslXMLUtils.h"
//---------------------------------------------------------------------------

using namespace dsl;


namespace at
{
RenderProjectItem::RenderProjectItem(const string& name, const string& owner, const string& project, const string& stack)
:
ATProject(name),
mOwner(owner),
mProject(project),
mStack(stack)
{
	mATProjectObjectType = (atpRenderProjectItem);
}


void RenderProjectItem::setupForStack(const string& owner, const string& project, const string& stack)
{
	mOwner 		= owner;
    mProject 	= project;
    mStack 		= stack;
}


XMLElement* RenderProjectItem::addToXMLDocumentAsChild(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
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

bool RenderProjectItem::loadFromXML(dsl::XMLNode* node)
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

bool RenderProjectItem::write()
{
	return false;
}

}
