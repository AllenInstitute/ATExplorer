#pragma hdrstop
#include "atTiffStack.h"
//---------------------------------------------------------------------------
namespace at
{

using namespace dsl;

TiffStack::TiffStack(const string& fName, const Path& p)
:
mFileName(fName),
mFilePath(p)
{}

TiffStack::~TiffStack()
{}

void TiffStack::setIntensities(int min, int max)
{
	mMinIntensity = min;
	mMaxIntensity = max;
}

XMLElement* TiffStack::addToXMLDocumentAsChild(tinyxml2::XMLDocument& doc, XMLElement* stacks)
{
    XMLElement* stackNode  	= doc.NewElement("tiff_stack");
    XMLNode*    rootNode   	= doc.InsertFirstChild(stackNode);
    stackNode->InsertEndChild(rootNode);

    //Create XML for saving to file
    XMLElement* val(nullptr);

    val = doc.NewElement("filename");
    val->SetText(mFileName.c_str());
    stackNode->InsertEndChild(val);

    val = doc.NewElement("filepath");
    val->SetText(mFilePath.toString().c_str());
    stackNode->InsertEndChild(val);

    mROI.addToXMLDocumentAsChild(doc, stackNode);

    val = doc.NewElement("min_intensity");
    val->SetText(mMinIntensity);
    stackNode->InsertEndChild(val);

    val = doc.NewElement("max_intensity");
    val->SetText(mMaxIntensity);
    stackNode->InsertEndChild(val);

    stacks->InsertEndChild(stackNode);
    return stackNode;
}

bool TiffStack::loadFromXML(dsl::XMLNode* node)
{
    XMLElement* e(nullptr);

    e = node->FirstChildElement("filename");
    if(e)
    {
    	mFileName = (e->GetText() ? string(e->GetText()) : string(""));
    }

    e = node->FirstChildElement("filepath");
    if(e)
    {
    	mFilePath = Path(e->GetText() ? string(e->GetText()) : string(""));
    }

    e = node->FirstChildElement("roi");
    if(e)
    {
	    mROI.loadFromXML(e);
    }

    e = node->FirstChildElement("min_intensity");
    if(e)
    {
    	mMinIntensity = (e->GetText() ? dsl::toInt(e->GetText()) : 0);
    }

    e = node->FirstChildElement("max_intensity");
    if(e)
    {
    	mMaxIntensity = (e->GetText() ? dsl::toInt(e->GetText()) : 0);
    }

	return true;
}

bool TiffStack::write()
{
	return false;
}




}

