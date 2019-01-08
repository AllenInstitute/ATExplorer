#pragma hdrstop
#include "atPointMatchContext.h"
#include "dslStringList.h"
#include "atStringUtils.h"
#include "atExceptions.h"
//---------------------------------------------------------------------------
namespace at
{

using namespace dsl;

PointMatchCollection::PointMatchCollection(const string& name, int pc)
:
mName(name),
mPairCount(pc)
{}

PointMatchCollection::~PointMatchCollection()
{}

}

