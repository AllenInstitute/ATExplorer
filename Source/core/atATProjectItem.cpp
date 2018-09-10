#pragma hdrstop
#include "atATProjectItem.h"
#include "dslXMLUtils.h"
#include "dslLogger.h"
#include "atRenderProjectItem.h"
#include "atATData.h"
#include "atATDataProjectItem.h"

using namespace dsl;
using namespace tinyxml2;
namespace at
{
//XML Version history
/*
    0.5 : Original version
*/

const string gATProjectFileVersion    = "0.6";

string ATProjectItem::getATObjectTypeAsString()
{
	return ::toString(mATProjectItemType);
}

//ATProjectItem::ATProjectItem(ATProjectItemType type)
//:
//Project("", "atp"),
//mATProjectItemType(type)
//{
//	resetXML();
//}

ATProjectItem::ATProjectItem(const string& projName)
:
Project(projName, "atp"),
mATProjectItemType(atpATProjectItem)
{
	resetXML();
}

ATProjectItem::~ATProjectItem()
{}

int	ATProjectItem::getNumberOfChilds()
{
	int sz =  mItems.size();
	return sz;
}

bool ATProjectItem::isModified()
{
    //Cycle trough children
    for(int i = 0; i < mItems.size(); i++)
    {
    	if(mItems[i]->isModified())
        {
	        return true;
			break;
        }
    }
    return mIsModified;
}

ProjItemPtr ATProjectItem::getChild(int i)
{
	if(i > 0 && i <= mItems.size())
    {
		return mItems[i - 1];
    }
    return ProjItemPtr();
}

string ATProjectItem::getPresentXMLModelVersion()
{
    return gATProjectFileVersion;
}

bool ATProjectItem::addChild(ProjItemPtr child)
{
	if(child)
    {
    	mItems.append(child);
        return true;
    }
	return false;
}

bool ATProjectItem::addProjectObject(ATObject* child)
{
    //Check what kind of object that was passed by dynamic casting
    if(!child)
    {
        return false;
    }

    if(dynamic_cast<ATData*>(child))
    {
	    ATData* data = dynamic_cast<ATData*>(child);
        Log(lInfo) << "Adding an ATData object to the project";

        //ATData does have a format
        shared_ptr<ATDataProjectItem> o = shared_ptr<ATDataProjectItem>(new ATDataProjectItem("ATDataItem", shared_ptr<ATData>(data)));
        return mItems.append(o) == true ? true : false;
    }

    return false;
}

//Re implemented in derived objects
XMLElement* ATProjectItem::addToXMLDocumentAsChild(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
{
	return NULL;
}

bool ATProjectItem::resetXML()
{
	mTheXML.Clear();
    mProjectRoot = mTheXML.NewElement("at_project");
    mRootNode = mTheXML.InsertFirstChild(mProjectRoot);

    //Insert as a minimum project file version
    XMLElement* xmlElement = mTheXML.NewElement("version");
    XMLText* 	xmlText = mTheXML.NewText(gATProjectFileVersion.c_str());
    xmlElement->InsertEndChild(xmlText);
    mProjectRoot->InsertEndChild(xmlElement);

    xmlElement 		= mTheXML.NewElement("name");
    xmlText 		= mTheXML.NewText(getProjectName().c_str());
    xmlElement->InsertEndChild(xmlText);
    mProjectRoot->InsertEndChild(xmlElement);
    return true;
}

//Create header for VCObject node
XMLElement* ATProjectItem::addToXMLDocument(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
{
    //Create XML for saving to file
    XMLElement* objectNode  	= doc.NewElement("at_object");
    XMLNode*    rootNode 		= doc.InsertFirstChild(objectNode);

    //Attributes
    objectNode->SetAttribute("type", getATObjectTypeAsString().c_str());
    objectNode->SetAttribute("name", getProjectName().c_str());

	XMLElement* dataval1 = doc.NewElement("info");
    dataval1->SetText(mInfoText.c_str());
	objectNode->InsertEndChild(dataval1);

    objectNode->InsertEndChild(rootNode);
    docRoot->InsertEndChild(objectNode);

    return objectNode;
}

bool ATProjectItem::save(const string& fName)
{
    resetXML();

    XMLElement* objects = newElement("at_objects");

    //Iterate through object container
	for(int i = 0; i < mItems.size(); i++)
    {
    	if(mItems[i])
        {
    	    XMLElement* node = mItems[i]->addToXMLDocument(mTheXML, objects);
	       	mItems[i]->addToXMLDocumentAsChild(mTheXML, node);
		    objects->InsertEndChild(node);
        }
    }

    mProjectRoot->InsertEndChild(objects);
    return saveToFile(fName);
}

bool ATProjectItem::open(const string& fName)
{
    try
    {
        if(fName.size())
        {
            setFileName(fName);
        }

        Project::loadXMLFromFile(fName);

    	createProjectFromXML(mProjectRoot);
        Log(lInfo) << "Attempting to load ATExplorer Project: "<<this->getFileName();

        //Read the name node
        int nrOfObjs = createProjectObjects();
        Log(lDebug) << "Loaded " << nrOfObjs << " AT Project Objects";
        return true;
    }
    catch(...)
    {
        throw("Bad model file!");
    }
}

bool ATProjectItem::createProjectFromXML(dsl::XMLNode* node)
{
    XMLElement* e = node->FirstChildElement("name");
    if(e)
    {
    	setProjectName(e->GetText() ? string(e->GetText()) : string(""));
    }

	return true;
}

int ATProjectItem::createProjectObjects()
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
        ProjItemPtr aProc = createATProjectItem(p);

        if(aProc)
        {
            mItems.append(aProc);
            Log(lDebug) <<"Imported Project Item: "<<aProc->getProjectName();
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

ProjItemPtr ATProjectItem::createATProjectItem(tinyxml2::XMLElement* element)
{
    if(!element && !compareStrings(element->Name(), "at_object", csCaseInsensitive))
    {
    	Log(lError) <<"Bad 'render_project' xml!";
    	return ProjItemPtr();
    }

    ATProjectItemType pt = toATProjectItemType(element->Attribute("type"));
    switch(pt)
    {
        case atpRenderProjectItem: 	  	return createRenderProjectItem(element);
        case atpATDataProjectItem: 		return createATDataProjectItem(element);

        default: return ProjItemPtr();
    }
}

ProjItemPtr ATProjectItem::createRenderProjectItem(tinyxml2::XMLElement* element)
{
    if(!element && !compareStrings(element->Name(), "render_project", csCaseInsensitive))
    {
    	Log(lError) <<"Bad 'render_project' xml!";
    	return ProjItemPtr();
    }

	const char* name = element->Attribute("name");

	shared_ptr<RenderProjectItem> p = shared_ptr<RenderProjectItem>(new RenderProjectItem(name ? string(name) : string(""), "", "" ,""));
	if(!p->loadFromXML(element))
    {
    	Log(lError) << "There was a problem loading model from XML";
    }

    return p;
}

ProjItemPtr ATProjectItem::createATDataProjectItem(tinyxml2::XMLElement* element)
{
    if(!element && !compareStrings(element->Attribute("type"), "atDataProjectItem", csCaseInsensitive))
    {
    	Log(lError) <<"Bad 'render_project' xml!";
    	return ProjItemPtr();
    }

    XMLNode* n = element->FirstChild();
    if(n)
    {
        if(!n->Value())
        {
            n->SetValue("No Value");
        }
    }

	const char* name = element->Attribute("name");
	shared_ptr<ATDataProjectItem> p = shared_ptr<ATDataProjectItem>(new ATDataProjectItem(name ? string(name) : string("")));

	if(!p->loadFromXML(element))
    {
    	Log(lError) << "There was a problem loading model from XML";
    }

    return p;
}

string toString(ATProjectItemType tp)
{
	switch(tp)
    {
    	case atpATProjectItem: 			    return "atATProjectItem";
    	case atpRenderProjectItem: 	        return "renderProjectItem";
        case atpVolumeProjectItem:			return "volumeProjectItem";
        case atpATDataProjectItem:			return "atDataProjectItem";
        default:							return "unKnownProjectItem";
    }
}

ATProjectItemType toATProjectItemType(const string& vcObject)
{
	if(     vcObject == "aTProjectItem") 		return atpATProjectItem;
	else if(vcObject == "renderProjectItem") 	return atpRenderProjectItem;
	else if(vcObject == "volumeProjectItem")  	return atpVolumeProjectItem;
	else if(vcObject == "atDataProjectItem")  	return atpATDataProjectItem;
	else if(vcObject == "unKnownProjectItem") 	return atpUnknownProjectItem;

   	return atpUnknownProjectItem;
}

}
