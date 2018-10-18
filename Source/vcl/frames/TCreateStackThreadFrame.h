#ifndef TCreateStackThreadFrameH
#define TCreateStackThreadFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include "atFetchImagesThread.h"
//---------------------------------------------------------------------------

using at::FetchImagesThread;

//---------------------------------------------------------------------------
class PACKAGE TCreateStackThreadFrame : public TFrame
{
    __published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TProgressBar *ProgressBar1;
        TButton *Button1;
        TLabel *CurrentZ;
	void __fastcall Button1Click(TObject *Sender);
    private:
        FetchImagesThread&   mThread;

    public:
			        __fastcall 	TCreateStackThreadFrame(FetchImagesThread& thread, TComponent* Owner);
			        __fastcall	~TCreateStackThreadFrame();
};

extern PACKAGE TCreateStackThreadFrame *CreateStackThreadFrame;
#endif
