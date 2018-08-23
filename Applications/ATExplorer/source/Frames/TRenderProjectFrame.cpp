#include <vcl.h>
#pragma hdrstop
#include "TRenderProjectFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTFloatLabeledEdit"
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTPropertyCheckBox"
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "RzSpnEdt"
#pragma link "TAffineTransformationFrame"
#pragma link "TRenderPythonRemoteScriptFrame"
#pragma link "TSSHFrame"
#pragma resource "*.dfm"
TRenderProjectFrame *RenderProjectFrame;
//---------------------------------------------------------------------------
__fastcall TRenderProjectFrame::TRenderProjectFrame(TComponent* Owner)
	: TFrame(Owner)
{
}
//---------------------------------------------------------------------------
