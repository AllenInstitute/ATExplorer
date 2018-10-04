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
mDataRootFolder(rootFolder),
mATData(nullptr)
{
    mATEObjectType = (ateATIFDataProject);
}

ATIFDataProject::ATIFDataProject(const ATIFDataProject& rp)
:
ATExplorerProject(rp),
mDataRootFolder(rp.mDataRootFolder)
{
}

ATIFDataProject::~ATIFDataProject()
{
    delete mATData;
}

//Shallow copy..
ATIFDataProject& ATIFDataProject::operator=(const ATIFDataProject& rhs)
{
	if(this != &rhs)
    {
    }
    return *this;
}


void ATIFDataProject::setDataRootFolder(const string& rFolder)
{
    mDataRootFolder = rFolder;
}

string ATIFDataProject::getDataRootFolder() const
{
    return mDataRootFolder;
}


XMLElement* ATIFDataProject::addToXMLDocumentAsChild(tinyxml2::XMLDocument& doc, XMLElement* parentNode)
{
    //Create XML for saving to file
    XMLElement* val(nullptr);

    val = doc.NewElement("datarootfolder");
    val->SetText(mDataRootFolder.c_str());
    parentNode->InsertEndChild(val);

    return val;
}

bool ATIFDataProject::loadFromXML(dsl::XMLNode* node)
{
    XMLElement* e(nullptr);
    e = node->FirstChildElement("datarootfolder");
    if(e)
    {
    	mDataRootFolder = (e->GetText() ? string(e->GetText()) : string(""));
    }

	return true;
}

bool ATIFDataProject::write()
{
	return false;
}

}
