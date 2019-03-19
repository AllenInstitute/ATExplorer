#include <vcl.h>
#pragma hdrstop
#include "ATExplorerUIProperties.h"

//USEFORM("..\..\..\..\Source\vcl\frames\TRenderServicesFrame.cpp", RenderServicesFrame); /* TFrame: File Type */
//USEFORM("..\..\source\Forms\TATESettingsForm.cpp", ATESettingsForm);
//USEFORM("..\..\source\Forms\TAboutATExplorerForm.cpp", AboutATExplorer);
//USEFORM("..\..\source\Frames\TGeneralPropertiesFrame.cpp", GeneralPropertiesFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
USEFORM("..\..\source\Frames\TGeneralPropertiesFrame.cpp", GeneralPropertiesFrame); /* TFrame: File Type */
USEFORM("..\..\..\..\Source\vcl\frames\TRenderServicesFrame.cpp", RenderServicesFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//   Package source.

#pragma argsused
extern "C" int _libmain(unsigned long reason)
{
	return 1;
}
//---------------------------------------------------------------------------
#pragma comment(lib, "dslFoundation.lib")
#pragma comment(lib, "dslVCLCommon.lib")
#pragma comment(lib, "dslVCLComponents.bpi")
#pragma comment(lib, "dslVCLVisualComponents.bpi")

#pragma comment(lib, "atExplorerFoundation.lib")
#pragma comment(lib, "atExplorerVCL.lib")

#pragma comment(lib, "poco_foundation.lib")
#pragma comment(lib, "tinyxml2.lib")
#pragma comment(lib, "libcurl_imp.lib")



