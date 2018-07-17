#pragma hdrstop
#include "atATDataProjectItem.h"
#include "dslXMLUtils.h"
#include "dslFileUtils.h"
#include "atATData.h"
//---------------------------------------------------------------------------

using namespace dsl;


namespace at
{

ATDataProjectItem::ATDataProjectItem(const string& lbl, const shared_ptr<ATData>& data)
:
ATProjectItem(""),
mATData(data)
{
	mATProjectItemType = atpATDataProjectItem;
    if(data)
    {
        mBasePath = (data->getBasePath());
        Path p = mBasePath;
        string fName = p.directory(p.depth()-1);
        setProjectName(fName);
    }
    else
    {
        setProjectName(lbl);
    }
}

ATDataProjectItem::ATDataProjectItem(const string& lbl, const Path& basePath, ATDataFileFormat atDataFormat)
:
ATProjectItem(basePath.getFileName()),
mBasePath(basePath),
mATData(shared_ptr<ATData>())
{
	mATProjectItemType = (atpATDataProjectItem);
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
