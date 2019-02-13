#include <vcl.h>
#pragma hdrstop
#include "dslLogger.h"
#include "UIProperties.h"
#include "atATExplorer.h"
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("TMainForm.cpp", MainForm);
//---------------------------------------------------------------------------
using namespace at;
using namespace dsl;

ATExplorer gATExplorer; //The destructor for gATExplorer executes before destruction of the main form.. weird..


int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
        //Keep track of Application related properties in an INIFile and Registry
		gUIProperties.init();
        gUIProperties.setupGeneralProperties();
        gUIProperties.GeneralProperties->read();

        gATExplorer.Properties.LogFileName.setValue(gUIProperties.getLogFileNameAndPath());
	    gATExplorer.init(gUIProperties.getIniFile());

        Application->Icon->LoadFromFile("ATExplorer.ico");
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		TStyleManager::TrySetStyle("Golden Graphite");
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

