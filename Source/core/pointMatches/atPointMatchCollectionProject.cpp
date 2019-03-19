#pragma hdrstop
#include "atPointMatchCollectionProject.h"
#include "dslXMLUtils.h"
#include "Poco/URI.h"
//---------------------------------------------------------------------------

namespace at
{

using namespace dsl;

PointMatchCollectionProject::PointMatchCollectionProject(const string& projName, const string& o, const string& name)
:
ATExplorerProject(projName),
mPointMatchCollection(o, name),
mRenderService(new RenderServiceParameters(""))
{
    mATEObjectType = (atePointMatchCollectionProject);
}

PointMatchCollectionProject::PointMatchCollectionProject(const string& projName, const PointMatchCollection& pmc)
:
ATExplorerProject(projName ),
mPointMatchCollection(pmc),
mRenderService(new RenderServiceParameters(""))
{
    mATEObjectType = (atePointMatchCollectionProject);
}

//PointMatchCollectionProject::PointMatchCollectionProject(const PointMatchCollectionProject& rp)
//:
//ATExplorerProject(rp),
//mRenderService(rp.mRenderService)
//{
////    mPointMatchCollectionProjectName      = rp.mPointMatchCollectionProjectName;
//}

PointMatchCollectionProject::~PointMatchCollectionProject()
{}

////Shallow copy..
//PointMatchCollectionProject& PointMatchCollectionProject::operator=(const PointMatchCollectionProject& rhs)
//{
//	if(this != &rhs)
//    {
//        mPointMatchCollectionProjectName	    = rhs.mPointMatchCollectionProjectName;
//        mRenderService          = rhs.mRenderService;
//    }
//    return *this;
//}

string PointMatchCollectionProject::getTypeName() const
{
    return "pointMatchCollectionProject";
}

bool PointMatchCollectionProject::setRenderServiceParameters(RenderServiceParameters* rsp)
{
    mRenderService = rsp;
    return true;
}

XMLElement* PointMatchCollectionProject::addToXMLDocumentAsChild(tinyxml2::XMLDocument& doc, XMLElement* parentNode)
{
    if(!mRenderService)
    {
        return NULL;
    }
    //Create XML for saving to file
    XMLElement* val(nullptr);

    val = doc.NewElement("owner");
    val->SetText(mPointMatchCollection.getOwner().c_str());
    parentNode->InsertEndChild(val);

    val = doc.NewElement("pointMatchContextName");
    val->SetText(mPointMatchCollection.getName().c_str());
    parentNode->InsertEndChild(val);

    val = doc.NewElement("pairCount");
    val->SetText(toString(mPointMatchCollection.getCount()).c_str());
    parentNode->InsertEndChild(val);
    return val;
}

bool PointMatchCollectionProject::loadFromXML(dsl::XMLNode* node)
{
    XMLElement* e(nullptr);

    e = node->FirstChildElement("owner");
    if(e)
    {
    	mPointMatchCollection.setOwner(e->GetText() ? string(e->GetText()) : string(""));
    }

    e = node->FirstChildElement("pointMatchContextName");
    if(e)
    {
    	mPointMatchCollection.setName(e->GetText() ? string(e->GetText()) : string(""));
    }

//    e = node->FirstChildElement("pairCount");
//    if(e)
//    {
//    	mPointMatchCollection.setCount(e->GetText() ? toInt(string(e->GetText())) : -1);
//    }
	return true;
}

bool PointMatchCollectionProject::write()
{
	return false;
}

}
