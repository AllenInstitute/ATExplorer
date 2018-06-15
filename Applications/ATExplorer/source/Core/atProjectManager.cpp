#pragma hdrstop
#include "atProjectManager.h"
#include "atATExplorerProject.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"


using namespace dsl;

TTreeNode* getNodeWithCaption(TTreeView* tv, const string& name);
TTreeNode* getNodeWithProject(TTreeView* tv, const ATExplorerProject* p);

ProjectManager::ProjectManager(TTreeView& tv)
:
ProjectTView(&tv)
{
	mCurrentVCProject = mVCProjects.begin();
}

ProjectManager::~ProjectManager()
{}

bool ProjectManager::createNewProject()
{
	//Check how many main nodes
    int nrOfVCPs = mVCProjects.size();

	string pName = "VC Project " + dsl::toString(nrOfVCPs);
	ATExplorerProject* vcp = new ATExplorerProject(pName);
    mVCProjects.push_back(vcp);

    Log(lInfo) << "Created a new ATExplorer project";

    ProjectTView->Items->AddObject(NULL, vcp->getProjectName().c_str(), (void*) vcp);
	return true;
}

bool ProjectManager::selectItem(TTreeNode* item)
{
	//Check if this is a root node or a child
    if(item->Parent == NULL)
    {
		ATExplorerProject* vcp = (ATExplorerProject*) item->Data;
        if(vcp)
        {
        	Log(lInfo) << "Selecting project: " << vcp->getProjectName();
            return true;
        }
    }
    else
	{}
    return false;
}

bool ProjectManager::selectFirst()
{
	mCurrentVCProject = mVCProjects.begin();

    return selectNode(*mCurrentVCProject);
}

ATExplorerProject* ProjectManager::getCurrentProject()
{
	//This relies on proper iterator management troughout the code!
	return (mCurrentVCProject != mVCProjects.end()) ? (*mCurrentVCProject) : NULL;
}

bool ProjectManager::selectLast()
{
	if(!mVCProjects.size())
    {
    	return false;
    }

	mCurrentVCProject = mVCProjects.end();
    mCurrentVCProject--;

    return selectNode(*mCurrentVCProject);
}

bool ProjectManager::selectNode(ATExplorerProject*)
{
	TTreeNode* node = getNodeWithProject(ProjectTView, (*mCurrentVCProject));
    if(node)
    {
		ProjectTView->Selected = node;
        return true;
    }
	return false;
}

bool ProjectManager::selectNext()
{
	return false;
}

bool ProjectManager::selectPrevious()
{
	return false;
}

TTreeNode* getNodeWithCaption(TTreeView* tv, const string& name)
{
	for(int i = 0; i < tv->Items->Count; i++)
    {
		TTreeNode* node = tv->Items->Item[i];
    	if(node->Text == vclstr(name))
        {
        	return node;
        }
    }
    return NULL;
}

TTreeNode* getNodeWithProject(TTreeView* tv, const ATExplorerProject* p)
{
	for(int i = 0; i < tv->Items->Count; i++)
    {
		TTreeNode* node = tv->Items->Item[i];
    	if((ATExplorerProject*) node->Data == p)
        {
        	return node;
        }
    }
    return NULL;
}
