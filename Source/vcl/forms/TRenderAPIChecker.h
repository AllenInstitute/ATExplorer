//---------------------------------------------------------------------------

#ifndef TRenderAPICheckerH
#define TRenderAPICheckerH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TRenderAPIChecker : public TForm
{
__published:	// IDE-managed Components
	TRadioGroup *APIs;
private:	// User declarations
public:		// User declarations
	__fastcall TRenderAPIChecker(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRenderAPIChecker *RenderAPIChecker;
//---------------------------------------------------------------------------
#endif
