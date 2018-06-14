#ifndef TImageFormH
#define TImageFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include "dslTRegistryForm.h"
//---------------------------------------------------------------------------

class TImageForm : public TRegistryForm
{
__published:	// IDE-managed Components
	TPaintBox *PaintBox1;
	TImage *Image1;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);


	private:

	public:
						__fastcall  TImageForm(const string& regRoot, const string& fName, TComponent* Owner);
						__fastcall  ~TImageForm();


		bool						load(const string& fName);
		bool						mPrepareForDeletion;
};


extern PACKAGE TImageForm *ImageForm;
#endif
