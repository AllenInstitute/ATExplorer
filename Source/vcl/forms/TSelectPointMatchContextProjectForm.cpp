#pragma hdrstop
#include "TSelectPointMatchContextProjectForm.h"
#include "dslStringList.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "dslFileUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTSTDStringLabeledEdit"
#pragma resource "*.dfm"
TSelectPointmatchContextProjectForm *SelectPointmatchContextProjectForm;
//---------------------------------------------------------------------------

using namespace dsl;

//---------------------------------------------------------------------------
__fastcall TSelectPointmatchContextProjectForm::TSelectPointmatchContextProjectForm(ATExplorer& e, TComponent* Owner)
	: TForm(Owner),
    mRP("", "", "" , ""),
    mRC(mRP,IdHTTP1, e.DefaultRenderService),
    mExplorer(e)
{
    try
    {
        RenderServicesCB->Clear();
        RenderServiceParameters* rs =  mExplorer.getFirstRenderService();
        while(rs)
        {
            RenderServicesCB->AddItem(rs->getName().c_str(), (TObject*) rs);
            rs = mExplorer.getNextRenderService();
        }
    }
    catch(...)
    {
//        Log(lError) << "We were not able to connect to host: " << BaseURLE->getValue();
    }
}

string TSelectPointmatchContextProjectForm::getRenderOwner()
{
    return stdstr(OwnerCB->Text);
}

string TSelectPointmatchContextProjectForm::getMatchCollection()
{
    return stdstr(CollectionCB->Text);
}

string TSelectPointmatchContextProjectForm::getOutputFolderLocation()
{
    return OutputDataRootFolderE->getValue();
}

RenderServiceParameters* TSelectPointmatchContextProjectForm::getRenderService()
{
	int index = RenderServicesCB->ItemIndex;
    if(index == -1)
    {
        return nullptr;
    }
	RenderServiceParameters* service = (RenderServiceParameters*) RenderServicesCB->Items->Objects[index];
    return service;
}
//---------------------------------------------------------------------------
void __fastcall TSelectPointmatchContextProjectForm::FormCloseQuery(TObject *Sender,
          bool &CanClose)
{
    if(this->ModalResult == mrOk)
    {
        if(OwnerCB->Text.Length() < 1 || CollectionCB->Text.Length() < 1)
        {
            MessageDlg("Please select an Owner and a Project", mtInformation, TMsgDlgButtons() << mbOK, 0);
            CanClose = false;
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TSelectPointmatchContextProjectForm::OwnerCBChange(TObject *Sender)
{
    //Populate projects
    StringList p = mRC.getPointMatchCollectionNamesForOwner(stdstr(OwnerCB->Text));
    if(p.size())
    {
		populateDropDown(p, CollectionCB);
        CollectionCB->ItemIndex = 0;
        CollectionCB->Text = CollectionCB->Items->Strings[0];
    }
}

//---------------------------------------------------------------------------
void __fastcall TSelectPointmatchContextProjectForm::PopulateOwnersBtnClick(TObject *Sender)
{
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

//---------------------------------------------------------------------------
void __fastcall TSelectPointmatchContextProjectForm::BrowseForDataOutputPathBtnClick(TObject *Sender)
{
    TButton* btn = dynamic_cast<TButton*>(Sender);

    if(btn == BrowseForDataOutputPathBtn)
    {
        //Browse for folder
        string res = browseForFolder(OutputDataRootFolderE->getValue());
        if(folderExists(res))
        {
            OutputDataRootFolderE->setValue(res);
        }
        else
        {
            Log(lWarning) << "Path was not set..!";
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TSelectPointmatchContextProjectForm::FormKeyDown(TObject *Sender,
          WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
	{
 	    Close();
     }
}

//---------------------------------------------------------------------------
void __fastcall TSelectPointmatchContextProjectForm::RenderServicesCBCloseUp(TObject *Sender)
{
    mRC.setRenderServiceParameters(getRenderService());
}

//---------------------------------------------------------------------------
void __fastcall TSelectPointmatchContextProjectForm::RenderServicesCBChange(TObject *Sender)

{
    mRC.setRenderServiceParameters(getRenderService());
}


