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
	mProjects.selectProject(p);
	TTreeNode* n (getItemForProject(p));
    if(n)
    {
        n->Selected = true;
        return true;
    }
    return false;

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

void ProjectsView::updateView(Project* _p)
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

void ProjectsView::expandView(Project* p)
{
    TTreeNode* n = getItemForProject(p);
    n->Expand(true);

}

string ProjectsView::closeProject(Project* p)
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
    return pFile ;
}

bool ProjectsView::removeProject(Project* p)
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

    for(int i = 0; i < p->getNumberOfChilds(); i++)
    {
        addChildProjectToView(project, p->getChild(i));
    }
    return n;
}

TTreeNode* ProjectsView::addChildProjectToView(Project* parent, Project* child)
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

Project* ProjectsView::getRootForSelectedProject()
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

Project* ProjectsView::getSelectedProject()
{
    if(mTree->Selected)
    {
        return (Project*) mTree->Selected->Data;

    }
	return nullptr;
}

Project* ProjectsView::getParentForSelectedProject()
{
    if(mTree->Selected)
    {
        Project* p = (Project*) mTree->Selected->Data;

        return  p->getParent();
    }
	return nullptr;
}

TTreeNode* ProjectsView::addRenderProjectToView(TTreeNode* ateNode, RenderProject* rp)
{
    if(!ateNode)
    {
    	Log(lError) <<"Node is NULL";
        return nullptr;
    }

	TTreeNode* n = mTree->Items->AddChildObject(ateNode, "", (void*) rp);
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
