#ifndef TATIFDataProjectFrameH
#define TATIFDataProjectFrameH
#include "atATIFDataProject.h"
#include <System.Classes.hpp>
#include <Vcl.CheckLst.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include "dslTSTDStringLabeledEdit.h"
#include "atPopulateATDataThread.h"
//---------------------------------------------------------------------------
using at::ATIFDataProject;

//---------------------------------------------------------------------------
class PACKAGE TATIFDataProjectFrame : public TFrame
{
    __published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TSTDStringLabeledEdit *DataRootFolderE;
        TButton *ScanDataBtn;
        TGroupBox *GroupBox2;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *NrOfRibbonsLbl;
        TLabel *NrOfSectionsLbl;
        TLabel *NrOfSessionsLbl;
        TLabel *NrOfTilesLbl;
        TProgressBar *PopulatePB;
        TLabel *Label5;
        TLabel *NrOfChannelsLbl;
	TButton *Button1;
        void __fastcall ScanDataBtnClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);

    private:
                                            //A Reference to a atifdata project
        ATIFDataProject&		      	    mProject;
        void                                populate();
        at::PopulateATDataThread            mPopulateDataThread;

        void								onThreadEnter(void*, 	void*);
        void								onThreadProgress(void*, void*);
        void								onThreadExit(void*, 	void*);

    public:
    						__fastcall 		TATIFDataProjectFrame(ATIFDataProject& rp, TComponent* Owner);
};

extern PACKAGE TATIFDataProjectFrame *ATIFDataProjectFrame;
#endif
