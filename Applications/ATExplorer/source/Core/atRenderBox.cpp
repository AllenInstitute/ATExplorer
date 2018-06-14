#pragma hdrstop
#include "atRenderBox.h"
#include <math.h>
//---------------------------------------------------------------------------
using namespace std;


RenderBox::RenderBox(double x, double y, double width, double height, double scale)
:
	mX1(x),
	mY1(y),
	mWidth(width),
	mHeight(height),
    mScale(scale)
{}

//f is from -100 to +100
void RenderBox::zoom(double f)
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
    else //Zooming out(box will get bigger)
    {
	    newWidth  = mWidth  / (1.0 - fabs(1.0 - f));
    	newHeight = mHeight / (1.0 - fabs(1.0 - f));

		mX1 = mX1 - fabs(newWidth - mWidth ) / 2.0;
		mY1 = mY1 - fabs(newHeight- mHeight) / 2.0;
    }

    mWidth 	= newWidth;
    mHeight = newHeight;
}


