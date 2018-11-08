#ifndef TSimpleTextInputDialogH
#define TSimpleTextInputDialogH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class PACKAGE TNewValueE : public TForm
{
__published:	// IDE-managed Components
	TButton *mCancelBtn;
	TButton *mOkBtn;
	TSTDStringLabeledEdit *NewValueE;
	void __fastcall OnChange(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);


private:	// User declarations

public:		// User declarations
				__fastcall 	TNewValueE(TComponent* Owner);
	string 					getText();
	void					setText(const string& txt);
    bool					mProcessReturn;
};

//---------------------------------------------------------------------------
extern PACKAGE TNewValueE *NewValueE;
//---------------------------------------------------------------------------
#endif
