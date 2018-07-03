#pragma hdrstop
#include "atATDataProjectObject.h"
#include "dslXMLUtils.h"
#include "dslFileUtils.h"
#include "atATData.h"
//---------------------------------------------------------------------------

using namespace dsl;


namespace at
{

ATDataProjectObject::ATDataProjectObject(const shared_ptr<ATData>& data)
:
ATProject(""),
mATData(data)
{
	mATProjectObjectType = atpATDataProjectObject;
    if(data)
    {
        mBasePath = (data->getBasePath());
        Path p = mBasePath;
        string fName = p.directory(p.depth()-1);
        setProjectName(fName);
    }
}

ATDataProjectObject::ATDataProjectObject(const Path& basePath, ATDataFileFormat atDataFormat)
:
ATProject(basePath.getFileName()),
mBasePath(basePath),
mATData(shared_ptr<ATData>())
{
	mATProjectObjectType = (atpATDataProjectObject);
}

XMLElement* ATDataProjectObject::addToXMLDocumentAsChild(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
{
    //Create XML for saving to file

    XMLElement* val = doc.NewElement("basepath");
    string bp(mBasePath.toString());
    val->SetText(bp.c_str());
    docRoot->InsertEndChild(val);

    return val;
}

bool ATDataProjectObject::loadFromXML(dsl::XMLNode* node)
{
    XMLElement* e = node->FirstChildElement("basepath");
    if(e)
    {
    	mBasePath = e->GetText() ? string(e->GetText()) : string("");
    }

	return true;
}

bool ATDataProjectObject::write()
{
	return false;
}

}
