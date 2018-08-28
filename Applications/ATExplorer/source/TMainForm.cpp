#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslVCLUtils.h"
#include "atATExplorerProject.h"
#include "dslLogger.h"
#include "TATESettingsForm.h"
#include "ateAppUtilities.h"
#include "atRenderProject.h"
#include "TRenderProjectFrame.h"
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

        Project* parent = p->getParent();
        if(!parent)
        {
            parent = p;
        }
        else
        {
            while(parent != NULL)
            {
                if(parent->getParent())
                {
                    parent = parent->getParent();
                }
                else
                {
                    break;
                }
            }
        }

	    //user may cancel the request
        if(parent->isModified())
        {
            if(saveProject(parent) == mrCancel)
            {
                return;
            }
        }

	    gAU.LastOpenedProject = mPV.closeProject(parent);
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

//---------------------------------------------------------------------------
void __fastcall TMainForm::ProjTreeViewPopupPopup(TObject *Sender)
{
//    //We gotta filter actions depending on what item is selected in the tree
//    Project* p = mPV.getParentForSelectedProject();
//    if(p)
//    {
//        //Hide close action
//        CloseProjectA->Visible = false;
//    }
//    else
//    {
//        CloseProjectA->Visible = true;
//    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ProjectTViewContextPopup(TObject *Sender, TPoint &MousePos,
          bool &Handled)
{
	TTreeNode* node = ProjectTView->GetNodeAt(MousePos.X, MousePos.Y);
	if(node)
    {
    	Handled = false;

        //Check what item is held by the treeview, and modify popup depending on what
        ATExplorerProject* ate = (ATExplorerProject*) node->Data;
        if(dynamic_cast<RenderProject*>(ate))
        {
            AddRenderProject->Enabled = false;
        }
        else
        {
            AddRenderProject->Enabled = true;
        }
    }
    else
    {
    	Handled = true;
    }

    if(ProjectTView->Items->GetFirstNode() == NULL)
    {
    	Handled = true;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ProjectTViewDblClick(TObject *Sender)
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
        Log(lDebug) << "User double clicked: " << p->getProjectName();
        createProjectView(p);
    }
	mPV.selectProject(p);
}

bool TMainForm::createProjectView(Project* p)
{
    RenderProject* rp = dynamic_cast<RenderProject*>(p);
    //Check what kind of project we are to create a view for
    if(rp)
    {
        //Creat a renderproject view
        Log(lInfo) << "Showing a Render ProjectView";
        //Create a new tab page
        TTabSheet* s = new TTabSheet(MainPC);
        s->PageControl = MainPC;
        s->Caption = p->getProjectName().c_str();
        TRenderProjectFrame* f = new TRenderProjectFrame(rp, this);
        f->Parent = s;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::MainPCContextPopup(TObject *Sender, TPoint &MousePos,
          bool &Handled)
{
	//Check current page
    if(MainPC->PageCount < 1)
    {

    }
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::Close3Click(TObject *Sender)
{
    //Close current Page
    TTabSheet* s = MainPC->ActivePage;
    if(s)
    {

        delete s;
    }
}


