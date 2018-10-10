#include <vcl.h>
#pragma hdrstop
#include "TRenderSectionViewFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTIntegerEdit"
#pragma link "dslTSTDStringEdit"
#pragma resource "*.dfm"
TRenderSectionViewFrame *RenderSectionViewFrame;
//---------------------------------------------------------------------------
__fastcall TRenderSectionViewFrame::TRenderSectionViewFrame(TComponent* Owner)
	: TFrame(Owner)
{
}
//---------------------------------------------------------------------------
