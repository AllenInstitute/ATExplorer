//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TRenderAPIChecker.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TRenderAPIChecker *RenderAPIChecker;
//---------------------------------------------------------------------------
__fastcall TRenderAPIChecker::TRenderAPIChecker(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
