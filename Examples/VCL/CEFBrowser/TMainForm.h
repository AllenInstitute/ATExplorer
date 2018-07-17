#ifndef TMainFormH
#define TMainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "DcefB.Core.DcefBrowser.hpp"
#include <Vcl.ExtCtrls.hpp>

//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TDcefBrowser *DcefBrowser1;
	TPanel *Panel1;
	TEdit *URLEdit;
	TButton *Button1;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DcefBrowser1KeyEvent(ICefBrowser * const browser, const PCefKeyEvent event,
          PMsg osEvent, bool &Cancel);

private:	// User declarations
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
