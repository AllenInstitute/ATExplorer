#include <vcl.h>
#pragma hdrstop
#include "TRenderProjectFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTPropertyCheckBox"
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "dslTFloatLabeledEdit"
#pragma link "dslTIntegerLabeledEdit"
#pragma resource "*.dfm"
TRenderProjectFrame *RenderProjectFrame;

using namespace dsl;
int frameNr(0);
//---------------------------------------------------------------------------
__fastcall TRenderProjectFrame::TRenderProjectFrame(RenderProject* rp, TComponent* Owner)
	: TFrame(Owner),
    mRP(rp)
{
    this->Name = string("RPFrame_" +  dsl::toString(frameNr++)).c_str();
}

//---------------------------------------------------------------------------
