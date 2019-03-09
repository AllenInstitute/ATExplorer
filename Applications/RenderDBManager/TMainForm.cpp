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

void setListSelectionAfterDeletion(int oldIndex, TCustomListControl* l);
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
//	mRenderServiceParameters.setHost("atbigdawg");
	mRenderServiceParameters.setHost("localhost");
    mRenderServiceParameters.setMaxTilesToRender(250);
    mRenderServiceParameters.setPortNr(80);
    gATExplorer.appendRenderService(&mRenderServiceParameters);
    gATExplorer.RenderClient.setRenderServiceParameters(&mRenderServiceParameters);

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

void __fastcall TMainForm::PopulateRPOwnersExecute(TObject *Sender)
{
	StringList owners = gATExplorer.RenderClient.StackDataAPI.getOwners();
    populateDropDown(owners, RPOwnersCB);

    //Select first one..
    if(owners.count())
    {
	    RPOwnersCB->ItemIndex = 0;
		PopulateRPProjectsForOwnerAExecute(NULL);
    }
}

void __fastcall TMainForm::PopulateRPProjectsForOwnerAExecute(TObject *Sender)
{
	if(RPOwnersCB->ItemIndex == -1)
    {
        return;
    }
    string owner = stdstr(RPOwnersCB->Items->Strings[RPOwnersCB->ItemIndex]);

    RenderProjectsLB->Clear();
    StringList projects = gATExplorer.RenderClient.StackDataAPI.getProjectsForOwner(owner);

    //Stor the collections in the list box items object property
    for(int i = 0; i < projects.count(); i++)
    {
        RenderProjectsLB->Items->Add(projects[i].c_str());
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::PopulatePointMatchOwnersAExecute(TObject *Sender)
{
	StringList owners = gATExplorer.RenderClient.PointMatchAPI.getPointMatchCollectionOwners();
    populateDropDown(owners, PMOwnersCB);

    //Select first one..
    if(owners.count())
    {
	    PMOwnersCB->ItemIndex = 0;
		PopulateCollectionsForOwnerAExecute(NULL);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::PMOwnersCBCloseUp(TObject *Sender)
{
    //Populate collections
    if(PMOwnersCB->ItemIndex != -1)
    {
    	PopulateCollectionsForOwnerAExecute(NULL);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::PopulateCollectionsForOwnerAExecute(TObject *Sender)
{
	if(PMOwnersCB->ItemIndex != -1)
    {
    	string owner = stdstr(PMOwnersCB->Items->Strings[PMOwnersCB->ItemIndex]);

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
            setListSelectionAfterDeletion(idx, PMCollections);
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::DeleteItem(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key != VK_DELETE)
    {
        return;
    }

    if(Sender == RenderStacksLB)
    {
	    DeleteStackAExecute(NULL);
    }
    else if(Sender == RenderProjectsLB)
    {
		DeleteRenderProjectAExecute(NULL);
    }
    else if(Sender == PMCollections)
    {
        int res = MessageDlg("Delete Collection: ", mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0);
        if(res = mrOk)
        {
	        DeletePMCAClick(NULL);
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::DeleteRenderProjectAExecute(TObject *Sender)
{
    int idx = RenderProjectsLB->ItemIndex;
	if(idx == -1)
    {
        return ;
    }
    string o = stdstr(RPOwnersCB->Text);
    string p  = stdstr(RenderProjectsLB->Items->Strings[idx]);

    gATExplorer.RenderClient.StackDataAPI.deleteProject(o, p);
    RenderProjectsLB->Items->Delete(idx);
    setListSelectionAfterDeletion(idx, RenderProjectsLB);
    RenderStacksLB->Clear();

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::RenderProjectsLBClick(TObject *Sender)
{
    //Populate stacks
	PopulateRenderStacksForProjectAExecute(NULL);
}

void __fastcall TMainForm::PopulateRenderStacksForProjectAExecute(TObject *Sender)
{
    //Get stacks
    int idx = RenderProjectsLB->ItemIndex;
    if(idx != -1)
    {
        string projName = stdstr(RenderProjectsLB->Items->Strings[idx]);
        string o = stdstr(RPOwnersCB->Text);
	    string p  = stdstr(RenderProjectsLB->Items->Strings[idx]);
		StringList stacks = gATExplorer.RenderClient.StackDataAPI.getStacksForProject(o, p);
        populateCheckListBox(stacks, RenderStacksLB);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::DeleteStackAExecute(TObject *Sender)
{
    //
    int idx = RenderProjectsLB->ItemIndex;
    if(idx == -1)
    {
        return;
    }

    string o = stdstr(RPOwnersCB->Text);
    string p = stdstr(RenderProjectsLB->Items->Strings[idx]);

    int stackID = RenderStacksLB->ItemIndex;
    if(stackID != -1)
    {
        string stack = stdstr(RenderStacksLB->Items->Strings[stackID]);
        bool res = gATExplorer.RenderClient.StackDataAPI.deleteStack(o, p, stack);

        if(res)
        {
            Log(lInfo) << "The stack was deleted";
            RenderStacksLB->Items->Delete(stackID);
            setListSelectionAfterDeletion(stackID, RenderStacksLB);
        }
        else
        {
            Log(lInfo) << "The stack was NOT deleted";
        }
    }
}

void setListSelectionAfterDeletion(int oldIndex, TCustomListControl* list)
{
    if(!list)
    {
        return;
    }

    if(oldIndex > 0)
    {
        list->ItemIndex = oldIndex - 1;
    }
    else
    {
        if(list->GetCount())
        {
            list->ItemIndex = 0;
        }
    }
}
