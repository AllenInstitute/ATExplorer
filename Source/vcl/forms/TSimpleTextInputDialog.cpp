#include <vcl.h>
#pragma hdrstop
#include "TSimpleTextInputDialog.h"
#include "dslVCLUtils.h"

using namespace dsl;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTStdStringLabeledEdit"
#pragma resource "*.dfm"
TNewValueE *NewValueE;
//---------------------------------------------------------------------------
__fastcall TNewValueE::TNewValueE(TComponent* Owner)
	: TForm(Owner),
    mProcessReturn(true)
{
}

//---------------------------------------------------------------------------
string TNewValueE::getText()
{
	return NewValueE->getValue();
}

//---------------------------------------------------------------------------
void __fastcall TNewValueE::OnChange(TObject *Sender)
{
	mOkBtn->Enabled = (NewValueE->Modified) ? true : false;
}

void TNewValueE::setText(const string& txt)
{
    NewValueE->setValue(txt);
}

//---------------------------------------------------------------------------
void __fastcall TNewValueE::FormShow(TObject *Sender)
{
    ActiveControl = NewValueE;
    this->Update();
}

void __fastcall TNewValueE::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == vkEscape)
    {
     	this->ModalResult = mrCancel;
    }
}


