#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "UIProperties.h"
#include "atATExplorer.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTLogMemoFrame"
#pragma link "dslTLogFileReader"
#pragma resource "*.dfm"
TMainForm *MainForm;

using namespace at;
using namespace dsl;
extern ATExplorer gATExplorer;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	:
    TRegistryForm(gUIProperties.AppRegistryRoot, "MainForm", Owner)
{
    //Setup some UI properties
	BottomPanel->Height 		= gUIProperties.BottomPanelHeight;
    LogMemoFrame1->init();

    //Create a renderservice
    mRenderServiceParameters.setName("Test");
	mRenderServiceParameters.setHost("localhost");
    mRenderServiceParameters.setMaxTilesToRender(250);
    gATExplorer.appendRenderService(&mRenderServiceParameters);
}

__fastcall TMainForm::~TMainForm()
{
//	gATExplorer.removeRenderService("Test");
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
	{
 	    Close();
     }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	gUIProperties.BottomPanelHeight = BottomPanel->Height;
	gUIProperties.GeneralProperties->write();

    gATExplorer.writeProperties();

	//Write to file
	gUIProperties.getIniFile().save();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::PopulateOwnersAExecute(TObject *Sender)
{
	StringList owners = gATExplorer.RenderClient.PointMatchAPI.getPointMatchCollectionOwners();
    populateDropDown(owners, OwnersCB);

    //Select first one..
    if(owners.count())
    {
	    OwnersCB->ItemIndex = 0;
		PopulateCollectionsForOwnerAExecute(NULL);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::OwnersCBCloseUp(TObject *Sender)
{
    //Populate collections
    if(OwnersCB->ItemIndex != -1)
    {
    	PopulateCollectionsForOwnerAExecute(NULL);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::PopulateCollectionsForOwnerAExecute(TObject *Sender)
{
	if(OwnersCB->ItemIndex != -1)
    {
    	string owner = stdstr(OwnersCB->Items->Strings[OwnersCB->ItemIndex]);

        PMCollections->Clear();
        const PointMatchCollections& PMCs = gATExplorer.RenderClient.PointMatchAPI.getPointMatchCollectionsForOwner(owner, true);

        //Stor the collections in the list box items object property
        PointMatchCollectionSP pmc = PMCs.getFirst();
        while(pmc)
        {
			PMCollections->Items->InsertObject(0, pmc->getName().c_str(), (TObject*)(pmc.get()));
            pmc = PMCs.getNext();
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ApplicationEvents1Exception(TObject *Sender, Exception *E)
{
    Log(lError) << "There was an exception: " << stdstr(E->Message);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::DeletePMCAClick(TObject *Sender)
{
    //get PMC from Object
    int idx = PMCollections->ItemIndex;
	if(idx != -1)
    {
	    PointMatchCollection* pmc = (PointMatchCollection*) PMCollections->Items->Objects[idx];
        if(pmc)
        {
			gATExplorer.RenderClient.PointMatchAPI.deletePointMatchCollection(pmc);
			PMCollections->Items->Delete(idx);
            if(idx > 0)
            {
				PMCollections->ItemIndex = idx - 1;
            }
            else
            {
                if(PMCollections->Count)
                {
					PMCollections->ItemIndex = 0;
                }
            }
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::PMCollectionsKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_DELETE)
    {
        int res = MessageDlg("Delete Collection: ", mtWarning, TMsgDlgButtons() << mbYes<<mbNo, 0);
        if(res = mrOk)
        {
	        DeletePMCAClick(NULL);
        }
    }
}


