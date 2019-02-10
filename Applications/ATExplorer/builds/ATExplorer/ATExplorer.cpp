#include <vcl.h>
#pragma hdrstop
#include "ATExplorerUIProperties.h"
#include "dslLogger.h"
#include "atATExplorer.h"
#include <memory>
//---------------------------------------------------------------------------
using namespace at;
using namespace dsl;

USEFORM("..\..\source\TMainForm.cpp", MainForm);
USEFORM("..\..\..\..\Source\vcl\forms\TRenderAPIChecker.cpp", RenderAPIChecker);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
        //Keep track of Application related properties in an INIFile and Registry
		gAU.init();

        //Setup parameters
        gAU.setupGeneralProperties();
        gAU.GeneralProperties->read();
        gATExplorer.Properties.LogFileName.setValue(gAU.getLogFileNameAndPath());
	    gATExplorer.init(gAU.getIniFile());

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





