#include <vcl.h>
#pragma hdrstop
#include "atApplicationSupportFunctions.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

TPoint controlToImage(const TPoint& p, double scale, double stretchFactor)
{
	TPoint pt;
    if(scale > 0)
    {
    	pt.X = (p.X / scale) / stretchFactor;
	    pt.Y = (p.Y / scale) / stretchFactor;
    }
	return pt;
}

