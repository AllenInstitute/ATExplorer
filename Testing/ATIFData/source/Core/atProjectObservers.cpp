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
{}

void ProjectObservers::clear()
{

    mViews.clear();
}

void  ProjectObservers::append(RenderProjectView* v)
{
    shared_ptr<DummyProjectViewObserver> dummy ( new DummyProjectViewObserver (*this, *v));
	mViews.push_back(dummy);
}

unsigned int ProjectObservers::count()
{
    return mViews.size();
}

bool ProjectObservers::removeObserver(DummyProjectViewObserver* o)
{
    //Find observer object
    for(int i = 0; i < mViews.size(); i++)
    {
        observer obs = mViews[i];
        if(obs)
        {
            DummyProjectViewObserver* dObs = obs.get();
            if(dObs == o)
            {
                mViews.erase(mViews.begin() + i);
                return true;
            }
        }
    }
    return false;
}


//Just deleteing the view.. not subject!
bool ProjectObservers::removeViewOnTabSheet(TTabSheet* ts)
{
        //Find observer object
        for(int i = 0; i < mViews.size(); i++)
        {
	        shared_ptr<DummyProjectViewObserver> dummy = mViews[i];
            RenderProjectView* rpv = dynamic_cast<RenderProjectView*>(dummy->getView());
            if(rpv && rpv->getTabSheet() == ts)
            {
                //Tell this observer to go away...
                mViews.erase(mViews.begin() + i);
                delete rpv;
                return true; //Can only be on one sheet
            }
        }
    return false;
}

//Should not be needed..
bool ProjectObservers::removeViewForProject(Project* p)
{
    //Find observer object
    for(int i = 0; i < mViews.size(); i++)
    {
        shared_ptr<DummyProjectViewObserver> dummy = mViews[i];
        RenderProjectView* rpv = dynamic_cast<RenderProjectView*>(dummy->getView());
        if(rpv && rpv->getRenderProject() == p)
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
	vector< shared_ptr<DummyProjectViewObserver> >::iterator it;
    for(it = mViews.begin(); it != mViews.end(); ++it)
    {
		shared_ptr<DummyProjectViewObserver> ptr = (*it);
        if(ptr)
        {
            if(ptr->getView()->getRenderProject() == p)
            {
                return ptr->getView()->getTabSheet();
            }
        }
    }
    return nullptr;
}

void ProjectObservers::update(Subject* theChangedSubject, SubjectEvent se)
{
    if(se == SubjectEvent::SubjectBeingDestroyed)
    {
        //Go away..
        Log(lInfo) << "Subject being destroyed..";
		//Remove from container
                delete this;
    }
}


}
