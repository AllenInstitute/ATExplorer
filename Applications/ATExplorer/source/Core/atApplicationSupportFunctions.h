#ifndef atApplicationSupportFunctionsH
#define atApplicationSupportFunctionsH
#include <windows.h>
#include <System.Types.hpp>
#include <System.hpp>
//---------------------------------------------------------------------------

PACKAGE TPoint 			controlToImage(const TPoint& p, double scale, double stretchFactor);
PACKAGE void 			setupLogging();
PACKAGE int 			loadStyles();
PACKAGE void 			setupApplicationTheme();
PACKAGE int __stdcall 	FindOtherWindow(HWND hwnd, LPARAM lParam) ;

#endif
