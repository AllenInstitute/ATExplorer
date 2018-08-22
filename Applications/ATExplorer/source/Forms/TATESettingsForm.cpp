#include <vcl.h>
#pragma hdrstop
#include "TATESettingsForm.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

TATESettingsForm *ATESettingsForm;

using namespace dsl;
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

void TATESettingsForm::append(shared_ptr<Properties> props)
{
    mSections.append(props);
    TTreeNode* n = TreeView1->Items->AddChild(BaseNode, props->getSection().c_str());
}

bool TATESettingsForm::enablePropertyEdits()
{
    mSections.enableEdits();
    return true;
}

bool TATESettingsForm::disablePropertyEdits()
{
    mSections.disableEdits();
    return true;
}

bool TATESettingsForm::discardPropertyEdits()
{
    mSections.discardEdits();
    return true;
}

int TATESettingsForm::applyPropertyEdits()
{
    //Check general setting
	mSections.applyEdits();
    return -1;
}

//---------------------------------------------------------------------------
void __fastcall TATESettingsForm::TreeView1Change(TObject *Sender, TTreeNode *Node)
{
    if(Node->Selected)
    {
        Log(lInfo) << "User selected: " << stdstr(Node->Text);

        //Extract the properties
        shared_ptr<Properties> props = mSections.getSection(stdstr(Node->Text));
        if(props && props->getSection() == "General")
        {
            populateGeneralPanel(*props);
        }
    }
}

void TATESettingsForm::populateGeneralPanel(Properties& props)
{
	if(!mGeneralPropertiesFrame)
    {
    	mGeneralPropertiesFrame = shared_ptr<TGeneralPropertiesFrame>(new TGeneralPropertiesFrame(this));
    }

    mGeneralPropertiesFrame->Parent = this;
    mGeneralPropertiesFrame->Align = alClient;
    mGeneralPropertiesFrame->populate(props);
}

//---------------------------------------------------------------------------
void __fastcall TATESettingsForm::FormShow(TObject *Sender)
{
    //Find the last expanded item
    enablePropertyEdits();

}

//---------------------------------------------------------------------------
void __fastcall TATESettingsForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    if(ModalResult == mrOk)
    {
        applyPropertyEdits();
    }

    disablePropertyEdits();
}


