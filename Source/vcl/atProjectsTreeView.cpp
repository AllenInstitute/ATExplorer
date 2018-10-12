#include <vcl.h>
#pragma hdrstop
#include "atProjectsTreeView.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "atATExplorerProject.h"
#include "atRenderProject.h"
#include "atATIFDataProject.h"
#include "atSession.h"
#include "atSection.h"
#include "atRibbon.h"
#include "atRenderProjectView.h"
#include "atATIFDataProjectView.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace at
{

using namespace dsl;

ProjectsTreeView::ProjectsTreeView(TTreeView& tv, TreeItemObservers& v)
:
mTree(tv),
mViews(v)
{
    this->mObserverTag = "ProjectsTreeView";
}

ProjectsTreeView::~ProjectsTreeView()
{}

const TTreeView* ProjectsTreeView::getTreeView()
{
    return &mTree;
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

void ProjectsTreeView::handleNodeClick(TTreeNode* node, bool isDoubleClick)
{
    if(!node)
    {
        return;
    }

    //Figure out what type of item the user clicked
    ExplorerObject* eo = (ExplorerObject*) node->Data;
    Log(lInfo) << "ItemType: " << eo->getTypeName();

    if(dynamic_cast<ATIFDataProject*>(eo))
    {
        ATIFDataProject* o = dynamic_cast<ATIFDataProject*>(eo);
        if(o)
        {
            Log(lInfo) << "Clicked on ATIFData project item: " << o->getProjectName();
            handleClick(o, isDoubleClick);
        }
    }
    if(dynamic_cast<RenderProject*>(eo))
    {
        RenderProject* o = dynamic_cast<RenderProject*>(eo);
        if(o)
        {
            Log(lInfo) << "Clicked on RenderProject project item: " << o->getProjectName();
            handleClick(o, isDoubleClick);
        }
    }

    if(dynamic_cast<ATExplorerProject*>(eo))
    {
        ATExplorerProject* o = dynamic_cast<ATExplorerProject*>(eo);
        if(o)
        {
            Log(lInfo) << "Clicked on ATExplorerProject project item: " << o->getProjectName();
            handleClick(o, isDoubleClick);
        }
    }

    else if(dynamic_cast<Channel*>(eo))
    {
        Channel* o = dynamic_cast<Channel*>(eo);
        if(o)
        {
            Log(lInfo) << "Clicked on channel item: " << o->getLabel();
            handleClick(o, isDoubleClick);
        }
    }
    else if(dynamic_cast<Session*>(eo))
    {
        Session* o = dynamic_cast<Session*>(eo);
        if(o)
        {
            Log(lInfo) << "Clicked on session item: " << o->getLabel();
            handleClick(o, isDoubleClick);
        }
    }
    else if(dynamic_cast<Ribbon*>(eo))
    {
        Ribbon* o = dynamic_cast<Ribbon*>(eo);
        if(o)
        {
            Log(lInfo) << "Clicked on Ribbon item: " << o->getAlias();
            handleClick(o, isDoubleClick);
        }
    }
}


bool ProjectsTreeView::handleClick(ATExplorerProject* o, bool isDoubleClick)
{
}

bool ProjectsTreeView::handleClick(ATIFDataProject* p, bool isDoubleClick)
{
    if(!p)
    {
        return true;
    }

    if(isDoubleClick)
    {
    	createATIFDataProjectView(p);
    }

	selectProject(p);

    //Select the page with projectView
//    selectTabForTreeItem(item);
    return true;
}

bool ProjectsTreeView::handleClick(RenderProject* o, bool isDoubleClick)
{
//    Project* p = (Project*) item->Data;
//    if(p)
//    {
//        Log(lDebug) << "User double clicked: " << p->getProjectName();
//        createProjectView(p);
//    }
//
//	mPTreeView.selectProject(p);
//
//    //Select the page with projectView
//    selectTabForTreeItem(item);
}


bool ProjectsTreeView::handleClick(  Ribbon* o, bool isDoubleClick)
{
    return true;
}

bool ProjectsTreeView::handleClick(Section* o, bool isDoubleClick)
{
    return true;
}

bool ProjectsTreeView::handleClick(Session* o, bool isDoubleClick)
{
    return true;
}

bool ProjectsTreeView::handleClick(Channel* o, bool isDoubleClick)
{
    return true;
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
            Sessions* sessions = atIFDatap->mATIFData.getSessions();
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
                TTreeNode* session_node = mTree.Items->AddChildObject(parent_node, "", (void*) session.get());
                session_node->EditText();
                session_node->Text = session->getLabel().c_str();

                //Add Channels for each session

                StringList chs = session->getChannelLabels();
                for(int j = 0; j < chs.count(); j++)
                {
                    string ch = chs[j];
                    ChannelSP channel = session->getChannel(ch);
                    TTreeNode* ch_node = mTree.Items->AddChildObject(session_node, "", (void*) channel.get());
                    ch_node->EditText();
                    ch_node->Text = ch.c_str();

                    for(int r = 0; r < atIFDatap->mATIFData.getNumberOfRibbons(); r++)
                    {
                        RibbonSP ribbon = atIFDatap->mATIFData.getRibbon(r + 1);
                        //Add sections for each channel
                        TTreeNode* ribbon_node = mTree.Items->AddChildObject(ch_node, "", (void*) ribbon.get());
                        ribbon_node->EditText();
                        ribbon_node->Text = ribbon->getAlias().c_str();


//                        for(int s = 0; s < atIFDatap->getNumberOfSections(); s++)
//                        {
//                            //SectionSP section = atIFDatap->getSection(channel, s);
//                            //TTreeNode* section_node = mTree.Items->AddChildObject(ch_node, "", (void*) atIFDatap);
//                            TTreeNode* section_node = mTree.Items->AddChildObject(ch_node, "", (void*) atIFDatap);
//                            section_node->EditText();
//                            section_node->Text = toString(s + 1).c_str();
//                        }
                    }
                }
            }
        }
    }
}

