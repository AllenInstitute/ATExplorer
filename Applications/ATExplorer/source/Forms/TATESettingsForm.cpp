#include <vcl.h>
#pragma hdrstop
#include "TATESettingsForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TATESettingsForm *ATESettingsForm;
//---------------------------------------------------------------------------
__fastcall TATESettingsForm::TATESettingsForm(TComponent* Owner)
	: TForm(Owner)
{
	 BaseNode = TreeView1->Items->Add(NULL, "Properties");
}

//---------------------------------------------------------------------------
void __fastcall TATESettingsForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}

void TATESettingsForm::append(PropertiesSP props)
{
    mSections.push_back(props);


    TreeView1->Items->AddChild(BaseNode, props->getSection().c_str());
}




