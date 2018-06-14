#pragma hdrstop
#include "atProjectManager.h"
#include "atVolumeCreatorProject.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"


using namespace dsl;

TTreeNode* getNodeWithCaption(TTreeView* tv, const string& name);
TTreeNode* getNodeWithProject(TTreeView* tv, const VolumeCreatorProject* p);

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
	VolumeCreatorProject* vcp = new VolumeCreatorProject(pName);
    mVCProjects.push_back(vcp);

    Log(lInfo) << "Created a new VolumeCreator project";

    ProjectTView->Items->AddObject(NULL, vcp->getProjectName().c_str(), (void*) vcp);
	return true;
}

bool ProjectManager::selectItem(TTreeNode* item)
{
	//Check if this is a root node or a child
    if(item->Parent == NULL)
    {
		VolumeCreatorProject* vcp = (VolumeCreatorProject*) item->Data;
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

VolumeCreatorProject* ProjectManager::getCurrentProject()
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

bool ProjectManager::selectNode(VolumeCreatorProject*)
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

TTreeNode* getNodeWithProject(TTreeView* tv, const VolumeCreatorProject* p)
{
	for(int i = 0; i < tv->Items->Count; i++)
    {
		TTreeNode* node = tv->Items->Item[i];
    	if((VolumeCreatorProject*) node->Data == p)
        {
        	return node;
        }
    }
    return NULL;
}
