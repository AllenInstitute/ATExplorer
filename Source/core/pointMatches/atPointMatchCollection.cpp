#pragma hdrstop
#include "atPointMatchCollection.h"
#include "dslStringList.h"
#include "atStringUtils.h"
#include "atExceptions.h"
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
    return true;
}

StringList PointMatchCollection::getGroupIDs()
{
	return (mRenderClient) ? mRenderClient->PointMatchAPI.getPointMatchGroupIDs(mOwner, mName) : StringList();
}

StringList PointMatchCollection::getPGroupIDs()
{
    return (mRenderClient) ? mRenderClient->PointMatchAPI.getPPointMatchGroupIDs(mOwner, mName) : StringList();
}

StringList PointMatchCollection::getQGroupIDs()
{
    return (mRenderClient) ? mRenderClient->PointMatchAPI.getQPointMatchGroupIDs(mOwner, mName) : StringList();
}

List<PointMatch> PointMatchCollection::getPQMatches(const string& pGroup, const string& qGroup)
{
    return (mRenderClient) ? mRenderClient->PointMatchAPI.getPQMatches(mOwner, mName, pGroup, qGroup) : List<PointMatch>();
}

bool PointMatchCollection::deleteCollection()
{
    return (mRenderClient) ? mRenderClient->PointMatchAPI.deletePointMatchCollection(mOwner, mName) : false;
}

}

