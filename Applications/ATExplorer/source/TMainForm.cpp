#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslVCLUtils.h"
#include "atATExplorerProject.h"
#include "dslLogger.h"
#include "TATESettingsForm.h"
#include "ateAppUtilities.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTLogMemoFrame"
#pragma resource "*.dfm"
TMainForm *MainForm;

using namespace dsl;
using namespace std;
using namespace at;
using namespace Poco;

extern at::AppUtilities gAU;

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TRegistryForm(gAU.AppRegistryRoot, "MainForm", Owner),
    mIsStyleMenuPopulated(false),
     mPV(ProjectTView)
{
    setupAndReadIniParameters();
    Application->ShowHint = true;
}

__fastcall TMainForm::~TMainForm()
{}

//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenSettingsAExecute(TObject *Sender)
{
    //open Settings form
    shared_ptr<TATESettingsForm> s = shared_ptr<TATESettingsForm> (new TATESettingsForm(this));

    //The settings form will bring all properties into Edit mode
    s->append(gAU.GeneralProperties);
    s->append(gAU.ServerProperties);

    int r = s->ShowModal();
    if(r == mrOk)
    {
        //Update values
        Log(lInfo) << "Cache folder is now: " << gAU.LocalCacheFolder.getValue();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ProjectTViewClick(TObject *Sender)
{
	//Get current node from the treeview
	TTreeNode* item = ProjectTView->Selected;
    if(!item)
    {
        return;
    }
    Project* p = (Project*) item->Data;
    if(p)
    {
        Log(lDebug) << "User clicked: " << p->getProjectName();
    }
	mPV.selectProject(p);
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::CloseProjectAExecute(TObject *Sender)
{
	TTreeNode* item = ProjectTView->Selected;
    if(item && item->Data)
    {
		ATExplorerProject* p = (ATExplorerProject*) item->Data;

	    //user may cancel the request
        if(p->isModified())
        {
            if(saveProject(p) == mrCancel)
            {
                return;
            }
        }

	    mPV.closeProject(p);
    }
}

void __fastcall TMainForm::CloseProjectAUpdate(TObject *Sender)
{
   	CloseProjectA->Enabled = mPV.getSelectedProject() ? true : false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveProjectAsAExecute(TObject *Sender)
{
	Project* p = mPV.getCurrent();
	saveProjectAs(p);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveProjectAsAUpdate(TObject *Sender)
{
	SaveProjectAsA->Enabled = mPV.getSelectedProject() ? true : false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveProjectAUpdate(TObject *Sender)
{
    Project* p = mPV.getSelectedProject();
	SaveProjectA->Enabled = (p && p->isModified()) ? true : false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveProjectAExecute(TObject *Sender)
{
    Project* p = mPV.getSelectedProject();
	saveProject(p);
}

