#pragma hdrstop
#include "atPointMatchCollection.h"
#include "dslStringList.h"
#include "atStringUtils.h"
#include "atATEExceptions.h"
#include "atRenderClient.h"
#include "atJSONParser.h"
//---------------------------------------------------------------------------
namespace at
{

using namespace dsl;

PointMatchCollection::PointMatchCollection(const string& owner, const string& name, RenderClient*  renderService)
:
RenderObject(renderService),
mName(name),
mOwner(owner)
{}

PointMatchCollection::~PointMatchCollection()
{}

bool PointMatchCollection::fetch()
{
    mGroupIDs = getGroupIDs();
    StringList ps = getPGroupIDs();
    StringList qs = getQGroupIDs();
    Log(lDebug) <<"Ps: "<<ps;
    Log(lDebug) <<"Qs: "<<qs;

    //Fetch
    int matchCount(0);
    for(int p = 0; p < ps.count(); p++)
    {
        for(int q = 0; q < qs.count(); q++)
        {
            //Get pointmatches between p and q
            ListOfObjects<PointMatch> matches = getPQMatches(ps[p], qs[q]);
            if(matches.count())
            {
            	Log(lDebug) << "There are: " <<matches.count()<<" matches between " <<ps[p]<< " and " << qs[q];
				PointMatch* pm = matches.getFirst();
                while(pm)
                {
                	mPMCollection.append(*pm);
                    pm = matches.getNext();
                    matchCount++;
                }
            }
        }
    }

   	Log(lInfo) << "Fetched: "<<matchCount<<" pairs";
    return true;
}

StringList PointMatchCollection::getGroupIDs() const
{
	return (mRenderClient) ? mRenderClient->PointMatchAPI.getPointMatchGroupIDs(mOwner, mName) : StringList();
}

StringList PointMatchCollection::getPGroupIDs() const
{
    return (mRenderClient) ? mRenderClient->PointMatchAPI.getPPointMatchGroupIDs(mOwner, mName) : StringList();
}

StringList PointMatchCollection::getQGroupIDs() const
{
    return (mRenderClient) ? mRenderClient->PointMatchAPI.getQPointMatchGroupIDs(mOwner, mName) : StringList();
}

ListOfObjects<PointMatch> PointMatchCollection::getPQMatches(const string& pGroup, const string& qGroup) const
{
    return (mRenderClient) ? mRenderClient->PointMatchAPI.getPQMatches(mOwner, mName, pGroup, qGroup) : ListOfObjects<PointMatch>();
}

bool PointMatchCollection::deleteCollection()
{
    return (mRenderClient) ? mRenderClient->PointMatchAPI.deletePointMatchCollection(mOwner, mName) : false;
}

}

