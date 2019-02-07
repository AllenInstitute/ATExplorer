#include <vcl.h>
#pragma hdrstop
#include "dslLogger.h"
#include "UIProperties.h"
#include "atATExplorer.h"
//---------------------------------------------------------------------------
USEFORM("TMainForm.cpp", MainForm);
//---------------------------------------------------------------------------
using namespace at;
using namespace dsl;


int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
        //Keep track of Application related properties in an INIFile and Registry
		gRDBMProperties.init();

        gATExplorer.Properties.LogFileName.setValue(gRDBMProperties.getLogFileNameAndPath());

		Application->Initialize();
		Application->MainFormOnTaskBar = true;
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

#pragma comment(lib, "atExplorerFoundation.lib")
#pragma comment(lib, "atExplorerVCL.bpi")
//#pragma comment(lib, "ATExplorerAppPackage.bpi")

#pragma comment(lib, "poco_foundation.lib")
#pragma comment(lib, "tinyxml2.lib")

