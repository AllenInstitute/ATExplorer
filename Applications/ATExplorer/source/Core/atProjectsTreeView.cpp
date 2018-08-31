#include <vcl.h>
#pragma hdrstop
#include "atProjectsTreeView.h"
#include "atATExplorerProject.h"
#include "atRenderProject.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


namespace at
{

using namespace dsl;

ProjectsTreeView::ProjectsTreeView(TTreeView* tv)
:
mTree(tv)
{}

ProjectsTreeView::~ProjectsTreeView()
{}

Project* ProjectsTreeView::getCurrent()
{
    return mProjects.getCurrent();
}

Project* ProjectsTreeView::getFirst()
{
    return mProjects.getFirst();
}

Project* ProjectsTreeView::getNext()
{
    return mProjects.getNext();
}

TTreeNode* ProjectsTreeView::addProjectToView(Project* project)
{
    ATExplorerProject* p = dynamic_cast<ATExplorerProject*>(project);
    if(!p)
    {
        Log(lError) << "Non Explorer Project in addProjectToView..";
        return false;
    }

    //Store a reference to the pointer in the TreeView
	TTreeNode* n = mTree->Items->AddObject(NULL, project->getProjectName().c_str(), (void*) project);
    n->EditText();

    for(int i = 0; i < p->getNumberOfChilds(); i++)
    {
        addChildProjectToView(project, p->getChild(i));
    }
    return n;
}

TTreeNode* ProjectsTreeView::addChildProjectToView(Project* parent, Project* child)
{
    //Get node for the parent
	TTreeNode* parent_node (getItemForProject(parent));
    if(!parent_node)
    {
        return NULL;
    }

	TTreeNode* child_node = mTree->Items->AddChildObject(parent_node, "", (void*) child);
    child_node->EditText();
    child_node->Text = child->getProjectName().c_str();
    return child_node;
}

bool ProjectsTreeView::selectProject(Project* p)
{
	mProjects.selectProject(p);
	TTreeNode* n (getItemForProject(p));
    if(n)
    {
        n->Selected = true;
        return true;
    }
    return false;

}

TTreeNode* ProjectsTreeView::getItemForProject(Project* p)
{
    TTreeNode* item = mTree->Items->GetFirstNode();

	while (item)
  	{
        if(item->Data)
        {
            Project* itemData = (Project*) item->Data;
            if(itemData == p)
            {
                return item;
            }
        }

		item = item->GetNext();
  	}
    return nullptr;
}

void ProjectsTreeView::updateView(Project* _p)
{
    ATExplorerProject* p (dynamic_cast<ATExplorerProject*>(_p));

    if(!p)
    {
    	Log(lWarning) << "Bad project type passed to updateView function";
        return;
    }

	TTreeNode* root_node (getItemForProject(p));

    if(!root_node)
    {
        root_node = addProjectToView(p);
    }
    else
    {
    	root_node->Text = vclstr(p->getProjectName());

        //Check children
        for(int i = 0; i < p->getNumberOfChilds(); i++)
        {
            Project* child = p->getChild(i);
            if(!getItemForProject(child))
            {
                addChildProjectToView(p, child);
            }
        }
    }
}

void ProjectsTreeView::expandView(Project* p)
{
    TTreeNode* n = getItemForProject(p);
    if(n)
    {
    	n->Expand(true);
    }
    else
    {
        Log(lError) << "No node for project: " << p->getProjectName();
    }
}

string ProjectsTreeView::closeProject(Project* p)
{
    string pFile = joinPath(p->getFileFolder(), p->getFileName());
    mProjects.remove(p);
    TTreeNode* n = getItemForProject(p);
    if(n)
    {
    	n->DeleteChildren();
	    n->Delete();
    }
    mProjects.selectFirst();

    //Projects are delte HERE...
    //Notify any observers
    p->notifyObservers(SubjectBeingDestroyed);
    delete p;
    return pFile;
}

bool ProjectsTreeView::removeProject(Project* p)
{
    Project* parent = p->getParent();

    if(!parent)
    {
        return false;
    }

    parent->removeChild(p);

    mProjects.remove(p);
    TTreeNode* n = getItemForProject(p);
    if(n)
    {
    	n->DeleteChildren();
	    n->Delete();
    }

    selectProject(parent);
    return true;
}

int ProjectsTreeView::mProjectCount()
{
    return mProjects.count();
}

ATExplorerProject* ProjectsTreeView::createNewATExplorerProject()
{
    ATExplorerProject* p (new ATExplorerProject);
    p->setProjectName("ATExplorer Project " + dsl::toString(mProjects.count() + 1));
	p->setModified();
    mProjects.append(p);
    return p;
}

Project* ProjectsTreeView::getRootForSelectedProject()
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

Project* ProjectsTreeView::getSelectedProject()
{
    if(mTree->Selected)
    {
        return (Project*) mTree->Selected->Data;

    }
	return nullptr;
}

Project* ProjectsTreeView::getParentForSelectedProject()
{
    if(mTree->Selected)
    {
        Project* p = (Project*) mTree->Selected->Data;
        return  p->getParent();
    }
	return nullptr;
}

TTreeNode* ProjectsTreeView::addRenderProjectToView(ATExplorerProject* parent, RenderProject* rp)
{
    if(!parent)
    {
    	Log(lError) <<"Parent is NULL";
        return nullptr;
    }

    TTreeNode* parentNode = getItemForProject(parent);
	TTreeNode* n = mTree->Items->AddChildObject(parentNode, "", (void*) rp);
    n->Text = rp->getProjectName().c_str();
	mTree->Items->GetFirstNode()->Expand(true);
    mTree->Select(n);
    return n;
}

void ProjectsTreeView::selectLast()
{
//	TTreeNode* n = mTree->Items->AddChildObject(vcNode, "", (void*) rp);
}
}
