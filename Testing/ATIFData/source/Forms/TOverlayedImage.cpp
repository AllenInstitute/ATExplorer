#include <vcl.h>
#pragma hdrstop
#include "TOverlayedImage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOverlayedImage *OverlayedImage;

//---------------------------------------------------------------------------
__fastcall TOverlayedImage::TOverlayedImage(TComponent* Owner)
	: TForm(Owner)
{

}

void __fastcall TOverlayedImage::Image1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	int sc_DragMove = 0xF012;
    ReleaseCapture();
    Perform( WM_SYSCOMMAND, sc_DragMove, 0 );
}

//---------------------------------------------------------------------------
void __fastcall TOverlayedImage::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}


