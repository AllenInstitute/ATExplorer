//---------------------------------------------------------------------------

#ifndef TATESettingsFormH
#define TATESettingsFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TATESettingsForm : public TForm
{
__published:	// IDE-managed Components
	TTreeView *TreeView1;
	TPanel *Panel1;
	TButton *Button1;
	TButton *Button2;
private:	// User declarations
public:		// User declarations
	__fastcall TATESettingsForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TATESettingsForm *ATESettingsForm;
//---------------------------------------------------------------------------
#endif
