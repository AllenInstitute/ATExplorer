#pragma hdrstop
#include "atTiffStackProject.h"
#include "dslFileUtils.h"
#include <sstream>
//---------------------------------------------------------------------------
namespace at
{

using namespace dsl;
using namespace std;

TiffStackProject::TiffStackProject(const string& fName, const Path& p)
:
mFilePath(p)
{}

TiffStackProject::~TiffStackProject()
{}

string TiffStackProject::getInfo()
{
    stringstream info;
    info<<"FileName: "                      <<mFileName << '\n';
    info<<"FilePath: "                      <<mFilePath.toString() << '\n';
    info<<"Region of Interest (ROI): " 		<<mROI.asString() << '\n';
    info<<"Z's: " 							<<mSections.asString() << '\n';
    info<<"Min, Max intensity: " 	   		<<mMinIntensity <<','<<mMaxIntensity<< '\n';
    info<<"Channels: " 	   					<<mChannels.asString()<< '\n';

    return info.str();
}

bool TiffStackProject::deleteData()
{
    //delete stack from disk
    return removeFile(joinPath(mFilePath.toString(), mFileName));
}

TiffStackProject::TiffStackProject(const TiffStackProject& stack)
{
    mFileName 		= stack.mFileName;
    mFilePath 		= stack.mFilePath;
    mROI			= stack.mROI;
    mSections		= stack.mSections;
    mMinIntensity 	= stack.mMinIntensity;
    mMaxIntensity	= stack.mMaxIntensity;
    mChannels       = stack.mChannels;
}

void TiffStackProject::reset()
{
    mFileName 		= "";
    mFilePath 		= "";
    mROI			= RegionOfInterest();
    mSections.clear();
    mMinIntensity 	= -1;
    mMaxIntensity	= -1;
    mChannels.clear();
}
void TiffStackProject::appendChannel(const string& ch)
{
    mChannels.append(ch);
}

void TiffStackProject::setChannels(const StringList& chs)
{
    mChannels = chs;
}

StringList TiffStackProject::getChannels()
{
    return mChannels;
}

StringList TiffStackProject::getSections()
{
    return mSections;
}

void TiffStackProject::setSections(const StringList& s)
{
    mSections = s;
}

void TiffStackProject::setROI(const RegionOfInterest& roi)
{
    mROI = roi;
}

RegionOfInterest TiffStackProject::getROI()
{
    return mROI;
}

void TiffStackProject::setIntensities(int min, int max)
{
	mMinIntensity = min;
	mMaxIntensity = max;
}

void TiffStackProject::setFilePath(const Path& p)
{
    mFilePath = p;
}

Path TiffStackProject::getFilePath()
{
    return mFilePath;
}

XMLElement* TiffStackProject::addToXMLDocumentAsChild(tinyxml2::XMLDocument& doc, XMLElement* stacks)
{
    XMLElement* stackNode  	= doc.NewElement("tiff_stack");
    XMLNode*    rootNode   	= doc.InsertFirstChild(stackNode);

	stackNode->SetAttribute("name", this->getProjectName().c_str());
    stackNode->InsertEndChild(rootNode);

    //Create XML for saving to file
    XMLElement* val(nullptr);

    val = doc.NewElement("filename");
    val->SetText(mFileName.c_str());
    stackNode->InsertEndChild(val);

    val = doc.NewElement("filepath");
    val->SetText(mFilePath.toString().c_str());
    stackNode->InsertEndChild(val);

    val = doc.NewElement("channels");
    val->SetText(mChannels.asString(',').c_str());
    stackNode->InsertEndChild(val);

    val = doc.NewElement("sections");
    val->SetText(mSections.asString(',').c_str());
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

bool TiffStackProject::loadFromXML(dsl::XMLNode* node)
{
    XMLElement* e(node->ToElement());

    string projName = e->Attribute("name") ? e->Attribute("name") : "Missing Name";
    e = node->FirstChildElement("filename");

    this->setProjectName(projName);

    if(e)
    {
    	mFileName = (e->GetText() ? string(e->GetText()) : string(""));
    }

    e = node->FirstChildElement("filepath");
    if(e)
    {
    	mFilePath = Path(e->GetText() ? string(e->GetText()) : string(""));
    }

    e = node->FirstChildElement("sections");
    if(e)
    {
    	mSections = StringList(e->GetText() ? string(e->GetText()) : string(""), ',');
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

bool TiffStackProject::write()
{
	return false;
}




}

