#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslLogger.h"
#include "ateAppUtilities.h"
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------
using namespace dsl;
using namespace at;
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
    static bool firstShow(true);

    if(mIsStyleMenuPopulated == false)
    {
        populateStyleMenu(ThemesMenu, ThemesMenuClick);
        mIsStyleMenuPopulated = true;
	}

    if(gAU.LastOpenedProject.getValue().size() > 0 && firstShow == true)
    {
        FileOpen1Accept(NULL);
    }
    firstShow = false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	this->Caption = vclstr(createWindowTitle("ATExplorer", Application));
    this->DoubleBuffered = true;

	gLogger.setLogLevel(gAU.LogLevel);
    TLogMemoFrame1->init();
}

bool TMainForm::setupAndReadIniParameters()
{
	//Setup parameters
    gAU.setupIniParameters();
	gAU.GeneralProperties->read();

    //Setup UI
	BottomPanel->Height 		= gAU.BottomPanelHeight;
    ProjectManagerPanel->Width 	= gAU.ProjectPanelWidth == 0 ? 100 : gAU.ProjectPanelWidth; //Gotta be at least 100px on startup
	//	mRC.setLocalCacheFolder(gAU.LocalCacheFolder.getValue());

	if(gAU.LastOpenedProject.getValue().size())
    {
        Log(lInfo) << "Last opened project: " << gAU.LastOpenedProject;
		TMenuItem *Item = new TMenuItem(ReopenMenu);
        Item->Caption = gAU.LastOpenedProject.getValue().c_str();
        FileOpen1->Dialog->FileName = gAU.LastOpenedProject.getValue().c_str();
        Item->OnClick = FileOpen1Accept;
        ReopenMenu->Add(Item);
        ReopenMenu->Enabled = true;

    }
    return true;
}

