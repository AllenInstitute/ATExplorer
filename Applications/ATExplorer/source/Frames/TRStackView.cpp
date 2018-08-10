#include <vcl.h>
#pragma hdrstop
#include "TRStackView.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TRStackView *RStackView;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
__fastcall TRStackView::TRStackView(TComponent* Owner)
	: TFrame(Owner)
{
}

