#include <vcl.h>
#pragma hdrstop
#include "TImageCloneForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TImageCloneForm *ImageCloneForm;
//---------------------------------------------------------------------------

//  TRegistryForm(const string& regRoot, const string& formName, TComponent* Owner);
__fastcall TImageCloneForm::TImageCloneForm(const string& regRoot, const string& fName, TComponent* Owner)
	: TRegistryForm(regRoot, fName, Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TImageCloneForm::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree;
}
//---------------------------------------------------------------------------

