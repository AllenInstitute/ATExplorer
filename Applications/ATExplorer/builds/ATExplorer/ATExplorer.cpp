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
//---------------------------------------------------------------------------
//extern string		gAppName					= "ATExplorer";
//extern string       gLogFileName                = "ATExplorer.log";
//extern string       gAppDataLocation            = joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), gAppName);
//extern string 		gApplicationRegistryRoot  	= "\\Software\\Allen Institute\\ATExplorer\\0.5.0";
//extern string       gApplicationStyle           = "Iceberg Classico";
//extern string       gApplicationMutexName       = "ATExplorerMutex";
//extern HWND         gOtherAppWindow             = NULL;
//extern string       gRestartMutexName           = "ATExplorerRestartMutex";


AppUtilities au;

int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	au.init();
    //The app mutex is used to check for already running instances
    HANDLE appMutex;
	try
	{

//        appMutex = ::CreateMutexA(NULL, FALSE, gApplicationMutexName.c_str());
//        if( ERROR_ALREADY_EXISTS == GetLastError() )
//        {
//            // The Program is already running somewhere
//            MessageDlg("It seems ATExplorer is already running!\nOnly one instance can be running at any one time..", mtWarning, TMsgDlgButtons() << mbOK, 0);
//            ::EnumWindows(FindOtherWindow, NULL);
//
//            if(gOtherAppWindow != NULL)
//            {
//                //Send a custom message to restore window here..
//            }
//
//            return(1);
//        }
//
//		gApplicationStyle = readStringFromRegistry(gApplicationRegistryRoot, "", "Theme",  gApplicationStyle);
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
        Application->Icon->LoadFromFile("ATExplorer_Icon.ico");
        setupLogging();

		TStyleManager::TrySetStyle("Carbon");

		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->Run();
//		writeStringToRegistry(gApplicationRegistryRoot, "", "Theme",  gApplicationStyle);
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




