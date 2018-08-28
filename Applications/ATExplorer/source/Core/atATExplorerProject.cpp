#include <vcl.h>
#pragma hdrstop
#include "atATExplorerProject.h"
#include "dslXMLUtils.h"
#include "dslLogger.h"
#include "atRenderProject.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

namespace at
{
using namespace dsl;
using namespace tinyxml2;

//XML Version history
/*
    0.5 : Original version
*/

const string gATExplorerProjectFileVersion    = "0.6";

string ATExplorerProject::getATEObjectTypeAsString()
{
	return at::toString(mATEObjectType);
}

ATExplorerProject::ATExplorerProject(const string& projName)
:
Project(projName, "atp"),
mATEObjectType(ateBaseType)
{
	resetXML();
}

ATExplorerProject::~ATExplorerProject()
{}


int	ATExplorerProject::getNumberOfChilds()
{
	int sz =  mChilds.size();
	return sz;
}

bool ATExplorerProject::isModified()
{
    //Cycle trough children
    for(uint i = 0; i < mChilds.size(); i++)
    {
    	if(mChilds[i]->isModified())
        {
	        return true;
        }
    }
    return mIsModified;
}

ATExplorerProject* ATExplorerProject::getChild(int i)
{
	if(i >= 0 && i < mChilds.size())
    {
		return mChilds[i];
    }
    return NULL;
}

string ATExplorerProject::getPresentXMLModelVersion()
{
    return gATExplorerProjectFileVersion;
}

bool ATExplorerProject::addChild(ATExplorerProject* child)
{
	if(child)
    {
    	mChilds.push_back(child);
        child->setParent(this);
        return true;
    }
	return false;
}

//Re implemented in derived objects
XMLElement* ATExplorerProject::addToXMLDocumentAsChild(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
{
	return NULL;
}

bool ATExplorerProject::resetXML()
{
	mTheXML.Clear();
    mProjectRoot = mTheXML.NewElement("at_project");
    mRootNode = mTheXML.InsertFirstChild(mProjectRoot);

    //Insert as a minimum project file version
    XMLElement* xmlElement = mTheXML.NewElement("version");
    XMLText* 	xmlText = mTheXML.NewText(gATExplorerProjectFileVersion.c_str());
    xmlElement->InsertEndChild(xmlText);
    mProjectRoot->InsertEndChild(xmlElement);

    xmlElement 		= mTheXML.NewElement("name");
    xmlText 		= mTheXML.NewText(getProjectName().c_str());
    xmlElement->InsertEndChild(xmlText);
    mProjectRoot->InsertEndChild(xmlElement);
    return true;
}

//Create header for VCObject node
XMLElement* ATExplorerProject::addToXMLDocument(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
{
    //Create XML for saving to file
    XMLElement* objectNode  	= doc.NewElement("at_object");
    XMLNode*    rootNode 		= doc.InsertFirstChild(objectNode);

    //Attributes
    objectNode->SetAttribute("type", getATEObjectTypeAsString().c_str());
    objectNode->SetAttribute("name", getProjectName().c_str());

	XMLElement* dataval1 = doc.NewElement("info");
    dataval1->SetText(mInfoText.c_str());
	objectNode->InsertEndChild(dataval1);

    objectNode->InsertEndChild(rootNode);
    docRoot->InsertEndChild(objectNode);

    return objectNode;
}

bool ATExplorerProject::save(const string& fName)
{
    resetXML();

    XMLElement* objects = newElement("at_objects");

    //Iterate through object container
	for(int i = 0; i < mChilds.size(); i++)
    {
    	if(mChilds[i])
        {
    	    XMLElement* node = mChilds[i]->addToXMLDocument(mTheXML, objects);
	       	mChilds[i]->addToXMLDocumentAsChild(mTheXML, node);
		    objects->InsertEndChild(node);
        }
    }

    mProjectRoot->InsertEndChild(objects);
    return saveToFile(fName);
}

bool ATExplorerProject::open(const string& fname)
{
    try
    {
    	loadFromXML(mProjectRoot);

        Log(lInfo) << "Attempting to load at Project: "<<this->getFileName();

        //Read the name node
        int nrOfObjs = loadATObjects();
        Log(lDebug) << "Loaded " << nrOfObjs << " at objects";
        return true;
    }
    catch(...)
    {
        throw("Bad model file!");
    }
}

bool ATExplorerProject::loadFromXML(dsl::XMLNode* node)
{
    XMLElement* e = node->FirstChildElement("name");
    if(e)
    {
    	setProjectName(e->GetText() ? string(e->GetText()) : string(""));
    }

//    e = node->FirstChildElement("version");
//    if(e)
//    {
//    	setMoName(e->GetText() ? string(e->GetText()) : string(""));
//    }

	return true;
}

int ATExplorerProject::loadATObjects()
{
    XMLElement* project = this->getXML("at_objects");

    if(project == NULL)
    {
        return 0;
    }

    int nrOfObjects = 0;
    //Load child by child
    XMLElement* p = project->FirstChildElement();
    while(p)
    {
        //Find out what kind of element p is
        ATExplorerProject* child = createATObject(p);

        if(child)
        {
            mChilds.push_back(child);
            child->setParent(this);
            Log(lDebug) <<"Imported child: "<<child->getProjectName();
            nrOfObjects++;
        }
        else
        {
            Log(lError) << "Failed importing a "<<p->Name()<<" process";
        }

        p = p->NextSiblingElement();
    }
    return nrOfObjects;
}

ATExplorerProject* ATExplorerProject::createATObject(tinyxml2::XMLElement* element)
{
    if(!element || !compareStrings(element->Name(), "at_object", csCaseInsensitive))
    {
    	Log(lError) <<"Bad 'render_project' xml!";
    	return NULL;
    }

    ATEObjectType pt = toATEObjectType(element->Attribute("type"));
    switch(pt)
    {
        case ateRenderProject:
        	return createRenderProject(element);
        default: return NULL;
    }
}

RenderProject* ATExplorerProject::createRenderProject(tinyxml2::XMLElement* element)
{
    if(!element || !compareStrings(element->Name(), "at_object", csCaseInsensitive))
    {
    	Log(lError) <<"Bad 'render_project' xml!";
    	return NULL;
    }

	const char* name = element->Attribute("name");

	RenderProject* p = new RenderProject(name ? string(name) : string(""), "", "" ,"");
	if(!p->loadFromXML(element))
    {
    	Log(lError) << "There was a problem loading model from XML";
    }

    return p;
}

string toString(ATEObjectType tp)
{
	switch(tp)
    {
    	case ateBaseType: 			return "atExplorerProject";
    	case ateRenderProject: 		return "renderProject";
        case ateVolume:				return "volume";
        default:					return "unKnownObject";
    }
}

ATEObjectType toATEObjectType(const string& ateObject)
{
	if(     ateObject == "atExplorerProject") 		return ateBaseType;
	else if(ateObject == "renderProject") 			return ateRenderProject;
	else if(ateObject == "volume") 					return ateVolume;
	else if(ateObject == "unKnownObject") 			return ateUnknown;

   	return ateUnknown;
}

}
