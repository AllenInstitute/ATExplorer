#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"

using namespace dsl;

void addRenderProjectToTreeView(TTreeNode* vcNode, RenderProject* rp, TTreeView* tv);

bool addVCProjectToTreeView(VolumeCreatorProject* mVCProject, TTreeView* tv)
{
	TTreeNode* vcn = tv->Items->AddObject(NULL, mVCProject->getProjectName().c_str(), (void*) mVCProject);
    vcn->EditText();

    for(int i = 1; i < mVCProject->getNumberOfChilds() + 1; i++)
    {
    	RenderProject* rp = dynamic_cast<RenderProject*>(mVCProject->getChild(i)) ;
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

VolumeCreatorProject* TMainForm::getCurrentVCProject()
{
	return mProjectManager.getCurrentProject();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::NewProjectAExecute(TObject *Sender)
{
	mProjectManager.createNewProject();
	mProjectManager.selectLast();
//    mCurrentVCProject = createNewProject();
//    ProjectTView->Items->AddObject(NULL, mCurrentVCProject->getProjectName().c_str(), (void*) mCurrentVCProject);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::AddRenderProjectExecute(TObject *Sender)
{
    TTreeNode* vcNode = ProjectTView->Selected;
	VolumeCreatorProject* vcp = (VolumeCreatorProject*) vcNode->Data;

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

VolumeCreatorProject* __fastcall TMainForm::createNewProject()
{
	//Check how many main nodes
    int nrOfVCPs = mVCProjects.size();

	string pName = "VC Project " + dsl::toString(nrOfVCPs);
	VolumeCreatorProject* vcp = new VolumeCreatorProject(pName);
    mVCProjects.push_back(vcp);

    Log(lInfo) << "Created a new VolumeCreator project";
    return vcp;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ProjectStatusTimerTimer(TObject *Sender)
{
	if(getCurrentVCProject() && getCurrentVCProject()->isModified())
    {
       	SaveProjectA->Enabled = true;
    }
    else
    {
		SaveProjectA->Enabled = false;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FileOpen1Accept(TObject *Sender)
{
    string f(stdstr(FileOpen1->Dialog->FileName));
    VolumeCreatorProject* p = getCurrentVCProject();
    if(p && p->isOpen())
    {
		if(closeProject() == mrOk)
        {
        	p->close();
        }
    }

    if(!p)
	{
		p = createNewProject();
    }

	if(p->loadFromFile(f))
    {
	    ProjFileLbl->Caption = string("Project File: " + f).c_str();
    	Log(lInfo) << "Loaded project file: "<<f;
        p->open();
    }

    addVCProjectToTreeView(p, ProjectTView);
}

//---------------------------------------------------------------------------
int __fastcall TMainForm::closeProject()
{
	if(saveProject() == mrOk)
    {
	    VolumeCreatorProject* p = getCurrentVCProject();
        p->close();
        Log(lInfo) << "Closed project: "<<p->getFileName();
   	    ProjFileLbl->Caption = string("Project File: None").c_str();
        delete p;
        p = NULL;
        return mrOk;
    }
    else
    {
    	return mrCancel;
    }
}

int __fastcall TMainForm::saveProjectAs()
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
	    VolumeCreatorProject* p = getCurrentVCProject();
        p->setFileName(fName);
        p->save();
        Log(lInfo) << "Saved project: "<<p->getFileName();
	    ProjFileLbl->Caption = string("Project File: " + fName).c_str();
        return mrOk;
    }
    else
    {
        return mrCancel;
    }
}

int __fastcall TMainForm::saveProject()
{
	//If project don't have an assigned filename, open filesavefile dialog
    VolumeCreatorProject* p = getCurrentVCProject();
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
    }
    else if(p)
    {
		p->save();
        Log(lInfo) << "Saved project: "<<p->getFileName();
        return mrOk;
    }
	return mrOk;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::CloseProjectAExecute(TObject *Sender)
{
	if(closeProject() == mrOk)
    {
        if(ProjectTView->Selected)
        {
			ProjectTView->Items->Delete(ProjectTView->Selected);
        }
    }
}

void __fastcall TMainForm::CloseProjectAUpdate(TObject *Sender)
{
   	CloseProjectA->Enabled = getCurrentVCProject() ? true : false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveProjectAsAUpdate(TObject *Sender)
{
	SaveProjectAsA->Enabled = getCurrentVCProject() ? true : false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveProjectAUpdate(TObject *Sender)
{
    VolumeCreatorProject* p = getCurrentVCProject();
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
        	VolumeCreatorProject* vcp = (VolumeCreatorProject*) node->Data;
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


