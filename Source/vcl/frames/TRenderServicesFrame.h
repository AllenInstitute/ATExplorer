#ifndef TRenderServicesFrameH
#define TRenderServicesFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTIntegerLabeledEdit.h"
#include "dslTPropertyCheckBox.h"
#include "dslTSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "dslProperties.h"
#include "atATExplorer.h"
#include <Vcl.Menus.hpp>
#include "dslPropertiesContainer.h"
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
//---------------------------------------------------------------------------

namespace at
{
	class RenderServiceParameters;
}

using dsl::Properties;
using at::ATExplorer;
using at::RenderServiceParameters;


//---------------------------------------------------------------------------
class PACKAGE TRenderServicesFrame : public TFrame
{
    __published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox4;
        TSTDStringLabeledEdit *HostE;
        TButton *TestRenderServiceBtn;
        TIntegerLabeledEdit *MaxTileSpecsToRenderE;
        TIntegerLabeledEdit *PortE;
        TListBox *ServicesLB;
        TPanel *Panel1;
        TButton *AddRenderServiceBtn;
        TButton *RemoveServiceBtn;
        TSTDStringLabeledEdit *ProtocolE;
        TSTDStringLabeledEdit *VersionE;
        TPopupMenu *PopupMenu1;
        TMenuItem *Rename;
        TIdHTTP *IdHTTP1;

	void __fastcall TestRenderServiceBtnClick(TObject *Sender);
	void __fastcall AddRenderServiceBtnClick(TObject *Sender);
	void __fastcall ServicesLBClick(TObject *Sender);
	void __fastcall RenameClick(TObject *Sender);
	void __fastcall RemoveServiceBtnClick(TObject *Sender);

    private:
		ATExplorer& 				mExplorer;

                                	//New services are a special case
        dsl::PropertiesContainer  	mNewServices;

	    RenderServiceParameters*  	getCurrent();
        string                    	getBaseURL();

    public:
        			__fastcall 		TRenderServicesFrame(ATExplorer& e, TComponent* Owner);
        bool                		populate();
        bool                    	applyEditsForNewServices();

};

extern PACKAGE TRenderServicesFrame *RenderServicesFrame;
#endif
