#ifndef TSelectZsFormH
#define TSelectZsFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.CheckLst.hpp>
#include "dslStringList.h"
#include "dslTIntegerLabeledEdit.h"
#include "dslTIntLabel.h"

using namespace dsl;

//---------------------------------------------------------------------------
class TSelectZsForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TListBox *SelectedItems;
	TListBox *UnSelectedItems;
	TSplitter *Splitter1;
	TPanel *Panel2;
	TButton *Button2;
	TButton *Button3;
	TPanel *Panel3;
	TButton *MoveToUnselectLBBtn;
	TButton *MoveToSelectedLBBtn;
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TIntegerLabeledEdit *ZDownSampleE;
	TLabel *Label1;
	TIntLabel *NrOfZsLlbl;
	TLabel *Label2;
	void __fastcall MoveItems(TObject *Sender);
	void __fastcall ItemsClick(TObject *Sender);
	void __fastcall ZDownSampleEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);


private:	// User declarations

	public:		// User declarations
			 __fastcall 	TSelectZsForm(TComponent* Owner);
	    void				populate(TCheckListBox* b);
        StringList			getUnSelected();
        StringList			getSelected();
        vector<int>			mAllZ;
};

extern PACKAGE TSelectZsForm *SelectZsForm;

#endif
