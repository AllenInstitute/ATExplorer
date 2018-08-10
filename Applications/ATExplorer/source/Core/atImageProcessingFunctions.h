#ifndef atImageProcessingFunctionsH
#define atImageProcessingFunctionsH
#include <Dialogs.hpp>
#include <math.h>
//---------------------------------------------------------------------------
PACKAGE bool loadImage(const AnsiString filename, Graphics::TBitmap *bitmap);
PACKAGE void convertToGrayScale(TImage *image);
PACKAGE void sobel(TImage *image);
PACKAGE void negative(TImage *image);
PACKAGE void averageFilter(TImage *image);
PACKAGE void medianFilter(TImage *image);
PACKAGE void flipH(TImage *image);
PACKAGE void flipV(TImage *image);
PACKAGE void stretchHistogram(TImage *image);
PACKAGE void sobel2(TImage *image);
PACKAGE void addImages(TImage *ImgA, TImage *ImgB, TImage *Result);
PACKAGE void subtractImages(TImage *ImgA, TImage *ImgB, TImage *Result);
PACKAGE void averageImages(TImage *ImgA, TImage *ImgB, TImage *Result);
PACKAGE void oldPicture(TImage *Image);
PACKAGE void linearTransformation(TImage *image, Byte **auximage, float a,  int b);

#endif

