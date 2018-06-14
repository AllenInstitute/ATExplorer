#ifndef TOverlayedImageH
#define TOverlayedImageH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>

//---------------------------------------------------------------------------
class TOverlayedImage : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

	private:

	public:
		__fastcall TOverlayedImage(TComponent* Owner);
};

extern PACKAGE TOverlayedImage *OverlayedImage;
#endif
