#pragma hdrstop
#include "TTiffStackProjectFrame.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "dslFileUtils.h"
#include "atATEExceptions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

TTiffStackProjectFrame *TiffStackProjectFrame;
using namespace dsl;
using namespace at;

static int frameNr(0);

//---------------------------------------------------------------------------
__fastcall TTiffStackProjectFrame::TTiffStackProjectFrame(at::TiffStackProject& dp, TComponent* Owner)
	: TFrame(Owner),
    mTiffStackProject(dp)
{
    this->Name = string("TiffStackProjectFrame_" +  dsl::toString(frameNr++)).c_str();
    populate();
}

//---------------------------------------------------------------------------
void TTiffStackProjectFrame::populate()
{
	GroupBox2->Caption = string("TiffStack: " + mTiffStackProject.getFileName()).c_str();
    //Load file into memo
    GroupBox1->Caption = "Properties.";
    stringstream info;

    info << mTiffStackProject.getInfo();

    StringList lines(info.str());
    for (int line = 0; line < lines.size(); line++)
    {
	    Memo1->Lines->Add(lines[line].c_str());
    }
}

//---------------------------------------------------------------------------
void __fastcall TTiffStackProjectFrame::Button1Click(TObject *Sender)
{
    string fName(joinPath(mTiffStackProject.getFilePath().toString(), mTiffStackProject.getFileName()));
    if(fName.size())
    {
        ITEMIDLIST *pidl = ILCreateFromPath(fName.c_str());
        if(pidl)
        {
            SHOpenFolderAndSelectItems(pidl,0,0,0);
            ILFree(pidl);
        }
        else
        {
            MessageDlg("Failed finding the stack!", mtWarning, TMsgDlgButtons() << mbOK, 0);
        }
    }
}


