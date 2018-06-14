#include <vcl.h>
#pragma hdrstop
#include "TImageForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

TImageForm *ImageForm;


//  TRegistryForm(const string& regRoot, const string& formName, TComponent* Owner);
__fastcall TImageForm::TImageForm(const string& regRoot, const string& fName, TComponent* Owner)
	:
    TRegistryForm(regRoot, "ImageForm", Owner),
    mPrepareForDeletion(false)
{
}

__fastcall TImageForm::~TImageForm()
{

}

bool TImageForm::load(const string& fName)
{
    TMemoryStream* stream = new TMemoryStream();
    stream->LoadFromFile(fName.c_str());
    stream->Position = 0;
    Image1->Picture->Graphic->LoadFromStream(stream);
    Image1->Repaint();
    delete stream;
    return true;
}

//---------------------------------------------------------------------------
void __fastcall TImageForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(mPrepareForDeletion)
    {
	    TRegistryForm::FormClose(Sender, Action);
    }
    else
    {
		Action = caHide;
    }
}

//--------6-------------------------------------------------------------------
void __fastcall TImageForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}


