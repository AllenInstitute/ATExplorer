#pragma hdrstop
#include "atVolumeCreatorProject.h"
#include "dslXMLUtils.h"
#include "dslLogger.h"
#include "atRenderProject.h"
using namespace dsl;
using namespace tinyxml2;

//XML Version history
/*
    0.5 : Original version
*/

const string gVolumeCreatorProjectFileVersion    = "0.6";

string VolumeCreatorProject::getVCObjectTypeAsString()
{
	return ::toString(mVCObjectType);
}

VolumeCreatorProject::VolumeCreatorProject(const string& projName)
:
Project(projName, "vc"),
mVCObjectType(vcoBaseType)
{
	resetXML();
}

VolumeCreatorProject::~VolumeCreatorProject()
{}

int	VolumeCreatorProject::getNumberOfChilds()
{
	int sz =  mChilds.size();
	return sz;
}

bool VolumeCreatorProject::isModified()
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

VolumeCreatorProject* VolumeCreatorProject::getChild(int i)
{
	if(i > 0 && i <= mChilds.size())
    {
		return mChilds[i - 1];
    }
    return NULL;
}

string VolumeCreatorProject::getPresentXMLModelVersion()
{
    return gVolumeCreatorProjectFileVersion;
}

bool VolumeCreatorProject::addChild(VolumeCreatorProject* child)
{
	if(child)
    {
    	mChilds.push_back(child);
        return true;
    }
	return false;
}

//Re implemented in derived objects
XMLElement* VolumeCreatorProject::addToXMLDocumentAsChild(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
{
	return NULL;
}

bool VolumeCreatorProject::resetXML()
{
	mTheXML.Clear();
    mProjectRoot = mTheXML.NewElement("vc_project");
    mRootNode = mTheXML.InsertFirstChild(mProjectRoot);

    //Insert as a minimum project file version
    XMLElement* xmlElement = mTheXML.NewElement("version");
    XMLText* 	xmlText = mTheXML.NewText(gVolumeCreatorProjectFileVersion.c_str());
    xmlElement->InsertEndChild(xmlText);
    mProjectRoot->InsertEndChild(xmlElement);

    xmlElement 		= mTheXML.NewElement("name");
    xmlText 		= mTheXML.NewText(getProjectName().c_str());
    xmlElement->InsertEndChild(xmlText);
    mProjectRoot->InsertEndChild(xmlElement);
    return true;
}

//Create header for VCObject node
XMLElement* VolumeCreatorProject::addToXMLDocument(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
{
    //Create XML for saving to file
    XMLElement* objectNode  	= doc.NewElement("vc_object");
    XMLNode*    rootNode 		= doc.InsertFirstChild(objectNode);

    //Attributes
    objectNode->SetAttribute("type", getVCObjectTypeAsString().c_str());
    objectNode->SetAttribute("name", getProjectName().c_str());

	XMLElement* dataval1 = doc.NewElement("info");
    dataval1->SetText(mInfoText.c_str());
	objectNode->InsertEndChild(dataval1);

    objectNode->InsertEndChild(rootNode);
    docRoot->InsertEndChild(objectNode);

    return objectNode;
}

bool VolumeCreatorProject::save(const string& fName)
{
    resetXML();

    XMLElement* objects = newElement("vc_objects");

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

bool VolumeCreatorProject::open()
{
    try
    {
    	loadFromXML(mProjectRoot);

        Log(lInfo) << "Attempting to load VC Project: "<<this->getFileName();

        //Read the name node
        int nrOfObjs = loadVCObjects();
        Log(lDebug) << "Loaded " << nrOfObjs << " VC objects";
        return true;
    }
    catch(...)
    {
        throw("Bad model file!");
    }
}

bool VolumeCreatorProject::loadFromXML(dsl::XMLNode* node)
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

int VolumeCreatorProject::loadVCObjects()
{
    XMLElement* project = this->getXML("vc_objects");

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
        VolumeCreatorProject* aProc = createVCObject(p);

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

VolumeCreatorProject* VolumeCreatorProject::createVCObject(tinyxml2::XMLElement* element)
{
    if(!element && !compareStrings(element->Name(), "vc_object", csCaseInsensitive))
    {
    	Log(lError) <<"Bad 'render_project' xml!";
    	return NULL;
    }

    VCObjectType pt = toVCObjectType(element->Attribute("type"));
    switch(pt)
    {
        case vcoRenderProject: return createRenderProject(element);
        default: return NULL;
    }
}

RenderProject* VolumeCreatorProject::createRenderProject(tinyxml2::XMLElement* element)
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

string toString(VCObjectType tp)
{
	switch(tp)
    {
    	case vcoBaseType: 		return "volumeCreatorProject";
    	case vcoRenderProject: 	return "renderProject";
        case vcoVolume:			return "volume";
        default:				return "unKnownObject";
    }
}

VCObjectType toVCObjectType(const string& vcObject)
{
	if(     vcObject == "volumeCreatorProject") return vcoBaseType;
	else if(vcObject == "renderProject") 		return vcoRenderProject;
	else if(vcObject == "volume") 				return vcoVolume;
	else if(vcObject == "unKnownObject") 		return vcoUnknown;

   	return vcoUnknown;
}
