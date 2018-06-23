#pragma hdrstop
#include "atSession.h"
//---------------------------------------------------------------------------
namespace at
{

Session::Session(const string& lbl, Ribbon& r)
:
mLabel(lbl),
mTiles(*this),
mRibbon(r)
{}

Session::~Session()
{}

bool Session::appendChannel(const Channel& ch)
{
	mChannels.append(ch);
}

}

