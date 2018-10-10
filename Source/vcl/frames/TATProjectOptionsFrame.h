#ifndef TATProjectOptionsFrameH
#define TATProjectOptionsFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TATProjectOptionsFrame : public TFrame
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TSTDStringLabeledEdit *STDStringLabeledEdit1;
	TButton *Button1;
private:	// User declarations
public:		// User declarations
	__fastcall TATProjectOptionsFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TATProjectOptionsFrame *ATProjectOptionsFrame;
//---------------------------------------------------------------------------
#endif
