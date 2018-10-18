#include <vcl.h>
#pragma hdrstop
#include "TCreateStackThreadFrame.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCreateStackThreadFrame *CreateStackThreadFrame;
//---------------------------------------------------------------------------

using namespace dsl;
extern int frameNr(0);
//---------------------------------------------------------------------------
__fastcall TCreateStackThreadFrame::TCreateStackThreadFrame(FetchImagesThread& t, TComponent* Owner)
	: TFrame(Owner),
    mThread(t)
{
    this->Name = "Frame_" + IntToStr(frameNr++);
}

__fastcall TCreateStackThreadFrame::~TCreateStackThreadFrame()
{
    Log(lDebug) << "Destructing a TCreateStackThreadFrame";
}
//---------------------------------------------------------------------------
void __fastcall TCreateStackThreadFrame::Button1Click(TObject *Sender)
{
    //Exit thread
    mThread.stop();
}

