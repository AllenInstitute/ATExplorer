#include <vcl.h>
#pragma hdrstop
#include "ateAppUtilities.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
using namespace at;
using namespace dsl;

USEFORM("..\..\source\Frames\TGeneralPropertiesFrame.cpp", GeneralPropertiesFrame); /* TFrame: File Type */
USEFORM("..\..\source\Frames\TATProjectOptionsFrame.cpp", ATProjectOptionsFrame); /* TFrame: File Type */
USEFORM("..\..\source\Forms\TSelectRenderProjectParametersForm.cpp", SelectRenderProjectParametersForm);
USEFORM("..\..\source\Forms\TATESettingsForm.cpp", ATESettingsForm);
USEFORM("P:\libs\dsl\VCL\Frames\dslTLogMemoFrame.cpp", LogMemoFrame); /* TFrame: File Type */
USEFORM("..\..\source\TMainForm.cpp", MainForm);
//---------------------------------------------------------------------------
AppUtilities gAU;

int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{

	try
	{
		gAU.init();
  		Application->Initialize();
		Application->MainFormOnTaskBar = true;
        Application->Icon->LoadFromFile("ATExplorer.ico");
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
    catch(DSLException& e)
	{
        stringstream s;
        s << "There was an exception: \n";
        s << e.what();
        s <<"\n\nProgram will now exit";
        MessageDlg(s.str().c_str(), mtError, TMsgDlgButtons() << mbOK, 0);
        Log(lError) << s.str() << e.what();
    }
	catch (...)
	{
		try
		{
			throw Exception("Uncaught exception..");
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
//#pragma comment(lib, "DCEFBrowser.bpi")




