#pragma hdrstop
#include "atATIFDataProject.h"
#include "dslXMLUtils.h"
#include "Poco/URI.h"
#include "atATIFData.h"
//---------------------------------------------------------------------------

namespace at
{

using namespace dsl;

ATIFDataProject::ATIFDataProject(const string& pName, const string& rootFolder)
:
ATExplorerProject(pName),
mATIFData(rootFolder)
{
    mATEObjectType = (ateATIFDataProject);
    mTag = pName;
}

ATIFDataProject::~ATIFDataProject()
{}

//ATIFDataProject::ATIFDataProject(const ATIFDataProject& rp)
//:
//ATExplorerProject(rp),
////mDataRootFolder(rp.mDataRootFolder)
//{}


//Shallow copy..
//ATIFDataProject& ATIFDataProject::operator=(const ATIFDataProject& rhs)
//{
//	if(this != &rhs)
//    {
//    }
//    return *this;
//}

void ATIFDataProject::setDataRootFolder(const string& rFolder)
{
	mATIFData.setBasePath(rFolder);
}

string ATIFDataProject::getDataRootFolder() const
{
	string path = 	mATIFData.getBasePath().toString();
    return path;
}

XMLElement* ATIFDataProject::addToXMLDocumentAsChild(tinyxml2::XMLDocument& doc, XMLElement* parentNode)
{
    //Create XML for saving to file
    XMLElement* val(nullptr);

    val = doc.NewElement("datarootfolder");
    val->SetText(mATIFData.getBasePath().toString().c_str());
    parentNode->InsertEndChild(val);
    return val;
}

bool ATIFDataProject::loadFromXML(dsl::XMLNode* node)
{
    XMLElement* e(nullptr);
    e = node->FirstChildElement("datarootfolder");
    if(e)
    {
    	mATIFData.setBasePath(e->GetText() ? string(e->GetText()) : string(""));
    }

	return true;
}

bool ATIFDataProject::write()
{
	return false;
}

}
