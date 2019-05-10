#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslVCLUtils.h"
#include "atATExplorerProject.h"
#include "dslLogger.h"
#include "TATESettingsForm.h"
#include "ATExplorerUIProperties.h"
#include "atRenderProject.h"
#include "pointMatches/atPointMatchCollectionProject.h"
#include "atRenderProjectItemView.h"
#include "atATIFDataProjectItemView.h"
#include "atATIFDataProject.h"
#include <gdiplus.h>
#include "TCreateATIFDataProjectForm.h"
#include "dslFileUtils.h"
#include "TSelectRenderProjectParametersForm.h"
#include "TSelectPointmatchCollectionProjectForm.h"
#include "atATExplorer.h"
#include "TAboutATExplorerForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTLogMemoFrame"
#pragma resource "*.dfm"
TMainForm *MainForm;

using namespace dsl;
using namespace std;
using namespace at;
using namespace Poco;

Gdiplus::GdiplusStartupInput	                gdiplusStartupInput;
ULONG_PTR  			         	                gdiplusToken;

extern ATExplorer gATExplorer;
extern ATExplorerUIProperties gUIProperties;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TRegistryForm(gUIProperties.AppRegistryRoot, "MainForm", Owner),
     mIsStyleMenuPopulated(false),
     mTreeItemObservers(*MainPC, gATExplorer),
     mPTreeView(*ProjectTView, mTreeItemObservers)
{
    Application->ShowHint = true;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    //Setup some UI properties
	BottomPanel->Height 		= gUIProperties.BottomPanelHeight;
    ProjectManagerPanel->Width 	= gUIProperties.ProjectPanelWidth == 0 ? 100 : gUIProperties.ProjectPanelWidth; //Gotta be at least 100px on startup
    gATExplorer.Cache.setBasePath(gUIProperties.LocalCacheFolder);
    //Populate "recent" files, projects

    string projectFile(gUIProperties.LastOpenedProject.getValue());

	if(projectFile.size() && fileExists(projectFile))
    {
        Log(lInfo) << "Last opened project: " << projectFile;
		TMenuItem *Item = new TMenuItem(ReopenMenu);
        Item->Caption = gUIProperties.LastOpenedProject.getValue().c_str();
        FileOpen1->Dialog->FileName = gUIProperties.LastOpenedProject.getValue().c_str();
        Item->OnClick = FileOpen1Accept;
        ReopenMenu->Add(Item);
        ReopenMenu->Enabled = true;
    }
}

