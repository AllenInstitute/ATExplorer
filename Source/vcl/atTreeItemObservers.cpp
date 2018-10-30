#pragma hdrstop
#include "atTreeItemObservers.h"
#include "atRenderProjectItemView.h"
#include "dslProject.h"
#include "dslLogger.h"
#include "atATExplorerProject.h"
#include "atRenderProject.h"
#include "atATIFDataProject.h"
#include "atSession.h"
#include "atSection.h"
#include "atRibbon.h"
#include "atATIFDataProjectItemView.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace at
{

using namespace dsl;
using namespace std;

TreeItemObservers::TreeItemObservers(TPageControl& pc)
:
MainPC(pc)
{
    this->mObserverTag = "TreeItemObservers";
}

TreeItemObservers::~TreeItemObservers()
{
	this->setInActive();
}

bool TreeItemObservers::selectTabWithView(ProjectItemTabbedView* v)
{
    if(!v)
    {
        return false;
    }

    TTabSheet* theSheet = getTabForSubject(v->getSubject());

    for(int i = 0; i < MainPC.PageCount; i++)
    {
        TTabSheet* sh = MainPC.Pages[i];
        if(sh == theSheet)
        {
			MainPC.TabIndex = i;
            return true;
        }
    }
    return false;
}

ProjectItemTabbedView* TreeItemObservers::createView(Subject* eo)
{
	if(!eo)
    {
        return false;
    }
    Log(lInfo) << "ItemType: " << eo->getTypeName();

    TTabSheet* sh = getTabForSubject(eo);
    if(sh)
    {
        MainPC.ActivePage = sh;
        return dynamic_cast<ProjectItemTabbedView*>(eo);
    }

    else if(dynamic_cast<ATIFDataProject*>(eo))
    {
        ATIFDataProject* o = dynamic_cast<ATIFDataProject*>(eo);
        if(o)
        {
            Log(lInfo) << "Creating a ATIFData project view";
	       	shared_ptr<ATIFDataProjectItemView> aView(new ATIFDataProjectItemView(MainPC, *o));
        	mViews.push_back(aView);
		    this->observe(aView->getSubject());
            return aView.get();
        }
    }
    else if(dynamic_cast<RenderProject*>(eo))
    {
        RenderProject* o = dynamic_cast<RenderProject*>(eo);
        if(o)
        {
            Log(lInfo) << "Creating a Render ProjectView";
            shared_ptr<RenderProjectItemView> aItemView(new RenderProjectItemView(MainPC,  *o));//, gAU.ImageMagickPath.getValue()));
           	mViews.push_back(aItemView);
            this->observe(aItemView->getSubject());
            return aItemView.get();
        }
    }

    else if(dynamic_cast<ATExplorerProject*>(eo))
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

    return nullptr;
}

void TreeItemObservers::closeAll()
{
	mViews.clear();
}

unsigned int TreeItemObservers::count()
{
    return mViews.size();
}

//Just deleting the view.. not the subject..
bool TreeItemObservers::removeViewOnTabSheet(TTabSheet* ts)
{
    //Find observer object
    for(int i = 0; i < mViews.size(); i++)
    {
        shared_ptr<ProjectItemTabbedView> rpv = mViews[i];
        if(rpv && rpv->getTabSheet() == ts)
        {
            //Tell this observer to go away...
            return removeViewForSubject(rpv->getSubject());
        }
    }
    return false;
}

//Should not be needed..
bool TreeItemObservers::removeViewForSubject(Subject* p)
{
    //Find observer object
    for(int i = 0; i < mViews.size(); i++)
    {
        shared_ptr<ProjectItemTabbedView> rpv = mViews[i];
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
	vector< shared_ptr<ProjectItemTabbedView> >::iterator it;
    for(it = mViews.begin(); it != mViews.end(); ++it)
    {
		shared_ptr<ProjectItemTabbedView> ptr = (*it);
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
