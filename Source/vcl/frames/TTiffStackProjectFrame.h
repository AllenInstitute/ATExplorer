#ifndef TTiffStackProjectFrameH
#define TTiffStackProjectFrameH
#include "dslTSTDStringLabeledEdit.h"
#include "atPopulateATDataThread.h"
#include "atTiffStackProject.h"
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
using at::TiffStackProject;

//---------------------------------------------------------------------------
class PACKAGE TTiffStackProjectFrame : public TFrame
{
    __published:	// IDE-managed Components
        TGroupBox *GroupBox1;
		TMemo *Memo1;
	TGroupBox *GroupBox2;
	TButton *Button1;
	TPanel *Panel1;
	TPanel *Panel2;
	TScrollBar *ScrollBar1;
	void __fastcall Button1Click(TObject *Sender);

    private:
                                            //A Reference to a TiffStack project
        TiffStackProject&	 			    mTiffStackProject;
        void                                populate();
    public:
    						__fastcall 		TTiffStackProjectFrame(at::TiffStackProject& tf, TComponent* Owner);
};

extern PACKAGE TTiffStackProjectFrame *TiffStackProjectFrame;
#endif
