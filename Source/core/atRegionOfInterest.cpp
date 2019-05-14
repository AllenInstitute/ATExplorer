#pragma hdrstop
#include "atRegionOfInterest.h"
#include <math.h>
#include "Poco/URI.h"
#include "dslStringList.h"
#include <sstream>

//---------------------------------------------------------------------------

namespace at
{
using namespace std;
using namespace dsl;


RegionOfInterest::RegionOfInterest(const string& _box, double scale)
:
mZ(0),
onChange(NULL)
{
	//-4515,-2739,9027,5472,0.1338
    StringList box(_box, ',');
    if(box.count() < 4)
    {
        throw("Bad stuff...");
    }

	mX 		= toDouble(box[0]);
	mY 		= toInt(box[1]);
	mWidth 	= toInt(box[2]);
	mHeight = toInt(box[3]);

   	mScale	= (box.count() >= 5) ? toDouble(box[4]) : scale;
}

RegionOfInterest::RegionOfInterest(int x, int y, int width, int height, double scale)
:
mZ(0),
mX(x),
mY(y),
mWidth(width),
mHeight(height),
mScale(scale),
onChange(NULL)
{}

RegionOfInterest::RegionOfInterest(const RegionOfInterest& cpme)
:
mZ(cpme.mZ),
mX(cpme.mX),
mY(cpme.mY),
mWidth(cpme.mWidth),
mHeight(cpme.mHeight),
mScale(cpme.mScale)
{}

RegionOfInterest& RegionOfInterest::operator=(const RegionOfInterest& rhs)
{
    bool changed2D(false);
    if(&rhs != this)
    {
        if(mZ != rhs.mZ)
        {
        	mZ  = rhs.mZ;
        }

        if(mX != rhs.mX)
        {
	        mX = rhs.mX;
            changed2D = true;
        }

        if(mY != rhs.mY)
        {
            mY = rhs.mY;
            changed2D = true;
        }

        if(mWidth != rhs.mWidth)
        {
	        mWidth = rhs.mWidth;
            changed2D = true;
        }

        if(mHeight != rhs.mHeight)
        {
	        mHeight = rhs.mHeight;
            changed2D = true;
        }

        if(mScale != rhs.mScale)
        {
        	mScale = rhs.mScale;
            changed2D = true;
        }
    }

//    if(onChange && changed2D)
//    {
//        onChange(NULL, NULL);
//    }
    return *this;
}

string RegionOfInterest::asString()
{
    stringstream i;
    i << "X = " << mX << '\n';
    i << "Y = " << mY << '\n';
    i << "Width = " << mWidth << '\n';
    i << "Height = " << mHeight << '\n';
    i << "Scale = " << mScale << '\n';
    i << "Z = " << mZ << '\n';

    return i.str();
}
string RegionOfInterest::getFolderName() const
{
    stringstream p;
    p << (int) mX << "," << (int) mY << "," <<  (int) mWidth << "," <<  (int) mHeight;
    return p.str();
}

void RegionOfInterest::assignOnChangeCallback(OnChangeFnc f)
{
	onChange = f;
}

void RegionOfInterest::setX1(int x){mX = x;}
int RegionOfInterest::getX1() const {return mX;}
void RegionOfInterest::setX2(int x){mWidth = abs(mX - x);}

int RegionOfInterest::getX2() const {return mX + mWidth;}
void  RegionOfInterest::setWidth(int w){mWidth = w;}
int RegionOfInterest::getWidth() const {return mWidth;}

void  RegionOfInterest::setY1(int y){mY = y;}
int RegionOfInterest::getY1() const {return mY;}

void  RegionOfInterest::setY2(int y){mHeight = abs(mY - y);}
int RegionOfInterest::getY2() const {return mY + mHeight;}

void  RegionOfInterest::setHeight(int h){mHeight = h;}
int RegionOfInterest::getHeight() const {return mHeight;}

void  RegionOfInterest::setZ(int z){mZ = z;}
int RegionOfInterest::getZ() const {return mZ;}

void  RegionOfInterest::setScale(double s){mScale = s;}
double RegionOfInterest::getScale() const {return mScale;}

//f is from -100 to +100
void RegionOfInterest::zoom(double f)
{
	f = 1.0 - f/100.0;

    double newWidth;
    double newHeight;

    if(f < 1)//Zooming in, box gets smaller
    {
	    newWidth  = mWidth  * f;
    	newHeight = mHeight * f;

		mX = mX + fabs(mWidth  - newWidth ) / 2.0;
		mY = mY + fabs(mHeight - newHeight) / 2.0;
    }
    else //Zooming out(box get bigger)
    {
	    newWidth  = mWidth  / (1.0 - fabs(1.0 - f));
    	newHeight = mHeight / (1.0 - fabs(1.0 - f));

		mX = mX - fabs(newWidth - mWidth ) / 2.0;
		mY = mY - fabs(newHeight- mHeight) / 2.0;
    }

    mWidth 	= newWidth;
    mHeight = newHeight;
}

XMLElement* RegionOfInterest::addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLNode* parentNode)
{
    //Create XML for saving to file
    XMLElement* roi(nullptr);
    roi = doc.NewElement("roi");

//    	int								mZ;
//	    double                          mX;
//    	double                          mY;
//	    int                             mWidth;
//    	int                             mHeight;
//      double							mScale;

    XMLElement* val(nullptr);
    val = doc.NewElement("z");
    val->SetText(mZ);
    roi->InsertEndChild(val);

    val = doc.NewElement("x");
    val->SetText(mX);
    roi->InsertEndChild(val);

    val = doc.NewElement("y");
    val->SetText(mY);
    roi->InsertEndChild(val);

    val = doc.NewElement("width");
    val->SetText(mWidth);
    roi->InsertEndChild(val);

    val = doc.NewElement("height");
    val->SetText(mHeight);
    roi->InsertEndChild(val);

    val = doc.NewElement("scale");
    val->SetText(mScale);
    roi->InsertEndChild(val);

    parentNode->InsertEndChild(roi);
    return roi;
}

bool RegionOfInterest::loadFromXML(dsl::XMLNode* node)
{
    XMLElement* e(nullptr);

    e = node->FirstChildElement("z");
    if(e)
    {
    	mZ = (e->GetText() ? dsl::toInt(e->GetText()) : 0);
    }

    e = node->FirstChildElement("x");
    if(e)
    {
    	mX = (e->GetText() ? dsl::toInt(e->GetText()) : 0);
    }

    e = node->FirstChildElement("y");
    if(e)
    {
    	mY = (e->GetText() ? dsl::toInt(e->GetText()) : 0);
    }

    e = node->FirstChildElement("width");
    if(e)
    {
    	mWidth = (e->GetText() ? dsl::toInt(e->GetText()) : 100);
    }

    e = node->FirstChildElement("height");
    if(e)
    {
    	mHeight = (e->GetText() ? dsl::toInt(e->GetText()) : 100);
    }

    e = node->FirstChildElement("scale");
    if(e)
    {
    	mScale = (e->GetText() ? dsl::toDouble(e->GetText()) : 1);
    }
    return true;
}

}
