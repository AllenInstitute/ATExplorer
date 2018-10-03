#include <vcl.h>
#pragma hdrstop
#include "TATIFDataProjectFrame.h"
#include "dslVCLUtils.h"

#include "dslLogger.h"
#include "dslFileUtils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

TATIFDataProjectFrame *ATIFDataProjectFrame;
using namespace dsl;
using namespace at;
using namespace Poco;

extern int frameNr(0);

//---------------------------------------------------------------------------
__fastcall TATIFDataProjectFrame::TATIFDataProjectFrame(ATIFDataProject& rp, TComponent* Owner)
	: TFrame(Owner),
    mRP(rp)
{
    this->Name = string("ATIFDataFrame_" +  dsl::toString(frameNr++)).c_str();
    populate();
}

void TATIFDataProjectFrame::populate()
{
}