__fastcall TMainForm::~TMainForm()
{
   	Gdiplus::GdiplusShutdown(gdiplusToken);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenSettingsAExecute(TObject *Sender)
{
    //open Settings form
    shared_ptr<TATESettingsForm> settingsForm(new TATESettingsForm(gATExplorer, this));
    PropertiesSP sec = gUIProperties.getFirstSection();

    while(sec)
    {
        settingsForm->append(sec);
        sec = gUIProperties.getNextSection();
    }

    if(settingsForm->ShowModal() == mrOk)
    {
        //save ini file
        gATExplorer.writeProperties();
        gUIProperties.saveIniFile();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ProjectTViewClick(TObject *Sender)
{
	//Get current node from the treeview
	mPTreeView.handleNodeClick(ProjectTView->Selected, false);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ProjectTViewDblClick(TObject *Sender)
{
	//Get current node from the treeview
    mPTreeView.handleNodeClick(ProjectTView->Selected, true);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::CloseProjectAExecute(TObject *Sender)
{
	TTreeNode* item = ProjectTView->Selected;
    if(item && item->Data)
    {
		ATExplorerProject* p = (ATExplorerProject*) item->Data;

        Project* parent = p->getProjectRoot();

	    //user m	ay cancel the request
        if(parent->isModified())
        {
            if(saveProject(parent) == mrCancel)
            {
                return;
            }
        }

//        //Make mTreeItemObservers an observer too, and the following code becomes reduntant..
//        for(int i = 0; i < parent->getNumberOfChilds(); i++)
//        {
//	        mTreeItemObservers.removeViewForSubject(parent->getChild(i));
//        }

	    gUIProperties.LastOpenedProject = mPTreeView.closeProject(parent);
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
//    Project* p = mPTreeView.getRootForSelectedProject();
//	SaveProjectA->Enabled = true;//(p && p->isModified()) ? true : false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveProjectAExecute(TObject *Sender)
{
    Project* p = mPTreeView.getRootForSelectedProject();
	saveProject(p);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ATIFDataPopupPopup(TObject *Sender)
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
    TPoint popupCoord = ProjectTView->ClientToScreen(MousePos);
	if(node)
    {
    	Handled = false;

        //Check what item is held by the treeview, and modify popup depending on what
        ExplorerObject* eo = (ExplorerObject*) node->Data;
        if(!eo)
        {
            return;
        }
        else if(dynamic_cast<RenderProject*>(eo))
        {
            RenderProjectPopup->Popup(popupCoord.X, popupCoord.Y);
        }
        else if(dynamic_cast<ATIFDataProject*>(eo))
        {
            ATIFDataPopup->Popup(popupCoord.X, popupCoord.Y);
        }
        else if(dynamic_cast<PointMatchCollectionProject*>(eo))
        {
            PointMatchCollectionPopup->Popup(popupCoord.X, popupCoord.Y);
        }

        else if(dynamic_cast<ATExplorerProject*>(eo))
        {
            ExplorerProjectPopup->Popup(popupCoord.X, popupCoord.Y);
        }
        Handled = true;
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

void TMainForm::selectTabForTreeItem(Project* p)
{
    RenderProject* rp = dynamic_cast<RenderProject*>(p);
    if(!rp)
    {
        return;
    }

    for(int i = 0; i < MainPC->PageCount; i++)
    {
        TTabSheet* sh = MainPC->Pages[i];
        if(sh && compareStrings(stdstr(sh->Caption), rp->getProjectName()))
        {
			MainPC->TabIndex = i;
            return;
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::MainPCContextPopup(TObject *Sender, TPoint &MousePos,
          bool &Handled)
{
	//Check current page
    if(MainPC->PageCount < 1)
    {    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::Close3Click(TObject *Sender)
{
    //Close current Page (sheet)
    TTabSheet* ts = MainPC->ActivePage;
    if(ts)
    {
        mTreeItemObservers.removeViewOnTabSheet(ts);
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
    mPTreeView.removeSubProject(p);

    //Delete project here.. if we were to use shared pointers
    //this will be unescarry..
    delete p;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::RenameClick(TObject *Sender)
{
	ProjectTView->ReadOnly = false;
	TTreeNode* n = mPTreeView.getSelectedNode();
    n->EditText();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenProjectOptionsAExecute(TObject *Sender)
{
    MessageDlg("", mtInformation, TMsgDlgButtons() << mbOK, 0);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::AddATIFDataActionExecute(TObject *Sender)
{
    TTreeNode* atNode = ProjectTView->Selected;
    if(!atNode)
    {
        return;
    }
	ATExplorerProject* parent = (ATExplorerProject*) atNode->Data;

    if(parent)
    {
        //If we can cast this to a ATIFDataProject, add to parent
        if(dynamic_cast<ATIFDataProject*>(parent))
        {
            parent = dynamic_cast<ATExplorerProject*>(parent->getParent());
        }
        //Open dialog to capture render parameters
		unique_ptr<TCreateATIFDataProjectForm> f (new TCreateATIFDataProjectForm(this));

        if(f->ShowModal() == mrCancel)
        {
            return;
        }

		ATIFDataProject* dataProject (new ATIFDataProject("", f->getDataRootFolderLocation()));

	    //Check how many renderproject childs
        int nrOfChilds = parent->getNumberOfChilds();
        dataProject->setProjectName(getLastFolderInPath(dataProject->getDataRootFolder()));

        //Make sure that no project with the same name exists in the view
        if(parent->hasChild(dataProject->getProjectName()))
        {
            MessageDlg("This data is already added to the current project!", mtWarning, TMsgDlgButtons() << mbOK, 0);
            return;
        }

        parent->addChild(dataProject);
    	parent->setModified();

		mPTreeView.addProjectToTreeView(parent, dataProject);
        mPTreeView.createTreeViewNodes(dataProject);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::AddRenderProjectExecute(TObject *Sender)
{
    TTreeNode* atNode = ProjectTView->Selected;
    if(!atNode)
    {
        return;
    }
	ATExplorerProject* parent = (ATExplorerProject*) atNode->Data;

    if(parent)
    {
        //If we can cast this to a RenderProject, add to parent
        if(dynamic_cast<RenderProject*>(parent))
        {
            parent = dynamic_cast<ATExplorerProject*>(parent->getParent());
        }
        //Open dialog to capture render parameters
		unique_ptr<TSelectRenderProjectParametersForm> f (new TSelectRenderProjectParametersForm(gATExplorer, this));

        if(f->ShowModal() == mrCancel)
        {
            return;
        }

        RenderServiceParameters rs(f->getRenderService());

		//Create a render project and associate with current ATE project
        //Use shared pointer later on
		RenderProject* rp (new RenderProject("", f->getRenderOwner(), f->getRenderProject(), ""));
        rp->setRenderServiceParameters(rs);
        rp->assignLocalCacheRootFolder(f->getOutputFolderLocation());

	    //Check how many renderproject childs
        int nrOfChilds = parent->getNumberOfChilds();

        rp->setProjectName(rp->getRenderProjectName());
    	parent->addChild(rp);
    	parent->setModified();
		mPTreeView.addProjectToTreeView(parent, rp);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenViewAExecute(TObject *Sender)
{
    //Get selected node
	mPTreeView.handleNodeClick(mPTreeView.getSelectedNode(), true);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenAboutAExecute(TObject *Sender)
{
	unique_ptr<TAboutATExplorer> a (new TAboutATExplorer(this));
	a->ShowModal();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::AddPointMatchCollectionAExecute(TObject *Sender)
{
    TTreeNode* atNode = ProjectTView->Selected;
	ATExplorerProject* parent = (ATExplorerProject*) atNode->Data;

    if(parent)
    {
        //If we can cast this to a RenderProject, add to parent
        if(dynamic_cast<RenderProject*>(parent))
        {
            parent = dynamic_cast<ATExplorerProject*>(parent->getParent());
        }
        //Open dialog to capture render parameters
		unique_ptr<TSelectPointmatchCollectionProjectForm> f (new TSelectPointmatchCollectionProjectForm(gATExplorer, this));

        if(f->ShowModal() == mrCancel)
        {
            return;
        }

        RenderServiceParameters rs(f->getRenderService());

		//Create a render project and associate with current ATE project
        //Use shared pointer later on
        if(f->getPointMatchCollection())
        {
	        PointMatchCollection pmc = *(f->getPointMatchCollection());

			PointMatchCollectionProject* pmp = new PointMatchCollectionProject("", pmc);
            //Check how many renderproject childs
            int nrOfChilds = parent->getNumberOfChilds();

            pmp->setProjectName("Pointmatch Collection: " + dsl::toString(nrOfChilds + 1));
            parent->addChild(pmp);
            parent->setModified();
            mPTreeView.addProjectToTreeView(parent, pmp);
        }
    }

}


