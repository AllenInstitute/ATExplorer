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
	    //Get collections for current users
        StringList c = gATExplorer.RenderClient.PointMatchAPI.getPointMatchCollectionNamesForOwner(owner);
        populateListBox(c, PMCollections);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ApplicationEvents1Exception(TObject *Sender, Exception *E)
{
    Log(lError) << "There was an exception: " << stdstr(E->Message);
}


