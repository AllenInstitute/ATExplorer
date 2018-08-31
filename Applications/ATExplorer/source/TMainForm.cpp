#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslVCLUtils.h"
#include "atATExplorerProject.h"
#include "dslLogger.h"
#include "TATESettingsForm.h"
#include "ateAppUtilities.h"
#include "atRenderProject.h"
#include "atRenderPRojectView.h"
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
     mPTreeView(ProjectTView)
{
    setupAndReadIniParameters();
    Application->ShowHint = true;
}

__fastcall TMainForm::~TMainForm()
{
	mObservers.clear();
}

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
	mPTreeView.selectProject(p);
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

	    gAU.LastOpenedProject = mPTreeView.closeProject(parent);
    }
}

void __fastcall TMainForm::CloseProjectAUpdate(TObject *Sender)
{
   	CloseProjectA->Enabled = mPTreeView.getRootForSelectedProject() ? true : false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveProjectAsAExecute(TObject *Sender)
{
	Project* p = mPTreeView.getCurrent();
	saveProjectAs(p);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveProjectAsAUpdate(TObject *Sender)
{
	SaveProjectAsA->Enabled = mPTreeView.getRootForSelectedProject() ? true : false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveProjectAUpdate(TObject *Sender)
{
    Project* p = mPTreeView.getRootForSelectedProject();
	SaveProjectA->Enabled = (p && p->isModified()) ? true : false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveProjectAExecute(TObject *Sender)
{
    Project* p = mPTreeView.getRootForSelectedProject();
	saveProject(p);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ProjTreeViewPopupPopup(TObject *Sender)
{
//    //We gotta filter actions depending on what item is selected in the tree
//    Project* p = mPTreeView.getParentForSelectedProject();
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
void __fastcall TMainForm::ProjectTViewContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled)
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
	        CloseProjectA->Visible = false;
            RemoveFromProjectA->Visible = true;
        }
        else
        {
            AddRenderProject->Enabled = true;
	        CloseProjectA->Visible = true;
            RemoveFromProjectA->Visible = false;
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
	mPTreeView.selectProject(p);
}

bool TMainForm::createProjectView(Project* p)
{
    RenderProject* rp = dynamic_cast<RenderProject*>(p);
    //Check what kind of project we are to create a view for
    if(rp)
    {
        //Check if there is already a tab with this view.. if so, switch to it
        TTabSheet* sh = mObservers.getTabForProject(rp);
        if(sh)
        {
            MainPC->ActivePage = sh;
            return false;
        }

        //Creat a renderproject view
        Log(lInfo) << "Showing a Render ProjectView";

        //Create a new tab page
        //Views deletes themselves when subjects dies
        RenderProjectView* obs = new RenderProjectView(MainPC, rp);
        mObservers.append(obs);
    }
    return true;
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
    //Close current Page (sheet)
    TTabSheet* ts = MainPC->ActivePage;
    if(ts)
    {
        mObservers.removeViewOnTabSheet(ts);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::RemoveFromProjectAExecute(TObject *Sender)
{
    Project* p = mPTreeView.getSelectedProject();
    if(!p->getParent())
    {
        Log(lWarning) << "You can't remove the root project..";
        return;
    }

    Log(lInfo) << "Removing subProject: " << p->getProjectName();

    //Close any views
    p->notifyObservers(SubjectBeingDestroyed);
    mPTreeView.removeProject(p);
    mObservers.removeViewForProject(p);

    //Delete project here..
    delete p;
}


