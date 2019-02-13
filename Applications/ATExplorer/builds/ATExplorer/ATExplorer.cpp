#include <vcl.h>
#pragma hdrstop
#include "ATExplorerUIProperties.h"
#include "dslLogger.h"
#include "atATExplorer.h"
#include <memory>
//---------------------------------------------------------------------------
using namespace at;
using namespace dsl;

ATExplorer gATExplorer;
//The destructor for gATExplorer executes before destruction of the main form.. weird..


USEFORM("..\..\source\TMainForm.cpp", MainForm);
USEFORM("..\..\source\Forms\TAboutATExplorerForm.cpp", AboutATExplorer);
USEFORM("..\..\source\Forms\TATESettingsForm.cpp", ATESettingsForm);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
        //Keep track of Application related properties in an INIFile and Registry
		gUIProperties.init();

        //Setup parameters
        gUIProperties.setupGeneralProperties();
        gUIProperties.GeneralProperties->read();

        gATExplorer.Properties.LogFileName.setValue(gUIProperties.getLogFileNameAndPath());
	    gATExplorer.init(gUIProperties.getIniFile());

  		Application->Initialize();
		Application->MainFormOnTaskBar = true;
        Application->Icon->LoadFromFile("ATExplorer.ico");
		Application->CreateForm(__classid(TMainForm), &MainForm);
         Application->CreateForm(__classid(TAboutATExplorer), &AboutATExplorer);
         Application->CreateForm(__classid(TATESettingsForm), &ATESettingsForm);
         Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
    catch(DSLException& e)
	{
        stringstream s;
        s << "There was a DSL exception: \n";
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

#pragma comment(lib, "atExplorerFoundation.lib")
#pragma comment(lib, "atExplorerVCL.bpi")
#pragma comment(lib, "ATExplorerAppPackage.bpi")

#pragma comment(lib, "poco_foundation.lib")
#pragma comment(lib, "tinyxml2.lib")





