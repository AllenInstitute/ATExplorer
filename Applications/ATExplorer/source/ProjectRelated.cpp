#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "dslFileUtils.h"
#include "atATExplorerProject.h"
#include "atRenderProject.h"
//---------------------------------------------------------------------------
using namespace dsl;

void addRenderProjectToTreeView(TTreeNode* vcNode, RenderProject* rp, TTreeView* tv);

bool addVCProjectToTreeView(ATExplorerProject* project, TTreeView* tv)
{
	TTreeNode* vcn = tv->Items->AddObject(NULL, project->getProjectName().c_str(), (void*) project);
    vcn->EditText();

    for(int i = 1; i < project->getNumberOfChilds() + 1; i++)
    {
    	RenderProject* rp = dynamic_cast<RenderProject*>(project->getChild(i)) ;
    	if(rp)
        {
	    	addRenderProjectToTreeView(vcn, rp, tv);
        }
    }
    return true;
}

void addRenderProjectToTreeView(TTreeNode* vcNode, RenderProject* rp, TTreeView* tv)
{
    if(!vcNode)
    {
    	Log(lError) <<"Node is NULL";
        return;
    }
    int nrOfChilds(0);

	TTreeNode* n = tv->Items->AddChildObject(vcNode, "", (void*) rp);
    n->Text = rp->getProjectName().c_str();
	tv->Items->GetFirstNode()->Expand(true);
    tv->Select(n);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ProjectTViewEditing(TObject *Sender, TTreeNode *Node,
          bool &AllowEdit)
{
	AllowEdit = true;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ProjectTViewEdited(TObject *Sender, TTreeNode *Node,
          UnicodeString &S)
{
	//Update underlying object with new valuse..
    ATExplorerProject* vcp = (ATExplorerProject*) Node->Data;
    if(vcp)
    {
    	vcp->setProjectName(stdstr(S));
        vcp->setModified();
		SaveProjectA->Update();
    }
}

void __fastcall TMainForm::EditViewNodeExecute(TObject *Sender)
{
	TTreeNode* item = ProjectTView->Selected;
    if(item)
    {
    	item->EditText();
    }
}

ATExplorerProject* TMainForm::getCurrentProject()
{
	return mPM.getCurrentProject();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::NewProjectAExecute(TObject *Sender)
{
	mPM.createNewProject();
	mPM.selectLast();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::AddRenderProjectExecute(TObject *Sender)
{
    TTreeNode* vcNode = ProjectTView->Selected;
	ATExplorerProject* vcp = (ATExplorerProject*) vcNode->Data;

    if(vcp)
    {
		//Create a render project and associate with current VC project
	  	RenderProject* rp = new RenderProject("", "", "" , "");

	    //Check how many renderproject childs
        int nrOfChilds = vcp->getNumberOfChilds();
        rp->setProjectName("Render project " + dsl::toString(nrOfChilds + 1));
    	vcp->addChild(rp);
    	vcp->setModified();
		addRenderProjectToTreeView(vcNode, rp, ProjectTView);
    }
}

ATExplorerProject* TMainForm::createNewProject()
{
	//Check how many main nodes
	string pName = "AT Project " + dsl::toString(mPM.projectCount());
    return mPM.createNewProject(pName);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ProjectStatusTimerTimer(TObject *Sender)
{
//	if(getCurrentVCProject() && getCurrentVCProject()->isModified())
//    {
//       	SaveProjectA->Enabled = true;
//    }
//    else
//    {
//		SaveProjectA->Enabled = false;
//    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FileOpen1Accept(TObject *Sender)
{
//    string f(stdstr(FileOpen1->Dialog->FileName));
//    ATExplorerProject* p = getCurrentVCProject();
//    if(p && p->isOpen())
//    {
//		if(closeProject() == mrOk)
//        {
//        	p->close();
//        }
//    }
//
//    if(!p)
//	{
//		p = createNewProject();
//    }
//
//	if(p->loadXMLFromFile(f))
//    {
////	    ProjFileLbl->Caption = string("Project File: " + f).c_str();
//    	Log(lInfo) << "Loaded project file: "<<f;
//        p->open();
//    }
//
//    addVCProjectToTreeView(p, ProjectTView);
}

//---------------------------------------------------------------------------
int __fastcall TMainForm::saveProject()
{
	//If project don't have an assigned filename, open filesavefile dialog
    ATExplorerProject* p = mPM.getCurrentProject();
    if(p && p->isNeverSaved())
    {
    	int res = MessageDlg("Save Project?", mtConfirmation, TMsgDlgButtons() << mbYes<<mbNo<<mbCancel, 0);
        if(res == mrYes)
        {
        	return saveProjectAs();
        }
        else if(res == mrCancel)
        {
        	return mrCancel;
        }
        else
        {
            return mrNo;
        }
    }
    else if(p)
    {
		p->save();
        Log(lInfo) << "Saved project: "<<p->getFileName();
    }
    return mrOk;
}


bool __fastcall TMainForm::saveProjectAs(ATExplorerProject* p)
{
    //Set filename and filePath
    SaveDialog1->Execute();
    if(SaveDialog1->FileName.Length())
    {
        string fName = stdstr(SaveDialog1->FileName);
        if(fileExists(fName))
        {
            if(MessageDlg("Overwrite file?", mtWarning, TMsgDlgButtons() << mbYes<<mbNo, 0) == mrCancel)
            {
                return mrCancel;
            }
        }
        p->setFileName(fName);
        p->save();
        Log(lInfo) << "Saved project as: "<<p->getFileName();
        return true;
    }
    return false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::CloseProjectAExecute(TObject *Sender)
{
	TTreeNode* item = ProjectTView->Selected;
    if(item && item->Data)
    {
		ATExplorerProject* p = (ATExplorerProject*) item->Data;

	    //user may cancel the request
	    mPM.closeProject(p);
    }
}

void __fastcall TMainForm::CloseProjectAUpdate(TObject *Sender)
{
   	CloseProjectA->Enabled = mPM.getCurrentProject() ? true : false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveProjectAsAUpdate(TObject *Sender)
{
	SaveProjectAsA->Enabled = mPM.getCurrentProject() ? true : false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveProjectAUpdate(TObject *Sender)
{
    ATExplorerProject* p = mPM.getCurrentProject();
	SaveProjectA->Enabled = (p && p->isModified()) ? true : false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveProjectAExecute(TObject *Sender)
{
	saveProject();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveProjectAsAExecute(TObject *Sender)
{
	saveProjectAs();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ProjectTViewContextPopup(TObject *Sender, TPoint &MousePos,
          bool &Handled)
{
	if(ProjectTView->GetNodeAt(MousePos.X, MousePos.Y))// == ProjectTView->TopItem)
    {
    	Handled = false;
        //Check what item is held by the treeview
		TTreeNode* node = ProjectTView->GetNodeAt(MousePos.X, MousePos.Y);
        if(node)
        {
        	ATExplorerProject* vcp = (ATExplorerProject*) node->Data;
            if(dynamic_cast<RenderProject*>(vcp))
            {
		        AddRenderProject->Enabled = false;
            }
            else
            {
	            AddRenderProject->Enabled = true;
            }
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


