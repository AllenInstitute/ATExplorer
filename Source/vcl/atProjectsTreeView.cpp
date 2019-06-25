#pragma hdrstop
#include "atProjectsTreeView.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "atATExplorerProject.h"
#include "atRenderProject.h"
#include "atATIFDataProject.h"
#include "atPointMatchCollectionProject.h"
#include "atSession.h"
#include "atSection.h"
#include "atRibbon.h"
#include "atRenderProjectItemView.h"
#include "atATIFDataProjectItemView.h"
#include "atTextFileItemView.h"

#include "atTextFile.h"
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

bool ProjectsTreeView::handleNodeClick(TTreeNode* node, bool isDoubleClick)
{
    if(!node)
    {
        return false;
    }

    //Figure out what type of item the user clicked
    ExplorerObject* eo = (ExplorerObject*) node->Data;

    if(dynamic_cast<ATIFDataProject*>(eo))
    {
        ATIFDataProject* o = dynamic_cast<ATIFDataProject*>(eo);
        if(o)
        {
            Log(lInfo) << "Clicked on ATIFData project item: " << o->getProjectName();
            return handleClick(o, isDoubleClick);
        }
    }

    else if(dynamic_cast<RenderProject*>(eo))
    {
        RenderProject* o = dynamic_cast<RenderProject*>(eo);
        if(o)
        {
            Log(lInfo) << "Clicked on RenderProject project item: " << o->getProjectName();
            return handleClick(o, isDoubleClick);
        }
    }

    else if(dynamic_cast<PointMatchCollectionProject*>(eo))
    {
        PointMatchCollectionProject* o = dynamic_cast<PointMatchCollectionProject*>(eo);
        if(o)
        {
            Log(lInfo) << "Clicked on PointMatchCollectionProject project item: " << o->getProjectName();
            return handleClick(o, isDoubleClick);
        }
    }

    else if(dynamic_cast<Channel*>(eo))
    {
        Channel* o = dynamic_cast<Channel*>(eo);
        if(o)
        {
            Log(lInfo) << "Clicked on channel item: " << o->getLabel();
            return handleClick(o, isDoubleClick);
        }
    }
    else if(dynamic_cast<Session*>(eo))
    {
        Session* o = dynamic_cast<Session*>(eo);
        if(o)
        {
            Log(lInfo) << "Clicked on session item: " << o->getLabel();
            return handleClick(o, isDoubleClick);
        }
    }
    else if(dynamic_cast<Ribbon*>(eo))
    {
        Ribbon* o = dynamic_cast<Ribbon*>(eo);
        if(o)
        {
            Log(lInfo) << "Clicked on Ribbon item: " << o->getAlias();
            return handleClick(o, isDoubleClick);
        }
    }

    else if(dynamic_cast<TextFile*>(eo))
    {
        TextFile* o = dynamic_cast<TextFile*>(eo);
        if(o)
        {
            Log(lInfo) << "Clicked on TextFile item: " << o->getFileNameWithPath();
            return handleClick(o, isDoubleClick);
        }
    }
    else if(dynamic_cast<TiffStackProject*>(eo))
    {
        TiffStackProject* o = dynamic_cast<TiffStackProject*>(eo);
        if(o)
        {
            Log(lInfo) << "Clicked on TiffStackProject: " << o->getProjectName();
            return handleClick(o, isDoubleClick);
        }
    }

    //All projects are ATExplorerProjects, so put this last...
    else if(dynamic_cast<ATExplorerProject*>(eo))
    {
        ATExplorerProject* o = dynamic_cast<ATExplorerProject*>(eo);
        if(o)
        {
            Log(lInfo) << "Clicked on ATExplorerProject project item: " << o->getProjectName();
            return handleClick(o, isDoubleClick);
        }
    }

    return false;
}

bool ProjectsTreeView::handleClick(ATExplorerProject* o, bool isDoubleClick)
{
    Log(lInfo) << "In function: " << __FUNC__;
    return true;
}

bool ProjectsTreeView::handleClick(ATIFDataProject* p, bool isDoubleClick)
{
    if(!p)
    {
        return false;
    }

    if(isDoubleClick)
    {
    	ProjectItemTabbedView* view = mViews.createView(p);

		//Select the page with projectView
	    return mViews.selectTabWithView(view);
    }

    return true;
}

bool ProjectsTreeView::handleClick(RenderProject* o, bool isDoubleClick)
{
    if(!o)
    {
        return false;
    }

    if(isDoubleClick)
    {
    	ProjectItemTabbedView* view = mViews.createView(o);

		//Select the page with projectView
	    return mViews.selectTabWithView(view);
    }
    return true;
}

bool ProjectsTreeView::handleClick(PointMatchCollectionProject* o, bool isDoubleClick)
{
    if(!o)
    {
        return false;
    }

    if(isDoubleClick)
    {
    	ProjectItemTabbedView* view = mViews.createView(o);

		//Select the page with projectView
	    return mViews.selectTabWithView(view);
    }
    return true;
}

bool ProjectsTreeView::handleClick(Ribbon* o, bool isDoubleClick)
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

bool ProjectsTreeView::handleClick(TextFile* o, bool isDoubleClick)
{
    if(!o)
    {
        return false;
    }

    //Check if a textfileviewing tab is open. If so, load current file
//	ProjectItemTabbedView* view = mViews.getFirst();
//    while(view)
//    {
//        if(dynamic_cast< TextFileItemView* >(view))
//        {
//            //Found one..
//            mViews.
//            mViews.removeView(view);
//            ProjectItemTabbedView* view = mViews.createView(o);
//
//            //Select the page with projectView
//            return mViews.selectTabWithView(view);
//        }
//        view = mViews.getNext();
//    }

    if(isDoubleClick)
    {
    	ProjectItemTabbedView* view = mViews.createView(o);
		//Select the page with projectView
	    return mViews.selectTabWithView(view);
    }

    return true;
}

