//---------------------------------------------------------------------------

#ifndef SelectZsFormH
#define SelectZsFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm6 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TListBox *ListBox1;
	TListBox *ListBox2;
	TSplitter *Splitter1;
	TButton *Button1;
	TPanel *Panel2;
	TButton *Button2;
	TButton *Button3;
private:	// User declarations
public:		// User declarations
	__fastcall TForm6(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm6 *Form6;
//---------------------------------------------------------------------------
#endif
