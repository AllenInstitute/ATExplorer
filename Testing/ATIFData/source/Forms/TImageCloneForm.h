#ifndef TImageCloneFormH
#define TImageCloneFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include "TRegistryForm.h"
//---------------------------------------------------------------------------

class TImageCloneForm : public TRegistryForm
{
__published:	// IDE-managed Components
	TPaintBox *PaintBox1;
	TImage *Image1;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TImageCloneForm(const string& regRoot, const string& fName, TComponent* Owner);
};


extern PACKAGE TImageCloneForm *ImageCloneForm;
#endif