bool ProjectsTreeView::handleClick(TiffStackProject* o, bool isDoubleClick)
{
    if(!o)
    {
        return false;
    }

    //Check if a textfileviewing tab is open. If so, load current file
//	ProjectItemTabbedView* view = mViews.getFirst();
//    while(view)
//    {
//        if(dynamic_cast< TextFileItemView* >(view))
//        {
//            //Found one..
//            mViews.
//            mViews.removeView(view);
//            ProjectItemTabbedView* view = mViews.createView(o);
//
//            //Select the page with projectView
//            return mViews.selectTabWithView(view);
//        }
//        view = mViews.getNext();
//    }

    if(isDoubleClick)
    {
    	ProjectItemTabbedView* view = mViews.createView(o);
		//Select the page with projectView
	    return mViews.selectTabWithView(view);
    }

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

        case UpdateTree:
        	createTreeViewNodes(dynamic_cast<ATExplorerProject*>(theChangedSubject));
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
            TTreeNode* dataRootNode (getTreeNodeForProject(atIFDatap));

            if(dataRootNode)
            {
                dataRootNode->DeleteChildren();
            }

            for(int i = 0; i < sessions->count(); i++)
            {
                SessionSP session = sessions->getSession(i);

                //add session as child node to parent
                TTreeNode* session_node = mTree.Items->AddChildObject(dataRootNode, "", (void*) session.get());
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

            //Add statetables
            StringList stateTables = atIFDatap->mATIFData.getStateTables();
            TTreeNode* stateTablesRootNode = mTree.Items->AddChildObject(dataRootNode, "StateTables", NULL);
            for(int i = 0; i < stateTables.count(); i++)
            {
                //Fix this memory leak..
                TextFile* tf = new TextFile(joinPath(atIFDatap->mATIFData.getBasePath().toString(), "scripts", stateTables[i]));
                tf->setAlias(stateTables[i]);
                TTreeNode* fileNode = mTree.Items->AddChildObject(stateTablesRootNode, stateTables[i].c_str(), (void*) tf);
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
		Project* child = p->getChild(i);
        addChildProjectToTree(project, child);

        //Check if the child have childs that needs to be added
        for(int j = 0; j < child->getNumberOfChilds(); j++)
        {
            Project* child_of_child = child->getChild(j);
            addChildProjectToTree(child, child_of_child);
        }

    }
    return n;
}

TTreeNode* ProjectsTreeView::addChildProjectToTree(Project* parent, Project* child)
{
    //Get node for the parent
	TTreeNode* parent_node (getTreeNodeForProject(parent));
    if(!parent_node)
    {
        return NULL;
    }

    //Every child need to be observed?
    this->observe(child);

	TTreeNode* child_node = mTree.Items->AddChildObject(parent_node, "", (void*) child);
    child_node->EditText();
    string nodeName =  child->getProjectName().size() > 0 ? child->getProjectName() : string("No-Name");
    child_node->Text = nodeName.c_str();
    return child_node;
}

bool ProjectsTreeView::selectProject(Project* p)
{
	mProjects.selectProject(p);
	TTreeNode* n (getTreeNodeForProject(p));
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

TTreeNode* ProjectsTreeView::getTreeNodeForProject(Project* p)
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

ProjectItemTabbedView* ProjectsTreeView::createTabbedView(Project* p)
{
    return nullptr;
}

void ProjectsTreeView::createTreeViewNodes(Project* _p)
{
    ATExplorerProject* p (dynamic_cast<ATExplorerProject*>(_p));

    if(!p)
    {
    	Log(lWarning) << "Bad project type passed to createView function";
        return;
    }

	TTreeNode* root_node (getTreeNodeForProject(p));

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
            if(!getTreeNodeForProject(child))
            {
                addChildProjectToTree(p, child);
            }
        }
    }
}

void ProjectsTreeView::expandView(Project* p)
{
    TTreeNode* n = getTreeNodeForProject(p);
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
    TTreeNode* n = getTreeNodeForProject(p);
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

bool ProjectsTreeView::removeSubProject(Project* p)
{
    Project* parent = p->getParent();

    if(!parent)
    {
        Log(lWarning) << "The project: " << p->getProjectName() << " don't have a parent";
        return false;
    }

    parent->removeChild(p);

    TTreeNode* n = getTreeNodeForProject(p);
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

TTreeNode* ProjectsTreeView::addProjectToTreeView(ATExplorerProject* parent, Project* project)
{
    if(!parent)
    {
    	Log(lError) <<"Parent is NULL";
        return nullptr;
    }

    TTreeNode* parentNode = getTreeNodeForProject(parent);
	TTreeNode* n = mTree.Items->AddChildObject(parentNode, "", (void*) project);
    n->Text = project->getProjectName().c_str();
	mTree.Items->GetFirstNode()->Expand(true);
    mTree.Select(n);
    return n;
}

//TTreeNode* ProjectsTreeView::addATIFDataProjectToTreeView(ATExplorerProject* parent, ATIFDataProject* rp)
//{
//    if(!parent)
//    {
//    	Log(lError) <<"Parent is NULL";
//        return nullptr;
//    }
//
//    TTreeNode* parentNode = getTreeNodeForProject(parent);
//	TTreeNode* n = mTree.Items->AddChildObject(parentNode, "", (void*) rp);
//    n->Text = rp->getProjectName().c_str();
//	mTree.Items->GetFirstNode()->Expand(true);
//    mTree.Select(n);
//    return n;
//}
//
void ProjectsTreeView::selectLast()
{
//	TTreeNode* n = mTree.Items->AddChildObject(vcNode, "", (void*) rp);
}






}
