#ifndef TAboutATExplorerFormH
#define TAboutATExplorerFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Imaging.jpeg.hpp>
//---------------------------------------------------------------------------
class PACKAGE TAboutATExplorer : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TMemo *Memo1;
	TPanel *Panel1;
	TImage *Image1;
	TPanel *Panel2;
	TButton *CloseBtn;
	TLabel *versionLabel;
	TLabel *Label1;
	TLabel *Label2;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:	// User declarations
public:		// User declarations
	__fastcall TAboutATExplorer(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAboutATExplorer *AboutATExplorer;
//---------------------------------------------------------------------------
#endif
