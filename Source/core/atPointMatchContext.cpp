#pragma hdrstop
#include "atPointMatchContext.h"
#include "dslStringList.h"
#include "atStringUtils.h"
#include "atExceptions.h"
//---------------------------------------------------------------------------
namespace at
{

using namespace dsl;

PointMatchContext::PointMatchContext(const string& owner, const string& name, int pc)
:
mOwner(owner),
mName(name),
mPairCount(pc)
{}

PointMatchContext::~PointMatchContext()
{}

}

