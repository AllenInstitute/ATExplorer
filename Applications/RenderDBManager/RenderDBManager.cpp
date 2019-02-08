#include <vcl.h>
#pragma hdrstop
#include "dslLogger.h"
#include "UIProperties.h"
#include "atATExplorer.h"
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("TMainForm.cpp", MainForm);
USEFORM("P:\libs\dsl\VCL\Frames\dslTLogMemoFrame.cpp", LogMemoFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
using namespace at;
using namespace dsl;


int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
        //Keep track of Application related properties in an INIFile and Registry
		gUIProperties.init();
        gUIProperties.setupGeneralProperties();
        gUIProperties.GeneralProperties->read();

        gATExplorer.Properties.LogFileName.setValue(gUIProperties.getLogFileNameAndPath());

		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		TStyleManager::TrySetStyle("Golden Graphite");
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TLogMemoFrame), &LogMemoFrame);
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

#pragma comment(lib, "atExplorerFoundation.lib")
#pragma comment(lib, "atExplorerVCL.bpi")
//#pragma comment(lib, "ATExplorerAppPackage.bpi")

#pragma comment(lib, "poco_foundation.lib")
#pragma comment(lib, "tinyxml2.lib")

