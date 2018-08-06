#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "MagickWand/MagickWand.h"
//#include "ImageMagick.h"
#include <string>
using namespace std;

#define QuantumScale  ((MagickRealType) 1.0/(MagickRealType) QuantumRange)
#define SigmoidalContrast(x) \
  (QuantumRange*(1.0/(1+exp(10.0*(0.5-QuantumScale*x)))-0.0066928509)*1.0092503)
#define ThrowWandException(wand) \
{ \
  char \
    *description; \
 \
  ExceptionType \
    severity; \
 \
  description=MagickGetException(wand,&severity); \
  (void) fprintf(stderr,"%s %s %lu %s\n",GetMagickModule(),description); \
  description=(char *) MagickRelinquishMemory(description); \
  exit(-1); \
}

#define min(a, b)  (((a) < (b)) ? (a) : (b))
#define max(a, b)  (((a) > (b)) ? (a) : (b))

//void TMainForm::flipImage(MagickWand *image_wand,int deg)
//{
//    MagickBooleanType status;
//    PixelWand *background = NewPixelWand();
//    PixelSetColor(background,"#111111");
//    status = MagickRotateImage(image_wand, background, deg);
//    DestroyPixelWand(background);
//
////	int angle = deg;//45;        //45° for example
////	float radians=(2*3.1416*angle)/360;
////	float cosine=(float)cos(radians);
////	float sine=(float)sin(radians);
////
////	Graphics::TBitmap *SrcBitmap = Image1->Picture->Bitmap;// Graphics::TBitmap;
////	Graphics::TBitmap *DestBitmap=new Graphics::TBitmap;
////
////    float Point1x=(-SrcBitmap->Height*sine);
////    float Point1y=(SrcBitmap->Height*cosine);
////    float Point2x=(SrcBitmap->Width*cosine-SrcBitmap->Height*sine);
////    float Point2y=(SrcBitmap->Height*cosine+SrcBitmap->Width*sine);
////    float Point3x=(SrcBitmap->Width*cosine);
////    float Point3y=(SrcBitmap->Width*sine);
////
////    float minx=min(0,min(Point1x,min(Point2x,Point3x)));
////    float miny=min(0,min(Point1y,min(Point2y,Point3y)));
////    float maxx=max(Point1x,max(Point2x,Point3x));
////    float maxy=max(Point1y,max(Point2y,Point3y));
////
////    int DestBitmapWidth=(int)ceil(fabs(maxx)-minx);
////    int DestBitmapHeight=(int)ceil(fabs(maxy)-miny);
////
////    SetGraphicsMode(DestBitmap->Canvas->Handle,GM_ADVANCED);
////    XFORM xform;
////    xform.eM11=cosine;
////    xform.eM12=-sine;
////    xform.eM21=sine;
////    xform.eM22=cosine;
////    xform.eDx=(float)-minx;
////    xform.eDy=(float)-miny;
////
////
////    DestBitmap->Height=DestBitmapHeight;
////    DestBitmap->Width=DestBitmapWidth;
////
////    SetWorldTransform(DestBitmap->Canvas->Handle,&xform);
////
////    BitBlt(DestBitmap->Canvas->Handle,
////           0,
////           0,
////           DestBitmap->Width,
////           DestBitmap->Height,
////           SrcBitmap->Canvas->Handle,
////           0,
////           0,
////           SRCCOPY);
////
////    //Show the rotated bitmap
////    Image1->Picture->Bitmap = DestBitmap;
////    delete DestBitmap;
////    delete SrcBitmap;
//
//
//
//}
//
//void TMainForm::applyContrastControl(MagickWand *image_wand)
//{
//    MagickBooleanType status;
//    PixelInfo pixel;
//    PixelIterator *contrast_iterator, *iterator;
//    PixelWand **contrast_pixels, **pixels;
//    register ssize_t x;
//    size_t width;
//
//    /*    Sigmoidal non-linearity contrast control.    */
//    iterator = NewPixelIterator(image_wand);
//    contrast_iterator = NewPixelIterator(image_wand);
//    if ((iterator == (PixelIterator *) NULL) || (contrast_iterator == (PixelIterator *) NULL))
//    {
//    	ThrowWandException(image_wand);
//    }
//
//    ssize_t y;
//    for (y = 0; y < (ssize_t) MagickGetImageHeight(image_wand); y++)
//    {
//	    pixels = PixelGetNextIteratorRow(iterator,&width);
//    	contrast_pixels = PixelGetNextIteratorRow(contrast_iterator, &width);
//    	if ((pixels == (PixelWand **) NULL) || (contrast_pixels == (PixelWand **) NULL))
//        {
//      		break;
//        }
//
//        for (x = 0; x < (ssize_t) width; x++)
//        {
//        	PixelGetMagickColor(pixels[x],&pixel);
//          	pixel.red=SigmoidalContrast(pixel.red);
//          	pixel.green=SigmoidalContrast(pixel.green);
//          	pixel.blue=SigmoidalContrast(pixel.blue);
//          	pixel.index=SigmoidalContrast(pixel.index);
//          	PixelSetPixelColor(contrast_pixels[x], &pixel);
//        }
//
//    	(void) PixelSyncIterator(contrast_iterator);
//    }
//
//    if (y < (ssize_t) MagickGetImageHeight(image_wand))
//    {
//        ThrowWandException(image_wand);
//    }
//
//    contrast_iterator=DestroyPixelIterator(contrast_iterator);
//    iterator=DestroyPixelIterator(iterator);
//}
//
////---------------------------------------------------------------------------
//void TMainForm::colorImage(MagickWand *image_wand, int colorIndex)
//{
//  	PixelWand *colorize = NewPixelWand();
//  	PixelWand *opacity = NewPixelWand();
//   	char* op = "#255";
//    switch(colorIndex)
//    {
//
//     	case 1:
//	  		PixelSetColor(colorize, "red");
//		  	PixelSetColor(opacity, op);
//		break;
//
//        case 2:
//	  		PixelSetColor(colorize, "green");
//		  	PixelSetColor(opacity, op);
//        break;
//
//        case 3:
//	  		PixelSetColor(colorize, "blue");
//		  	PixelSetColor(opacity, op);
//        break;
//
//        case 4:
//	  		PixelSetColor(colorize, "magenta");
//		  	PixelSetColor(opacity, op);
//        break;
//    }
//
//
//  	MagickColorizeImage(image_wand, colorize, opacity);
//}
