#pragma hdrstop
#include "atRegionOfInterest.h"
#include <math.h>
#include "Poco/URI.h"
#include "dslStringList.h"
#include <sstream>
#pragma package(smart_init)
//---------------------------------------------------------------------------
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
	mY 		= toDouble(box[1]);
	mWidth 	= toDouble(box[2]);
	mHeight = toDouble(box[3]);

   	mScale	= (box.count() >= 5) ? toDouble(box[4]) : scale;
}

RegionOfInterest::RegionOfInterest(double x, double y, double width, double height, double scale)
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

void RegionOfInterest::setX1(double x){mX = x;}
double RegionOfInterest::getX1(){return mX;}
void RegionOfInterest::setX2(double x){mWidth = abs(mX - x);}

double RegionOfInterest::getX2(){return mX + mWidth;}
void  RegionOfInterest::setWidth(double w){mWidth = w;}
double RegionOfInterest::getWidth(){return mWidth;}

void  RegionOfInterest::setY1(double y){mY = y;}
double RegionOfInterest::getY1(){return mY;}

void  RegionOfInterest::setY2(double y){mHeight = abs(mY - y);}
double RegionOfInterest::getY2(){return mY + mHeight;}

void  RegionOfInterest::setHeight(double h){mHeight = h;}
double RegionOfInterest::getHeight(){return mHeight;}

void  RegionOfInterest::setZ(double z){mZ = z;}
double RegionOfInterest::getZ(){return mZ;}

void  RegionOfInterest::setScale(double s){mScale = s;}
double RegionOfInterest::getScale(){return mScale;}

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


