#pragma hdrstop
#include "atRegionOfInterest.h"
#include <math.h>
#include "Poco/URI.h"
#include "dslStringList.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace std;
using namespace dsl;


RegionOfInterest::RegionOfInterest(const string& _box)
{
	//-4515,-2739,9027,5472,0.1338

    StringList box(_box, ',');

    if(box.count() != 5)
    {
        throw("Bad stuff...");
    }

	mX1 = toDouble(box[0]);
	mY1 = toDouble(box[1]);
	mWidth = toDouble(box[2]);
	mHeight = toDouble(box[3]);
    mScale	= toDouble(box[4]);

}

RegionOfInterest::RegionOfInterest(double x, double y, double width, double height, double scale)
:
	mX1(x),
	mY1(y),
	mWidth(width),
	mHeight(height),
    mScale(scale)
{}


void RegionOfInterest::setX1(double x){mX1 = x;}
double RegionOfInterest::getX1(){return mX1;}
void RegionOfInterest::setX2(double x){mWidth = abs(mX1 - x);}

double RegionOfInterest::getX2(){return mX1 + mWidth;}
void  RegionOfInterest::setWidth(double w){mWidth = w;}
double RegionOfInterest::getWidth(){return mWidth;}

void  RegionOfInterest::setY1(double y){mY1 = y;}
double RegionOfInterest::getY1(){return mY1;}

void  RegionOfInterest::setY2(double y){mHeight = abs(mY1 - y);}
double RegionOfInterest::getY2(){return mY1 + mHeight;}

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

		mX1 = mX1 + fabs(mWidth  - newWidth ) / 2.0;
		mY1 = mY1 + fabs(mHeight - newHeight) / 2.0;
    }
    else //Zooming out(box get bigger)
    {
	    newWidth  = mWidth  / (1.0 - fabs(1.0 - f));
    	newHeight = mHeight / (1.0 - fabs(1.0 - f));

		mX1 = mX1 - fabs(newWidth - mWidth ) / 2.0;
		mY1 = mY1 - fabs(newHeight- mHeight) / 2.0;
    }

    mWidth 	= newWidth;
    mHeight = newHeight;
}


