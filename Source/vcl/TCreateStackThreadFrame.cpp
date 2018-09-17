#include <vcl.h>
#pragma hdrstop
#include "TCreateStackThreadFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCreateStackThreadFrame *CreateStackThreadFrame;
//---------------------------------------------------------------------------

extern int frameNr(0);
//---------------------------------------------------------------------------
__fastcall TCreateStackThreadFrame::TCreateStackThreadFrame(FetchImagesThread& t, TComponent* Owner)
	: TFrame(Owner),
    mThread(t)
{
    this->Name = "Frame_" + IntToStr(frameNr++);
}

//---------------------------------------------------------------------------
void __fastcall TCreateStackThreadFrame::Button1Click(TObject *Sender)
{
    //Exit thread
    mThread.stop();
}

