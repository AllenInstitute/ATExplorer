#ifndef TMainFormH
#define TMainFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include "dslTRegistryForm.h"
#include "dslTLogMemoFrame.h"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------


class TMainForm  : public TRegistryForm
{
    __published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TListBox *ListBox1;
	TButton *Button1;
	TLogMemoFrame *TLogMemoFrame1;
	TPanel *BottomPanel;
	TSplitter *Splitter1;
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

    private:	// User declarations
    public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
};

extern PACKAGE TMainForm *MainForm;
#endif
