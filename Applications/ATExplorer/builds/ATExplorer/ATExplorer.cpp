#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <string>
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include "atApplicationSupportFunctions.h"
#include "dslRestartApplicationUtils.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "TMainForm.h"
#include "ateAppUtilities.h"
//---------------------------------------------------------------------------
using namespace dsl;
using namespace at;
using std::string;

USEFORM("P:\libs\dsl\VCL\Frames\dslTLogMemoFrame.cpp", LogMemoFrame); /* TFrame: File Type */
USEFORM("P:\libs\atapi\source\vcl\frames\TSSHFrame.cpp", SSHFrame); /* TFrame: File Type */
USEFORM("..\..\source\TMainForm.cpp", MainForm);
USEFORM("..\..\source\Forms\TATESettingsForm.cpp", ATESettingsForm);
USEFORM("..\..\source\Frames\TGeneralPropertiesFrame.cpp", GeneralPropertiesFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
AppUtilities gAU;

int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	gAU.init();

	try
	{
  		Application->Initialize();
		Application->MainFormOnTaskBar = true;
        Application->Icon->LoadFromFile("ATExplorer_Icon.ico");
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}

//---------------------------------------------------------------------------
#pragma comment(lib, "dslFoundation")
#pragma comment(lib, "dslVCLCommon.lib")
#pragma comment(lib, "dslVCLComponents.bpi")
#pragma comment(lib, "dslVCLVisualComponents.bpi")

#pragma comment(lib, "atFoundation.lib")
#pragma comment(lib, "atVCLCommon.lib")

#pragma comment(lib, "ATExplorerAppPackage.bpi")
#pragma comment(lib, "poco_foundation.lib")
#pragma comment(lib, "tinyxml2.lib")
#pragma comment(lib, "libcurl_imp.lib")
#pragma comment(lib, "DCEFBrowser.bpi")




