#include <vcl.h>
#pragma hdrstop
#include "atROIHistory.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

ROIHistory::ROIHistory()
{
    mCurrent = mHistory.begin();
}

ROIHistory::~ROIHistory(){}
void ROIHistory::clear()
{
	mHistory.clear();
}

void ROIHistory::add(RegionOfInterest& rb)
{
	mHistory.push_back(rb);
    mCurrent = mHistory.end();
    mCurrent--;
}

void ROIHistory::insert(RegionOfInterest& rb)
{
	if(mCurrent != (mHistory.end() - 1))
    {
		mCurrent = mHistory.insert(mCurrent, rb);
        mHistory.erase(mCurrent + 1, mHistory.end());
    }
    else
    {
		mHistory.push_back(rb);
    	mCurrent = mHistory.end();
	    mCurrent--;
    }
}

RegionOfInterest* ROIHistory::current()
{
	if(mCurrent != mHistory.end())
    {
    	return &(*(mCurrent));
    }
    return NULL;
}

RegionOfInterest* ROIHistory::first()
{
	return  mHistory.size() ? &(mHistory.front()) : NULL;
}

RegionOfInterest* ROIHistory::last()
{
	return  mHistory.size() ? &(mHistory.back()) : NULL;
}

RegionOfInterest* ROIHistory::next()
{
    if(mCurrent != mHistory.end())
    {
        mCurrent++;
        if(mCurrent != mHistory.end())
        {
            return &(*(mCurrent));
        }
    }
    return NULL;
}

RegionOfInterest* ROIHistory::previous()
{
    if(mCurrent != mHistory.begin())
    {
        mCurrent--;
        return &(*(mCurrent));
    }
    return NULL;

}

