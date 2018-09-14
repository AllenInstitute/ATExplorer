#include <vcl.h>
#pragma hdrstop
#include "TSelectRenderProjectParametersForm.h"
#include "dslStringList.h"
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTSTDStringLabeledEdit"
#pragma resource "*.dfm"
TSelectRenderProjectParametersForm *SelectRenderProjectParametersForm;
//---------------------------------------------------------------------------

using namespace dsl;

//---------------------------------------------------------------------------
__fastcall TSelectRenderProjectParametersForm::TSelectRenderProjectParametersForm(TComponent* Owner)
	: TForm(Owner),
    mRP("", "", "" , ""),
    mRC(mRP,IdHTTP1)
{
    mRC.setBaseURL(BaseURLE->getValue());

    //Populate owners
    StringList o = mRC.getOwners();
    if(o.size())
    {
		populateDropDown(o, OwnerCB);
        OwnerCB->ItemIndex = 0;
        OwnerCB->Text = OwnerCB->Items->Strings[0];
		OwnerCBChange(NULL);
    }
}

string TSelectRenderProjectParametersForm::getRenderOwner()
{
    return stdstr(OwnerCB->Text);
}

string TSelectRenderProjectParametersForm::getRenderProject()
{
    return stdstr(ProjectCB->Text);
}

RenderServiceParameters TSelectRenderProjectParametersForm::getRenderService()
{
	RenderServiceParameters service(BaseURLE->getValue(), HostPort->getValue());
    return service;
}
//---------------------------------------------------------------------------
void __fastcall TSelectRenderProjectParametersForm::FormCloseQuery(TObject *Sender,
          bool &CanClose)
{
    if(this->ModalResult == mrOk)
    {
        if(OwnerCB->Text.Length() < 1 || ProjectCB->Text.Length() < 1)
        {
            MessageDlg("Select an Owner and Project", mtInformation, TMsgDlgButtons() << mbOK, 0);
            CanClose = false;
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TSelectRenderProjectParametersForm::OwnerCBChange(TObject *Sender)
{
	//Populate projects
    //Populate projects
    StringList p = mRC.getProjectsForOwner(stdstr(OwnerCB->Text));
    if(p.size())
    {
		populateDropDown(p, ProjectCB);
        ProjectCB->ItemIndex = 0;
        ProjectCB->Text = ProjectCB->Items->Strings[0];
    }
}

//---------------------------------------------------------------------------
void __fastcall TSelectRenderProjectParametersForm::PopulateOwnersBtnClick(TObject *Sender)
{
    mRC.setBaseURL(BaseURLE->getValue());

    //Populate owners
    StringList o = mRC.getOwners();
    if(o.size())
    {
		populateDropDown(o, OwnerCB);
        OwnerCB->ItemIndex = 0;
        OwnerCB->Text = OwnerCB->Items->Strings[0];
		OwnerCBChange(NULL);
    }
}


