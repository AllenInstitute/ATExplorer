#include <vcl.h>
#pragma hdrstop
#include "ateAppUtilities.h"

USEFORM("..\..\source\Forms\TAboutATExplorerForm.cpp", AboutATExplorer);
USEFORM("..\..\source\Forms\TATESettingsForm.cpp", ATESettingsForm);
USEFORM("..\..\source\Frames\TGeneralPropertiesFrame.cpp", GeneralPropertiesFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//   Package source.

using namespace at;

//This GLOBAL object carries application specific paarametes, utilities etc..
//AppUtilities PACKAGE gAU;

#pragma argsused
extern "C" int _libmain(unsigned long reason)
{
	return 1;
}
//---------------------------------------------------------------------------
#pragma comment(lib, "dslFoundation.lib")
#pragma comment(lib, "sbridge250.bpi")

#pragma comment(lib, "dslFoundation")
#pragma comment(lib, "dslVCLCommon.lib")
#pragma comment(lib, "dslVCLComponents.bpi")
#pragma comment(lib, "dslVCLVisualComponents.bpi")

#pragma comment(lib, "atFoundation.lib")
#pragma comment(lib, "atExplorerFoundation.lib")
#pragma comment(lib, "atExplorerVCL.lib")
#pragma comment(lib, "atVCLCommon.lib")

#pragma comment(lib, "poco_foundation.lib")
#pragma comment(lib, "tinyxml2.lib")
#pragma comment(lib, "libcurl_imp.lib")

//#pragma comment(lib, "DCEFBrowser.bpi")



