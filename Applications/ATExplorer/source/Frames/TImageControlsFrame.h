//---------------------------------------------------------------------------

#ifndef TImageControlsFrameH
#define TImageControlsFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TImageControlsFrame : public TFrame
{
__published:	// IDE-managed Components
	TScrollBar *ScrollBar1;
	TGroupBox *GroupBox1;
private:	// User declarations
public:		// User declarations
	__fastcall TImageControlsFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TImageControlsFrame *ImageControlsFrame;
//---------------------------------------------------------------------------
#endif
