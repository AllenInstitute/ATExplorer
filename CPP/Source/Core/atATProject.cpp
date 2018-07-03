#pragma hdrstop
#include "atATProject.h"
#include "dslXMLUtils.h"
#include "dslLogger.h"
#include "atRenderProject.h"
#include "atATData.h"
#include "atATDataProjectObject.h"

using namespace dsl;
using namespace tinyxml2;
namespace at
{
//XML Version history
/*
    0.5 : Original version
*/

const string gATProjectFileVersion    = "0.6";

string ATProject::getATObjectTypeAsString()
{
	return ::toString(mATProjectObjectType);
}

ATProject::ATProject(ATProjectObjectType type)
:
Project("", "atp"),
mATProjectObjectType(type)
{
	resetXML();
}

ATProject::ATProject(const string& projName)
:
Project(projName, "atp"),
mATProjectObjectType(atpBaseType)
{
	resetXML();
}

ATProject::~ATProject()
{}

int	ATProject::getNumberOfChilds()
{
	int sz =  mChilds.size();
	return sz;
}

bool ATProject::isModified()
{
    //Cycle trough children
    for(int i = 0; i < mChilds.size(); i++)
    {
    	if(mChilds[i]->isModified())
        {
	        return true;
			break;
        }
    }
    return mIsModified;
}

ATProject* ATProject::getChild(int i)
{
	if(i > 0 && i <= mChilds.size())
    {
		return mChilds[i - 1];
    }
    return NULL;
}

string ATProject::getPresentXMLModelVersion()
{
    return gATProjectFileVersion;
}

bool ATProject::addChild(ATProject* child)
{
	if(child)
    {
    	mChilds.push_back(child);
        return true;
    }
	return false;
}

bool ATProject::addProjectObject(ATObject* child)
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
        ATDataProjectObject* o = new ATDataProjectObject(shared_ptr<ATData>(data));
        mChilds.push_back(o);
        //Project need to be saved in order to update the XML
        return true;
    }

    return false;
}

//Re implemented in derived objects
XMLElement* ATProject::addToXMLDocumentAsChild(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
{
	return NULL;
}

bool ATProject::resetXML()
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
XMLElement* ATProject::addToXMLDocument(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
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

bool ATProject::save(const string& fName)
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

bool ATProject::open(const string& fName)
{
    try
    {
        if(fName.size())
        {
            setFileName(fName);
        }

        loadXMLFromFile(fName);

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

bool ATProject::createProjectFromXML(dsl::XMLNode* node)
{
    XMLElement* e = node->FirstChildElement("name");
    if(e)
    {
    	setProjectName(e->GetText() ? string(e->GetText()) : string(""));
    }

	return true;
}

int ATProject::createProjectObjects()
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
        ATProject* aProc = createATProjectObject(p);

        if(aProc)
        {
            mChilds.push_back(aProc);
            Log(lDebug) <<"Imported object: "<<aProc->getProjectName();
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

ATProject* ATProject::createATProjectObject(tinyxml2::XMLElement* element)
{
    if(!element && !compareStrings(element->Name(), "at_object", csCaseInsensitive))
    {
    	Log(lError) <<"Bad 'render_project' xml!";
    	return NULL;
    }

    ATProjectObjectType pt = toATProjectObjectType(element->Attribute("type"));
    switch(pt)
    {
        case atpRenderProject: 			return createRenderProject(element);
        case atpATDataProjectObject: 	return createATDataProject(element);

        default: return NULL;
    }
}

RenderProject* ATProject::createRenderProject(tinyxml2::XMLElement* element)
{
    if(!element && !compareStrings(element->Name(), "render_project", csCaseInsensitive))
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

RenderProject* ATProject::createATDataProject(tinyxml2::XMLElement* element)
{
    if(!element && !compareStrings(element->Name(), "render_project", csCaseInsensitive))
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


string toString(ATProjectObjectType tp)
{
	switch(tp)
    {
    	case atpBaseType: 		                return "ATProject";
    	case atpRenderProject: 	                return "renderProject";
        case atpVolume:			                return "volume";
        case atpATDataProjectObject:			return "atData";
        default:								return "unKnownObject";
    }
}

ATProjectObjectType toATProjectObjectType(const string& vcObject)
{
	if(     vcObject == "ATProject") return atpBaseType;
	else if(vcObject == "renderProject") 		return atpRenderProject;
	else if(vcObject == "volume") 				return atpVolume;
	else if(vcObject == "atData") 				return atpATDataProjectObject;
	else if(vcObject == "unKnownObject") 		return atpUnknown;

   	return atpUnknown;
}

}
