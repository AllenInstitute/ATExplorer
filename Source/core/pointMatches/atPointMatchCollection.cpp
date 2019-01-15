#pragma hdrstop
#include "atPointMatchCollection.h"
#include "dslStringList.h"
#include "atStringUtils.h"
#include "atExceptions.h"
//---------------------------------------------------------------------------
namespace at
{

using namespace dsl;

PointMatchCollection::PointMatchCollection(const string& owner, const string& name, int pc)
:
mOwner(owner),
mName(name),
mDummyCount(pc)
{}

PointMatchCollection::~PointMatchCollection()
{}

}

