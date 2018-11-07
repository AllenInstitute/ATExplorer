#ifndef TATESettingsFormH
#define TATESettingsFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "dslIniFileProperties.h"
#include "dslRegistryProperties.h"
#include "dslPropertiesContainer.h"
#include "TGeneralPropertiesFrame.h"
#include "dslSharedPointer.h"
#include "TRenderServicesFrame.h"
#include "atATExplorer.h"

using std::list;
using dsl::PropertiesContainer;
using at::ATExplorer;
//---------------------------------------------------------------------------
class PACKAGE TATESettingsForm : public TForm
{
	__published:	// IDE-managed Components
        TTreeView *TreeView1;
        TPanel *Panel1;
        TButton *Button1;
        TButton *Button2;
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
		void __fastcall TreeView1Change(TObject *Sender, TTreeNode *Node);
		void __fastcall FormShow(TObject *Sender);
		void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
		void __fastcall TreeView1Click(TObject *Sender);

	private:
                                                      	        //Each item holds a container of related properties
        PropertiesContainer                                     mSections;
 		TTreeNode*												BaseNode;
 		TTreeNode*												RenderServiceBaseNode;
        void     												populateGeneralPanel(Properties& props);
        void     												populateRenderServicesFrame();
		shared_ptr<TGeneralPropertiesFrame>                     mGeneralPropertiesFrame;
		shared_ptr<TRenderServicesFrame>      	                mRenderServicesPropertiesFrame;
		ATExplorer& 											gATExplorer;

	public:
													__fastcall 	TATESettingsForm(ATExplorer& ex, TComponent* Owner);
        TTreeNode*                                              append(shared_ptr<Properties> props);
        bool                                                    enablePropertyEdits();
        bool                                                    disablePropertyEdits();
        bool                                                    discardPropertyEdits();
        int                                                     applyPropertyEdits();
};

extern PACKAGE TATESettingsForm *ATESettingsForm;
#endif
