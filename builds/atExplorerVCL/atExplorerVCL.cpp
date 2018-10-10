#include <vcl.h>
#pragma hdrstop
USEFORM("P:\libs\atapi\source\vcl\frames\TSSHFrame.cpp", SSHFrame); /* TFrame: File Type */
USEFORM("..\..\Source\vcl\forms\TCreateLocalVolumesForm.cpp", CreateLocalVolumesForm);
USEFORM("..\..\Source\vcl\forms\TImageForm.cpp", ImageForm);
USEFORM("..\..\Source\vcl\frames\TRenderProjectFrame.cpp", RenderProjectFrame); /* TFrame: File Type */
USEFORM("..\..\Source\vcl\frames\TATIFDataProjectFrame.cpp", ATIFDataProjectFrame); /* TFrame: File Type */
USEFORM("..\..\Source\vcl\frames\TATProjectOptionsFrame.cpp", ATProjectOptionsFrame); /* TFrame: File Type */
USEFORM("..\..\Source\vcl\frames\TCreateStackThreadFrame.cpp", CreateStackThreadFrame); /* TFrame: File Type */
USEFORM("..\..\Source\vcl\forms\TCreateATIFDataProjectForm.cpp", CreateATIFDataProjectForm);
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



