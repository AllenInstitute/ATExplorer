#include <vcl.h>
#pragma hdrstop
#include "TATESettingsForm.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "ateAppUtilities.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

TATESettingsForm *ATESettingsForm;

using namespace dsl;
using namespace at;

TTreeNode* getItemWithCaption(const string& c, TTreeView* tv);
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

TTreeNode* TATESettingsForm::append(shared_ptr<Properties> props)
{
    mSections.append(props);
    TTreeNode* n = TreeView1->Items->AddChild(BaseNode, props->getSectionName().c_str());
    return n;
}

bool TATESettingsForm::enablePropertyEdits()
{
    return mSections.enableEdits();
}

bool TATESettingsForm::disablePropertyEdits()
{
    return mSections.disableEdits();
}

bool TATESettingsForm::discardPropertyEdits()
{
    return mSections.discardEdits();
}

int TATESettingsForm::applyPropertyEdits()
{
    //Check general setting
	return mSections.applyEdits();
}

//---------------------------------------------------------------------------
void __fastcall TATESettingsForm::TreeView1Change(TObject *Sender, TTreeNode *Node)
{
    if(Node->Selected)
    {
        Log(lInfo) << "User selected: " << stdstr(Node->Text);
        gAU.LastSelectedSettingsSection.setValue("ERE");//stdstr(Node->Text));
        //Extract the properties
        shared_ptr<Properties> props = mSections.getSection(stdstr(Node->Text));
        if(props && props->getSectionName() == "General")
        {
            populateGeneralPanel(*props);
        }
        else
        {
			if(mGeneralPropertiesFrame)
		    {
                mGeneralPropertiesFrame->Hide();
        	}
        }
    }
}

void TATESettingsForm::populateGeneralPanel(Properties& props)
{
//	if(!mGeneralPropertiesFrame)
//    {
//    	mGeneralPropertiesFrame = shared_ptr<TGeneralPropertiesFrame>(new TGeneralPropertiesFrame(this));
//    }
//
//    mGeneralPropertiesFrame->Parent = this;
//    mGeneralPropertiesFrame->Align = alClient;
//    mGeneralPropertiesFrame->populate(props);
//    mGeneralPropertiesFrame->Show();
}

//---------------------------------------------------------------------------
void __fastcall TATESettingsForm::FormShow(TObject *Sender)
{
    //Enabling property edits causes any values changed in the UI to be stored
    //in a properties "Edit" value. The Edit value is propagated to
    //the properties real value if user selects OK
//    enablePropertyEdits();

//    string c = gAU.LastSelectedSettingsSection;
//	//Find the last expanded item
//    TTreeNode* n = getItemWithCaption(c, TreeView1);
//    if(n)
//    {
//        n->Selected = true;
//        n->Expanded = true;
//    }
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
//
//TTreeNode* getItemWithCaption(const string& c, TTreeView* tv)
//{
//    TTreeNode* baseNode = tv->Items->GetFirstNode();
//    TTreeNode* node = baseNode->getFirstChild();
//    while(node != NULL)
//    {
//        if(node->Text == vclstr(c))
//        {
//            return node;
//        }
//        node = baseNode->GetNextChild(node);
//    };
//    return NULL;
//}
//
//---------------------------------------------------------------------------
void __fastcall TATESettingsForm::TreeView1Click(TObject *Sender)
{
;
}