TTreeNode* ProjectsTreeView::addProjectToTree(Project* project)
{
    ATExplorerProject* p = dynamic_cast<ATExplorerProject*>(project);
    if(!p)
    {
        Log(lError) << "Non Explorer Project in addProjectToView..";
        return false;
    }
    project->setTag(p->getProjectName());
    this->observe(project);
    this->mObserverTag = "ProjectsTreeView";

    //Store a reference to the pointer in the TreeView
	TTreeNode* n = mTree.Items->AddObject(NULL, project->getProjectName().c_str(), (void*) project);
    n->EditText();

    for(int i = 0; i < p->getNumberOfChilds(); i++)
    {
        addChildProjectToTree(project, p->getChild(i));
    }
    return n;
}

TTreeNode* ProjectsTreeView::addChildProjectToTree(Project* parent, Project* child)
{
    //Get node for the parent
	TTreeNode* parent_node (getItemForProject(parent));
    if(!parent_node)
    {
        return NULL;
    }

    //Every child need to be observed?
    this->observe(child);

	TTreeNode* child_node = mTree.Items->AddChildObject(parent_node, "", (void*) child);
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
	return mTree.Selected;
}

TTreeNode* ProjectsTreeView::getItemForProject(Project* p)
{
    TTreeNode* item = mTree.Items->GetFirstNode();

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
        root_node = addProjectToTree(p);
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
                addChildProjectToTree(p, child);
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
    if(mTree.Selected)
    {
        Project* p = (Project*) mTree.Selected->Data;

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
    if(mTree.Selected)
    {
        return (Project*) mTree.Selected->Data;

    }
	return nullptr;
}

Project* ProjectsTreeView::getParentForSelectedProject()
{
    if(mTree.Selected)
    {
        Project* p = (Project*) mTree.Selected->Data;
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
	TTreeNode* n = mTree.Items->AddChildObject(parentNode, "", (void*) rp);
    n->Text = rp->getProjectName().c_str();
	mTree.Items->GetFirstNode()->Expand(true);
    mTree.Select(n);
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
	TTreeNode* n = mTree.Items->AddChildObject(parentNode, "", (void*) rp);
    n->Text = rp->getProjectName().c_str();
	mTree.Items->GetFirstNode()->Expand(true);
    mTree.Select(n);
    return n;
}

void ProjectsTreeView::selectLast()
{
//	TTreeNode* n = mTree.Items->AddChildObject(vcNode, "", (void*) rp);
}


bool ProjectsTreeView::createRenderProjectView(RenderProject* rp)
{
    //Check what kind of project we are to create a view for
    if(rp)
    {
        //Check if there is already a tab with this view.. if so, switch to it
        TTabSheet* sh = mViews.getTabForSubject(rp);
//        if(sh)
//        {
//            mMainPC.ActivePage = sh;
//            return false;
//        }
//
        //Creat a renderproject view
        Log(lInfo) << "Showing a Render ProjectView";

        //Create a new tab page
        //Views deletes themselves when subjects dies
//        shared_ptr<RenderProjectView> obs(new RenderProjectView(mMainPC,  *rp, gAU.ImageMagickPath.getValue()));
//        mViews.append(obs);

    }
}

bool ProjectsTreeView::createATIFDataProjectView(ATIFDataProject* ifData)
{
    if(ifData)
    {
        //Check if there is already a tab with this view.. if so, switch to it
        //Creat a renderproject view
        Log(lInfo) << "Creating a ATIF Data Project View";

        //Create a new tab page
        //Views deletes themselves when subjects dies
        mViews.createView(ifData);
    }
    else
    {
        Log(lInfo) << "There is no view for this type of object";
    }
    return true;
}




}
