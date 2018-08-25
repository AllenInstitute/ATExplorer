#include <vcl.h>
#pragma hdrstop
#include "atProjects.h"
#include "dslStringList.h"
#include <sstream>
#include "dslException.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace at
{

using namespace std;
using namespace dsl;

Projects::Projects()
{
	mCurrentProjectIter = mProjects.begin();
}

Projects::~Projects()
{}

Project* Projects::getRootProject(Project* p)
{
    //Find project root for project

}

void Projects::append(Project* p)
{
    mProjects.push_back(p);
    selectLast();
}

void Projects::remove(Project* p)
{
    mProjects.remove(p);
}

bool Projects::selectProject(Project* p)
{
	mCurrentProjectIter = std::find(mProjects.begin(), mProjects.end(), p);
    return (mCurrentProjectIter != mProjects.end()) ? true : false;
}

Project* Projects::getCurrent()
{
    return *mCurrentProjectIter;
}

Project* Projects::selectFirst()
{
    return getFirst();
}

Project* Projects::selectLast()
{
    return getLast();
}

Project* Projects::getFirst()
{
	mCurrentProjectIter = mProjects.begin();
    return *(mCurrentProjectIter);
}

Project* Projects::getNext()
{
    if(mCurrentProjectIter != mProjects.end())
    {
        mCurrentProjectIter++;
        if(mCurrentProjectIter != mProjects.end())
        {
            return (*mCurrentProjectIter);
        }
    }
    return nullptr;
}

Project* Projects::getPrevious()
{
    if(mCurrentProjectIter != mProjects.begin())
    {
        mCurrentProjectIter--;
        return (*mCurrentProjectIter);
    }
    return nullptr;
}

Project* Projects::getLast()
{
    if(count() > 0)
    {
		mCurrentProjectIter = mProjects.end();
        --mCurrentProjectIter;
        return (*mCurrentProjectIter);
    }
    return nullptr;
}

int Projects::count()
{
    return mProjects.size();
}




}
