#pragma hdrstop
#include "atProjectObservers.h"
#include "atRenderProjectView.h"
#include "dslProject.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


namespace at
{

using namespace dsl;
using namespace std;
ProjectObservers::ProjectObservers()
{}

ProjectObservers::~ProjectObservers()
{
//    Log(lInfo) << "Removing views: " << mViews.size();
}

void ProjectObservers::closeAll()
{
	mViews.clear();
}

void ProjectObservers::append(shared_ptr<TabbedProjectView> v)
{
	mViews.push_back(v);
//    this->observe(v->getSubject());
}

unsigned int ProjectObservers::count()
{
    return mViews.size();
}

//Just deleting the view.. not the subject..
bool ProjectObservers::removeViewOnTabSheet(TTabSheet* ts)
{
    int nrOfViews = mViews.size();
    //Find observer object
    for(int i = 0; i < mViews.size(); i++)
    {
        shared_ptr<TabbedProjectView> rpv = mViews[i];
        if(rpv && rpv->getTabSheet() == ts)
        {
            //Tell this observer to go away...
            mViews.erase(mViews.begin() + i);
        }
    }
    return (nrOfViews > mViews.size()) ? true : false;
}

//Should not be needed..
bool ProjectObservers::removeViewForProject(Project* p)
{
    //Find observer object
    for(int i = 0; i < mViews.size(); i++)
    {
        shared_ptr<TabbedProjectView> rpv = mViews[i];
        if(rpv && rpv->getProject() == p || rpv->getSubject() == p)
        {
            //Tell this observer to go away...
            mViews.erase(mViews.begin() + i);
            return true;
        }
    }
    return false;
}

TTabSheet* ProjectObservers::getTabForProject(Project* p)
{
	vector< shared_ptr<TabbedProjectView> >::iterator it;
    for(it = mViews.begin(); it != mViews.end(); ++it)
    {
		shared_ptr<TabbedProjectView> ptr = (*it);
        if(ptr)
        {
            if(ptr->getProject() == p)
            {
                return ptr->getTabSheet();
            }
        }
    }
    return nullptr;
}

//void ProjectObservers::update(Subject* s, SubjectEvent se)
//{
////    if(se == SubjectEvent::SubjectBeingDestroyed)
////    {
////        //Find subject in container and remove it.
////        //Find observer object
////        for(int i = 0; i < mViews.size(); i++)
////        {
////            shared_ptr<TabbedProjectView> rpv = mViews[i];
////            if(rpv && rpv->getSubject() == s)
////            {
////                //Tell this observer to go away...
////                mViews.erase(mViews.begin() + i);
////                return;
////            }
////        }
////	}
//}
//

}
