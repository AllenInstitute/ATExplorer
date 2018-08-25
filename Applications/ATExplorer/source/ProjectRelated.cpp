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
using namespace at;

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
//		addRenderProjectToTreeView(vcNode, rp, ProjectTView);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::NewProjectAExecute(TObject *Sender)
{
	mPV.createNewATExplorerProject();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FileOpen1Accept(TObject *Sender)
{
    string f(stdstr(FileOpen1->Dialog->FileName));

	ATExplorerProject* p = mPV.createNewATExplorerProject();


	if(p->loadXMLFromFile(f))
    {
//	    ProjFileLbl->Caption = string("Project File: " + f).c_str();
    	Log(lInfo) << "Loaded project file: "<<f;
        p->open();
        mPV.updateView(p);
    }
}

//---------------------------------------------------------------------------
int TMainForm::saveProject(Project* p)
{
	//If project don't have an assigned filename, open filesavefile dialog
    if(p && p->isNeverSaved())
    {
    	int res = MessageDlg("Save Project?", mtConfirmation, TMsgDlgButtons() << mbYes<<mbNo<<mbCancel, 0);
        if(res == mrYes)
        {
        	return saveProjectAs(p);
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

int TMainForm::saveProjectAs(Project* p)
{
    //Set filename and filePath
    SaveDialog1->Execute();
    if(SaveDialog1->FileName.Length())
    {
        string fName = stdstr(SaveDialog1->FileName);
        if(fileExists(fName))
        {
            if(MessageDlg("Overwrite file?", mtWarning, TMsgDlgButtons() << mbCancel << mbYes << mbNo, 0) == mrCancel)
            {
                return mrCancel;
            }
        }
        p->setFileName(fName);
        p->save();
        Log(lInfo) << "Saved project to file: "<<p->getFileName();
        return mrOk;
    }
    return mrCancel;
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


