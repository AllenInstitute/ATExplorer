#pragma hdrstop
#include "atPointMatchContextProject.h"
#include "dslXMLUtils.h"
#include "Poco/URI.h"
//---------------------------------------------------------------------------

namespace at
{

using namespace dsl;

PointMatchContextProject::PointMatchContextProject(const string& projName, const string& o, const string& name, int pairCount)
:
ATExplorerProject(projName),
mPointMatchContext(o, name, pairCount),
mRenderService(new RenderServiceParameters("", ""))
{
    mATEObjectType = (atePointMatchContextProject);
}

PointMatchContextProject::PointMatchContextProject(const string& projName, const PointMatchContext& pmc)
:
ATExplorerProject(projName ),
mPointMatchContext(pmc),
mRenderService(new RenderServiceParameters("", ""))
{
    mATEObjectType = (atePointMatchContextProject);
}

//PointMatchContextProject::PointMatchContextProject(const PointMatchContextProject& rp)
//:
//ATExplorerProject(rp),
//mRenderService(rp.mRenderService)
//{
////    mPointMatchContextProjectName      = rp.mPointMatchContextProjectName;
//}

PointMatchContextProject::~PointMatchContextProject()
{}

////Shallow copy..
//PointMatchContextProject& PointMatchContextProject::operator=(const PointMatchContextProject& rhs)
//{
//	if(this != &rhs)
//    {
//        mPointMatchContextProjectName	    = rhs.mPointMatchContextProjectName;
//        mRenderService          = rhs.mRenderService;
//    }
//    return *this;
//}

string PointMatchContextProject::getTypeName() const
{
    return "pointMatchContextProject";
}

bool PointMatchContextProject::setRenderServiceParameters(RenderServiceParameters* rsp)
{
    mRenderService = rsp;
    return true;
}

XMLElement* PointMatchContextProject::addToXMLDocumentAsChild(tinyxml2::XMLDocument& doc, XMLElement* parentNode)
{
    if(!mRenderService)
    {
        return NULL;
    }
    //Create XML for saving to file
    XMLElement* val(nullptr);

    val = doc.NewElement("owner");
    val->SetText(mPointMatchContext.getOwner().c_str());
    parentNode->InsertEndChild(val);

    val = doc.NewElement("pointMatchContextName");
    val->SetText(mPointMatchContext.getName().c_str());
    parentNode->InsertEndChild(val);

    val = doc.NewElement("pairCount");
    val->SetText(toString(mPointMatchContext.getPairCount()).c_str());
    parentNode->InsertEndChild(val);
    return val;
}

bool PointMatchContextProject::loadFromXML(dsl::XMLNode* node)
{
    XMLElement* e(nullptr);

    e = node->FirstChildElement("owner");
    if(e)
    {
    	mPointMatchContext.setOwner(e->GetText() ? string(e->GetText()) : string(""));
    }

    e = node->FirstChildElement("pointMatchContextName");
    if(e)
    {
    	mPointMatchContext.setName(e->GetText() ? string(e->GetText()) : string(""));
    }

    e = node->FirstChildElement("pairCount");
    if(e)
    {
    	mPointMatchContext.setPairCount(e->GetText() ? toInt(string(e->GetText())) : -1);
    }
	return true;
}

bool PointMatchContextProject::write()
{
	return false;
}

}
