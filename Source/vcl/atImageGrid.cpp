#include <vcl.h>
#pragma hdrstop
#include "atImageGrid.h"
#include <Vcl.ExtCtrls.hpp>
#include "atVCLUtils.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

namespace at
{

ImageGrid::ImageGrid(TImage* img, TCanvas* canvas)
:
mImage(img),
mCanvas(canvas)
{}

ImageGrid::~ImageGrid()
{}

void ImageGrid::hide()
{
    mCanvas->Refresh();
}

void ImageGrid::paint()
{
	if(!mImage->Picture->Height || !mImage->Picture->Width)
    {
        return;
    }

    double w = getCurrentImageWidth(mImage);
	double h = getCurrentImageHeight(mImage);

    mCanvas->Pen->Mode = pmCopy;
    mCanvas->Pen->Color = clGray;
    mCanvas->Pen->Width = 0.5;

    int nrOfXLines(20);
    int yOffset(h/nrOfXLines);

    for(int i = 0; i < nrOfXLines; i++)
    {
		mCanvas->MoveTo(0, yOffset*(i+1));
		mCanvas->LineTo(w, yOffset*(i+1));
    }

    int nrOfYLines(20);
    int xOffset(w/nrOfYLines);

    for(int i = 0; i < nrOfYLines; i++)
    {
		mCanvas->MoveTo(xOffset*(i+1), 0);
		mCanvas->LineTo(xOffset*(i+1), h);
    }
}

}
