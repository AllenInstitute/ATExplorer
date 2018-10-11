#include <vcl.h>
#pragma hdrstop
#include "atProjectsTreeView.h"
#include "atATExplorerProject.h"
#include "atRenderProject.h"
#include "atATIFDataProject.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "atSession.h"
#include "atSection.h"
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

TTreeView* ProjectsTreeView::getTreeView()
{
    return mTree;
}

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

void ProjectsTreeView::update(Subject* theChangedSubject, SubjectEvent se)
{
    //!Find the subject and do whats needed..
    switch(se)
    {
        case SubjectBeingDestroyed:
	        this->stopObserving();
        break;

        case UpdateRepresentation:
            updateRepresentation(theChangedSubject);
        break;

        default:
            Log(lWarning) << "Subject Event: " << se <<" not handled in update function.";
    }
}

void ProjectsTreeView::updateRepresentation(Subject* s)
{
	//Check what kind of project the subject is
    ATExplorerProject* atep = dynamic_cast<ATExplorerProject*>(s);
    ATIFDataProject*  atIFDatap = dynamic_cast<ATIFDataProject*>(s);

    if(atep)
    {
        if(atIFDatap)
        {
            Log(lInfo) << "Updating tree for project: "<< atIFDatap->getProjectName();
            Sessions* sessions = atIFDatap->getSessions();
            TTreeNode* parent_node (getItemForProject(atIFDatap));

            if(parent_node)
            {
                parent_node->DeleteChildren();
            }

            for(int i = 0; i < sessions->count(); i++)
            {
                SessionSP session = sessions->getSession(i);
                //add session as child node to parent
                TTreeNode* parent_node (getItemForProject(atIFDatap));
                TTreeNode* session_node = mTree->Items->AddChildObject(parent_node, "", (void*) session.get());
                session_node->EditText();
                session_node->Text = session->getLabel().c_str();

                //Add Channels for each session

                StringList chs = session->getChannelLabels();
                for(int j = 0; j < chs.count(); j++)
                {
                    string ch = chs[j];
                    ChannelSP channel = session->getChannel(ch);
                    TTreeNode* ch_node = mTree->Items->AddChildObject(session_node, "", (void*) channel.get());
                    ch_node->EditText();
                    ch_node->Text = ch.c_str();

                    for(int r = 0; r < atIFDatap->getNumberOfRibbons(); r++)
                    {
                        RibbonSP ribbon = atIFDatap->getRibbon(r);
                        //Add sections for each channel
                        for(int s = 0; s < atIFDatap->getNumberOfSections(); s++)
                        {
                            //SectionSP section = atIFDatap->getSection(channel, s);
                            //TTreeNode* section_node = mTree->Items->AddChildObject(ch_node, "", (void*) atIFDatap);
                            TTreeNode* section_node = mTree->Items->AddChildObject(ch_node, "", (void*) atIFDatap);
                            section_node->EditText();
                            section_node->Text = toString(s + 1).c_str();
                        }
                    }
                }
            }
        }
    }
}

TTreeNode* ProjectsTreeView::addProjectToView(Project* project)
{
    ATExplorerProject* p = dynamic_cast<ATExplorerProject*>(project);
    if(!p)
    {
        Log(lError) << "Non Explorer Project in addProjectToView..";
        return false;
    }
    project->setTag("Hello");
    this->observe(project);
    this->mObserverTag = "ProjectsTreeView";

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

    //Every child need to be observed?
    this->observe(child);

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

TTreeNode* ProjectsTreeView::getSelectedNode()
{
	return mTree->Selected;
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

void ProjectsTreeView::createView(Project* _p)
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
    TTreeNode* n = getItemForProject(p);
    if(n)
    {
    	n->DeleteChildren();
	    n->Delete();
    }
    mProjects.selectFirst();

    mProjects.remove(p);
    //Projects are deleted HERE... should be in the remove function?
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

    TTreeNode* n = getItemForProject(p);
    if(n)
    {
    	n->DeleteChildren();
	    n->Delete();
    }

    selectProject(parent);
    mProjects.remove(p);
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

TTreeNode* ProjectsTreeView::addATIFDataProjectToView(ATExplorerProject* parent, ATIFDataProject* rp)
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
