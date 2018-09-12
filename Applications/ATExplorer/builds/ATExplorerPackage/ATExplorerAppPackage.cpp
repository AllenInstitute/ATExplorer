#include <vcl.h>
#pragma hdrstop
USEFORM("..\..\source\Frames\TGeneralPropertiesFrame.cpp", GeneralPropertiesFrame); /* TFrame: File Type */
USEFORM("..\..\source\Frames\TImageControlsFrame.cpp", ImageControlsFrame); /* TFrame: File Type */
USEFORM("..\..\source\Frames\TRenderProjectFrame.cpp", RenderProjectFrame); /* TFrame: File Type */
USEFORM("..\..\source\Frames\TRenderPythonRemoteScriptFrame.cpp", RenderPythonRemoteScriptFrame); /* TFrame: File Type */
USEFORM("P:\libs\atapi\source\vcl\frames\TSSHFrame.cpp", SSHFrame); /* TFrame: File Type */
USEFORM("..\..\source\Forms\TAboutATExplorerForm.cpp", AboutATExplorer);
USEFORM("..\..\source\Forms\TImageForm.cpp", ImageForm);
USEFORM("..\..\source\Forms\TSelectRenderProjectParametersForm.cpp", SelectRenderProjectParametersForm);
USEFORM("..\..\source\Forms\TSelectZsForm.cpp", SelectZsForm);
USEFORM("..\..\source\Frames\TAffineTransformationFrame.cpp", AffineTransformationFrame); /* TFrame: File Type */
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
#pragma comment(lib, "sbridge250.bpi")

#pragma comment(lib, "dslFoundation")
#pragma comment(lib, "dslVCLCommon.lib")
#pragma comment(lib, "dslVCLComponents.bpi")
#pragma comment(lib, "dslVCLVisualComponents.bpi")

#pragma comment(lib, "atFoundation.lib")
#pragma comment(lib, "atExplorerFoundation.lib")
#pragma comment(lib, "atVCLCommon.lib")

#pragma comment(lib, "poco_foundation.lib")
#pragma comment(lib, "tinyxml2.lib")
#pragma comment(lib, "libcurl_imp.lib")

//#pragma comment(lib, "DCEFBrowser.bpi")



