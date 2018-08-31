#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "dslFileUtils.h"
#include "atATExplorerProject.h"
#include "atRenderProject.h"
#include "TSelectRenderProjectParametersForm.h"
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
    ATExplorerProject* ate = (ATExplorerProject*) Node->Data;
    if(ate)
    {
    	ate->setProjectName(stdstr(S));
        ate->setModified();
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
		unique_ptr<TSelectRenderProjectParametersForm> f (new TSelectRenderProjectParametersForm(this));

        if(f->ShowModal() == mrCancel)
        {
            return;
        }

        RenderServiceParameters rs(f->getRenderService());

		//Create a render project and associate with current VC project
	  	RenderProject* rp (new RenderProject(rs, "", f->getRenderOwner(), f->getRenderProject()));

	    //Check how many renderproject childs
        int nrOfChilds = parent->getNumberOfChilds();

        rp->setProjectName("Render project " + dsl::toString(nrOfChilds + 1));
    	parent->addChild(rp);
    	parent->setModified();
		mPV.addRenderProjectToView(parent, rp);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::NewProjectAExecute(TObject *Sender)
{
	ATExplorerProject* p = mPV.createNewATExplorerProject();
    mPV.addProjectToView(p);
	ProjectTView->SetFocus();
    mPV.selectProject(p);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FileOpen1Accept(TObject *Sender)
{
    string f(stdstr(FileOpen1->Dialog->FileName));
	ATExplorerProject* p = mPV.createNewATExplorerProject();

	if(p->loadXMLFromFile(f))
    {
    	Log(lInfo) << "Loaded project file: "<<f;
        p->open();
        mPV.updateView(p);
        mPV.expandView(p);
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



