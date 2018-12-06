#pragma hdrstop
#include "TCreateATIFDataProjectForm.h"
#include "dslStringList.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "dslFileUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTSTDStringLabeledEdit"
#pragma resource "*.dfm"
TCreateATIFDataProjectForm *CreateATIFDataProjectForm;
//---------------------------------------------------------------------------

using namespace dsl;

//---------------------------------------------------------------------------
__fastcall TCreateATIFDataProjectForm::TCreateATIFDataProjectForm(TComponent* Owner)
	: TForm(Owner)
{
    try
    {
    }
    catch(...)
    {
        Log(lError) << "...";
    }
}

string TCreateATIFDataProjectForm::getDataRootFolderLocation()
{
    return DataRootFolderE->getValue();
}

//---------------------------------------------------------------------------
void __fastcall TCreateATIFDataProjectForm::FormCloseQuery(TObject *Sender,
          bool &CanClose)
{
    if(this->ModalResult == mrOk)
    {
    	if(!folderExists(DataRootFolderE->getValue()))
        {
            MessageDlg("Select a valid folder!", mtInformation, TMsgDlgButtons() << mbOK, 0);
            CanClose = false;
        }
    }
}


//---------------------------------------------------------------------------
void __fastcall TCreateATIFDataProjectForm::BrowseForDataOutputPathBtnClick(TObject *Sender)
{
    TButton* btn = dynamic_cast<TButton*>(Sender);

    if(btn == BrowseForDataOutputPathBtn)
    {
        //Browse for folder
        string res = browseForFolder(DataRootFolderE->getValue());
        if(folderExists(res))
        {
            DataRootFolderE->setValue(res);
        }
        else
        {
            Log(lWarning) << "Path was not set..!";
        }
    }
}


