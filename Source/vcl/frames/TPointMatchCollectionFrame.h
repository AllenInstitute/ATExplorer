#ifndef TPointMatchCollectionFrameH
#define TPointMatchCollectionFrameH
#include "atATExplorer.h"
#include "atPointMatchCollectionProject.h"
#include "atRenderClient.h"
#include "dslTFloatLabeledEdit.h"
#include "dslTIntegerEdit.h"
#include "dslTIntegerLabeledEdit.h"
#include "dslTSTDStringEdit.h"
#include "dslTSTDStringLabeledEdit.h"
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <System.Actions.hpp>
#include <System.Classes.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.CheckLst.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdCtrls.hpp>
//---------------------------------------------------------------------------

using at::PointMatchCollectionProject;
using at::PointMatchCollection;
using at::RenderProject;
using at::RenderClient;
using at::RegionOfInterest;
using at::ATExplorer;

//---------------------------------------------------------------------------
class PACKAGE TPointMatchCollectionFrame : public TFrame
{
    __published:	// IDE-managed Components
        TPanel *mLeftPanel;
        TScrollBox *ScrollBox1;
        TGroupBox *GroupBox1;
	TPanel *IDsPanel;
        TPageControl *VisualsPC;
        TSTDStringLabeledEdit *OwnerE;
	TSTDStringLabeledEdit *CollectionE;
        TActionList *Actions;
        TIdHTTP *IdHTTP1;
	TIntegerLabeledEdit *PairsE;
	TButton *Button1;
	TAction *DeletePMCA;
	TGroupBox *GroupBox2;
	TCheckListBox *pGroupIDs;
	TGroupBox *GroupBox3;
	TCheckListBox *qGroupIDs;
	TPanel *Panel1;
	TButton *Button2;
	void __fastcall DeletePMCAExecute(TObject *Sender);

    private:
                                                        //A Reference to a PointMatchCollection project
        PointMatchCollectionProject&		            mPMC;
		PointMatchCollection& 							mTheCollection;

                                                        //Currently, the RenderClient need a RenderProject for initialization
        RenderProject                                   mRP;
        RenderClient                                    mRC;

        //Render areas history
        void                                            populate();

    public:
    						__fastcall 					TPointMatchCollectionFrame(ATExplorer& e, PointMatchCollectionProject& rp, TComponent* Owner);
		void 				__fastcall 					getValidZsForStack();

};

extern PACKAGE TPointMatchCollectionFrame *PointMatchCollectionFrame;
#endif
