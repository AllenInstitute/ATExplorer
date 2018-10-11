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
//mATData(ATDataSP(new ATIFData(rootFolder)))
ATIFData(rootFolder)
{
    mATEObjectType = (ateATIFDataProject);
}

//ATIFDataProject::ATIFDataProject(const ATIFDataProject& rp)
//:
//ATExplorerProject(rp),
////mDataRootFolder(rp.mDataRootFolder)
//{}

ATIFDataProject::~ATIFDataProject()
{}

////Shallow copy..
//ATIFDataProject& ATIFDataProject::operator=(const ATIFDataProject& rhs)
//{
//	if(this != &rhs)
//    {
//    }
//    return *this;
//}

void ATIFDataProject::setDataRootFolder(const string& rFolder)
{
//    mDataRootFolder = rFolder;
//	if(mATData)
    {
		//mATData->setBasePath(rFolder);
		setBasePath(rFolder);
    }
}

string ATIFDataProject::getDataRootFolder() const
{
    if(mATData)
    {
    	return mATData->getBasePath().toString();
    }
    else
    {
        return "";
    }
}

XMLElement* ATIFDataProject::addToXMLDocumentAsChild(tinyxml2::XMLDocument& doc, XMLElement* parentNode)
{
    //Create XML for saving to file
    XMLElement* val(nullptr);

    val = doc.NewElement("datarootfolder");
    val->SetText(mATData->getBasePath().toString().c_str());
    parentNode->InsertEndChild(val);
    return val;
}

bool ATIFDataProject::loadFromXML(dsl::XMLNode* node)
{
    XMLElement* e(nullptr);
	mATData = ATIFDataSP(new ATIFData(string("")));
    e = node->FirstChildElement("datarootfolder");
    if(e)
    {
    	mATData->setBasePath(e->GetText() ? string(e->GetText()) : string(""));
    }

	return true;
}

bool ATIFDataProject::write()
{
	return false;
}

}
