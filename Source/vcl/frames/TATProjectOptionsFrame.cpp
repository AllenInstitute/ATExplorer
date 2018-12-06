#pragma hdrstop
#include "TATProjectOptionsFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTSTDStringLabeledEdit"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------


TATProjectOptionsFrame *ATProjectOptionsFrame;

//---------------------------------------------------------------------------
__fastcall TATProjectOptionsFrame::TATProjectOptionsFrame(TComponent* Owner)
	: TFrame(Owner)
{
}

