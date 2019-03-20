#pragma hdrstop
#include "TTextFileFrame.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "dslFileUtils.h"
#include "atATEExceptions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

TTextFileFrame *TextFileFrame;
using namespace dsl;
using namespace at;

static int frameNr(0);

//---------------------------------------------------------------------------
__fastcall TTextFileFrame::TTextFileFrame(at::TextFile& dp, TComponent* Owner)
	: TFrame(Owner),
    mTextFile(dp)
{
    this->Name = string("TextFileFrame_" +  dsl::toString(frameNr++)).c_str();
    populate();
}

//---------------------------------------------------------------------------
void TTextFileFrame::populate()
{
    //Load file into memo
	Memo1->Lines->LoadFromFile(mTextFile.getFileNameWithPath().c_str());
    GroupBox1->Caption = "No Edit..";
}


