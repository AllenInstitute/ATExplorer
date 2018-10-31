#ifndef TTextFileFrameH
#define TTextFileFrameH
#include "dslTSTDStringLabeledEdit.h"
#include "atPopulateATDataThread.h"
#include "atTextFile.h"
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
//---------------------------------------------------------------------------
using at::TextFile;

//---------------------------------------------------------------------------
class PACKAGE TTextFileFrame : public TFrame
{
    __published:	// IDE-managed Components
        TGroupBox *GroupBox1;
		TMemo *Memo1;

    private:
                                            //A Reference to a atifdata project
        at::TextFile&	 		      	    mTextFile;
        void                                populate();
    public:
    						__fastcall 		TTextFileFrame(at::TextFile& tf, TComponent* Owner);
};

extern PACKAGE TTextFileFrame *TextFileFrame;
#endif
