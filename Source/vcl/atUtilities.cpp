#include <vcl.h>
#pragma hdrstop
#include "atUtilities.h"
#include "dslStringUtils.h"
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace dsl;

TTabSheet* getTabWithCaption(const string& c, TPageControl* pc)
{
    if(!pc)
    {
        return NULL;
    }

    for(int i = 0; i < pc->PageCount; i++)
    {
        if(compareStrings(stdstr(pc->Pages[i]->Caption), c, csCaseSensitive))
        {
            return pc->Pages[i];
        }
    }

    return NULL;
}

//---------------------------------------------------------------------------
double getCurrentImageWidth(TImage* img)
{
    //This function assumes stretch is proportional
    double origW = img->Picture->Width;
    double origH = img->Picture->Height;
    double imageR = origW / origH;

    double containerW = img->Width;
    double containerH = img->Height;
    double containerR = containerW / containerH;

    if(containerR > imageR)
    {
    	return containerH * imageR;
    }
    else
    {
    	return containerW;
    }
}

//---------------------------------------------------------------------------
double getCurrentImageHeight(TImage* img)
{
    //This function assumes stretch is proportional
    double origW = img->Picture->Width;
    double origH = img->Picture->Height;
    double imageR = origW / origH;

    double containerW = img->Width;
    double containerH = img->Height;
    double containerR = containerW / containerH;

    if(containerR > imageR)
    {
        return containerH;
    }
    else
    {
    	return containerW /imageR;
    }
}

