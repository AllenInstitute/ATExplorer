//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TMainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DcefB.Core.DcefBrowser"
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
	DcefBrowser1->Load("http://atbigdawg.corp.alleninstitute.org/synapses/view/synapsecollection/12");
}
//---------------------------------------------------------------------------

