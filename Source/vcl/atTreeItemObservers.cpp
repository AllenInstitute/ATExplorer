#pragma hdrstop
#include "atTreeItemObservers.h"
#include "atRenderProjectView.h"
#include "dslProject.h"
#include "dslLogger.h"
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
using namespace std;
TreeItemObservers::TreeItemObservers(TPageControl& pc)
:
mMainPC(pc)
{
    this->mObserverTag = "TreeItemObservers";
}

TreeItemObservers::~TreeItemObservers()
{
	this->setInActive();
}

bool TreeItemObservers::createView(Subject* eo)
{
    TTabSheet* sh = getTabForSubject(eo);
    if(sh)
    {
        mMainPC.ActivePage = sh;
        return false;
    }

    Log(lInfo) << "ItemType: " << eo->getTypeName();

    if(dynamic_cast<ATIFDataProject*>(eo))
    {
        ATIFDataProject* o = dynamic_cast<ATIFDataProject*>(eo);
        if(o)
        {
            Log(lInfo) << "Clicked on ATIFData project item: " << o->getProjectName();
	       	shared_ptr<ATIFDataProjectView> obs (new ATIFDataProjectView(mMainPC, *o));
        	mViews.push_back(obs);
		    this->observe(obs->getSubject());
        }
    }
    if(dynamic_cast<RenderProject*>(eo))
    {
        RenderProject* o = dynamic_cast<RenderProject*>(eo);
        if(o)
        {
            Log(lInfo) << "Clicked on RenderProject project item: " << o->getProjectName();
        }
    }

    if(dynamic_cast<ATExplorerProject*>(eo))
    {
        ATExplorerProject* o = dynamic_cast<ATExplorerProject*>(eo);
        if(o)
        {
            Log(lInfo) << "Clicked on ATExplorerProject project item: " << o->getProjectName();
        }
    }

    else if(dynamic_cast<Channel*>(eo))
    {
        Channel* o = dynamic_cast<Channel*>(eo);
        if(o)
        {
            Log(lInfo) << "Clicked on channel item: " << o->getLabel();
        }
    }
    else if(dynamic_cast<Session*>(eo))
    {
        Session* o = dynamic_cast<Session*>(eo);
        if(o)
        {
            Log(lInfo) << "Clicked on session item: " << o->getLabel();
        }
    }
    else if(dynamic_cast<Ribbon*>(eo))
    {
        Ribbon* o = dynamic_cast<Ribbon*>(eo);
        if(o)
        {
            Log(lInfo) << "Clicked on Ribbon item: " << o->getAlias();
        }
    }

    return true;
}


void TreeItemObservers::closeAll()
{
	mViews.clear();
}

//void TreeItemObservers::append(shared_ptr<TabbedProjectView> v)
//{
//	mViews.push_back(v);
//
//}

unsigned int TreeItemObservers::count()
{
    return mViews.size();
}

//Just deleting the view.. not the subject..
bool TreeItemObservers::removeViewOnTabSheet(TTabSheet* ts)
{
    int nrOfViews = mViews.size();
    //Find observer object
    for(int i = 0; i < mViews.size(); i++)
    {
        shared_ptr<TabbedProjectView> rpv = mViews[i];
        if(rpv && rpv->getTabSheet() == ts)
        {
            //Tell this observer to go away...
            removeViewForSubject(rpv->getSubject());
        }
    }
    return (nrOfViews > mViews.size()) ? true : false;
}

//Should not be needed..
bool TreeItemObservers::removeViewForSubject(Subject* p)
{
    //Find observer object
    for(int i = 0; i < mViews.size(); i++)
    {
        shared_ptr<TabbedProjectView> rpv = mViews[i];
        p->detachObserver(rpv.get());

        if(rpv && rpv->getSubject() == p )
        {
            mViews.erase(mViews.begin() + i);
            return true;
        }
    }
    return false;
}

TTabSheet* TreeItemObservers::getTabForSubject(Subject* o)
{
	vector< shared_ptr<TabbedProjectView> >::iterator it;
    for(it = mViews.begin(); it != mViews.end(); ++it)
    {
		shared_ptr<TabbedProjectView> ptr = (*it);
        if(ptr)
        {
            if(ptr->getSubject() == o)
            {
                return ptr->getTabSheet();
            }
        }
    }
    return nullptr;
}

void TreeItemObservers::update(Subject* s, SubjectEvent se)
{
    if(se == SubjectEvent::SubjectBeingDestroyed)
    {
        removeViewForSubject(s);
        Log(lInfo) << "Observing: " <<s->getTag()<< ": " <<s->hasObserver(this);
	}

    if(mViews.size() == 0)
    {
        this->setInActive();
    }
    Log(lInfo) << "Number of views after update: " << mViews.size();
}


}
