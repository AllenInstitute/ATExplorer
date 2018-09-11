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

    String url = URLEdit->Text;

	DcefBrowser1->Load(url);
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
void __fastcall TMainForm::DcefBrowser1KeyEvent(ICefBrowser * const browser,
          const PCefKeyEvent event, PMsg osEvent, bool &Cancel)
{
    if(event->native_key_code == 27) //Esc
    {
        Close();
    }
}


