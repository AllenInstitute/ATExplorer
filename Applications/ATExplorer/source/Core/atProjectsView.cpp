#include <vcl.h>
#pragma hdrstop
#include "atProjectsView.h"
#include "atATExplorerProject.h"
#include "atRenderProject.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


namespace at
{

using namespace dsl;

ProjectsView::ProjectsView(TTreeView* tv)
:
mTree(tv)
{}

ProjectsView::~ProjectsView()
{}

Project* ProjectsView::getCurrent()
{
    return mProjects.getCurrent();
}

Project* ProjectsView::getFirst()
{
    return mProjects.getFirst();
}

Project* ProjectsView::getNext()
{
    return mProjects.getNext();
}

bool ProjectsView::selectProject(Project* p)
{
    return mProjects.selectProject(p);
}


TTreeNode* ProjectsView::getItemForProject(Project* p)
{
    TTreeNode* item = mTree->Items->GetFirstNode();

	while (item)
  	{
        if(item->Data == p)
        {
            return item;
        }

		item = item->GetNext();
  	}
    return nullptr;
}

void ProjectsView::updateView(Project* p)
{
	TTreeNode* n (getItemForProject(p));
    if(n)
    {
    	n->Text = vclstr(p->getProjectName());
    }
    else
    {
        Log(lWarning) << "Failed retrieving TreeNode for project: " << p->getProjectName();
    }
}

bool ProjectsView::closeProject(Project* p)
{
    mProjects.remove(p);
    TTreeNode* n = getItemForProject(p);
    n->DeleteChildren();
    n->Delete();
    mProjects.selectFirst();
    return true;
}

int ProjectsView::mProjectCount()
{
    return mProjects.count();
}

ATExplorerProject* ProjectsView::createNewATExplorerProject()
{
    ATExplorerProject* p (new ATExplorerProject);
    p->setProjectName("ATExplorer Project " + dsl::toString(mProjects.count() + 1));
	p->setModified();
    mProjects.append(p);
    TTreeNode* n = addProjectToView(p);
    n->Selected = true;
    return p;
}

TTreeNode* ProjectsView::addProjectToView(Project* project)
{
    ATExplorerProject* p = dynamic_cast<ATExplorerProject*>(project);
    if(!p)
    {
        Log(lError) << "Non Explorer Project in addProjectToView..";
        return false;
    }

    //Store raw pointers in the TreeView
	TTreeNode* n = mTree->Items->AddObject(NULL, project->getProjectName().c_str(), (void*) project);
    n->EditText();

    for(int i = 1; i < p->getNumberOfChilds() + 1; i++)
    {
    	RenderProject* rp = dynamic_cast<RenderProject*>(p->getChild(i)) ;
    	if(rp)
        {
	    	addRenderProjectToView(n, rp);
        }
    }
    return n;
}

Project* ProjectsView::getSelectedProject()
{
    if(mTree->Selected)
    {
        Project* p = (Project*) mTree->Selected->Data;

        if(!p->getParent())
        {
            return p;
        }

        //This may be a RenderProject
        //Get RootProject
        Project* parent = p->getParent();
        while(parent)
        {
            if(parent->getParent())
            {
                parent = parent->getParent();
            }
            else
            {
            	return parent;
            }
        }
    }
	return nullptr;
}

TTreeNode* ProjectsView::addRenderProjectToView(TTreeNode* vcNode, RenderProject* rp)
{
    if(!vcNode)
    {
    	Log(lError) <<"Node is NULL";
        return nullptr;
    }

	TTreeNode* n = mTree->Items->AddChildObject(vcNode, "", (void*) rp);
    n->Text = rp->getProjectName().c_str();
	mTree->Items->GetFirstNode()->Expand(true);
    mTree->Select(n);
    return n;
}


void ProjectsView::selectLast()
{
//	TTreeNode* n = mTree->Items->AddChildObject(vcNode, "", (void*) rp);
}
}
