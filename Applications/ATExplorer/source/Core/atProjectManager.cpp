#pragma hdrstop
#include "atProjectManager.h"
#include "atATExplorerProject.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace dsl;

namespace at
{

////TTreeNode* getNodeWithCaption(TTreeView* tv, const string& name);
////TTreeNode* getNodeWithProject(TTreeView* tv, const ATExplorerProject* p);
//
//ProjectManager::ProjectManager()
//
//{
////	mCurrentProject = mProjects.begin();
//}
//
//ProjectManager::~ProjectManager()
//{}
//
//ATExplorerProject* ProjectManager::createNewProject(const string& projName)
//{
//	//Check how many main nodes
//    string pName;
//    if(projName.size() < 1)
//    {
//	    int count = mProjects.count();
//		pName = "ATExplorer Project " + dsl::toString(count);
//    }
//    else
//    {
//        pName = projName;
//    }
//
//	ATExplorerProject* p (new ATExplorerProject(pName));
//    mProjects.append(p);
//
//    Log(lInfo) << "Created a new ATExplorer project: "<<pName;
//
////    ProjectTView->Items->AddObject(NULL, p->getProjectName().c_str(), (void*) p);
//	return p;
//}
//
//bool ProjectManager::closeProject(ATExplorerProject* p)
//{
//    int res = saveProject(p);
//	if( res == mrOk || res == mrNo)
//    {
//        //Remove project from manager
////        mProjects.closeProject(p);
//
////        if(ProjectTView->Selected)
////        {
////			ProjectTView->Items->Delete(ProjectTView->Selected);
////        }
//
//        return true;
//    }
//    return false;
//}
//
////bool ProjectManager::selectItem(TTreeNode* item)
////{
////	//Check if this is a root node or a child
////    if(item->Parent == NULL)
////    {
////		ATExplorerProject* p = (ATExplorerProject*) item->Data;
////        if(p)
////        {
////        	Log(lInfo) << "Selecting project: " << p->getProjectName();
////            return true;
////        }
////    }
////    else
////	{}
////    return false;
////}
//
//bool ProjectManager::selectFirst()
//{
////	mCurrentProject = mProjects.begin();
////    return selectNode(*mCurrentProject);
//}
//
//ATExplorerProject* ProjectManager::getCurrentProject()
//{
//	//This relies on proper iterator management troughout the code!
//    return mProjects.getCurrent();
//}
//
//bool ProjectManager::selectLast()
//{
//	if(!mProjects.count())
//    {
//    	return false;
//    }
//
////	mCurrentProject = mProjects.end();
////    mCurrentProject--;
////
////    return selectNode(*mCurrentProject);
//    return false;
//}
//
////bool ProjectManager::selectNode(ATExplorerProject*)
////{
////	TTreeNode* node = getNodeWithProject(ProjectTView, (*mCurrentProject));
////    if(node)
////    {
////		ProjectTView->Selected = node;
////        return true;
////    }
////	return false;
////}
//
//bool ProjectManager::selectNone()
//{
////    mCurrentProject = mProjects.end();
//    return true;
//}
//
//bool ProjectManager::selectNext()
//{
//	return false;
//}
//
//bool ProjectManager::selectPrevious()
//{
//	return false;
//}
//
////TTreeNode* getNodeWithCaption(TTreeView* tv, const string& name)
////{
////	for(int i = 0; i < tv->Items->Count; i++)
////    {
////		TTreeNode* node = tv->Items->Item[i];
////    	if(node->Text == vclstr(name))
////        {
////        	return node;
////        }
////    }
////    return NULL;
////}
//
////TTreeNode* getNodeWithProject(TTreeView* tv, const ATExplorerProject* p)
////{
////	for(int i = 0; i < tv->Items->Count; i++)
////    {
////		TTreeNode* node = tv->Items->Item[i];
////    	if((ATExplorerProject*) node->Data == p)
////        {
////        	return node;
////        }
////    }
////    return NULL;
////}
//
}
