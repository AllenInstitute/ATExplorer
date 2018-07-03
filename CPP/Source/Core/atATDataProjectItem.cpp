#pragma hdrstop
#include "atATDataProjectItem.h"
#include "dslXMLUtils.h"
#include "dslFileUtils.h"
#include "atATData.h"
//---------------------------------------------------------------------------

using namespace dsl;


namespace at
{

ATDataProjectItem::ATDataProjectItem(const shared_ptr<ATData>& data)
:
ATProject(""),
mATData(data)
{
	mATProjectObjectType = atpATDataProjectItem;
    if(data)
    {
        mBasePath = (data->getBasePath());
        Path p = mBasePath;
        string fName = p.directory(p.depth()-1);
        setProjectName(fName);
    }
}

ATDataProjectItem::ATDataProjectItem(const Path& basePath, ATDataFileFormat atDataFormat)
:
ATProject(basePath.getFileName()),
mBasePath(basePath),
mATData(shared_ptr<ATData>())
{
	mATProjectObjectType = (atpATDataProjectItem);
}

XMLElement* ATDataProjectItem::addToXMLDocumentAsChild(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
{
    //Create XML for saving to file

    XMLElement* val = doc.NewElement("basepath");
    string bp(mBasePath.toString());
    val->SetText(bp.c_str());
    docRoot->InsertEndChild(val);

    return val;
}

bool ATDataProjectItem::loadFromXML(dsl::XMLNode* node)
{
    XMLElement* e = node->FirstChildElement("basepath");
    if(e)
    {
    	mBasePath = e->GetText() ? string(e->GetText()) : string("");
    }

	return true;
}

bool ATDataProjectItem::write()
{
	return false;
}

}
