#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "UIProperties.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTLogMemoFrame"
#pragma resource "*.dfm"
TMainForm *MainForm;

using namespace at;

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	:
    TRegistryForm(gUIProperties.AppRegistryRoot, "MainForm", Owner)
{
    //Setup some UI properties
	BottomPanel->Height 		= gUIProperties.BottomPanelHeight;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
	{
 	    Close();
     }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	gUIProperties.BottomPanelHeight = BottomPanel->Height;
	gUIProperties.GeneralProperties->write();
//    gATExplorer.writeProperties();

	//Write to file
	gUIProperties.getIniFile().save();
}


