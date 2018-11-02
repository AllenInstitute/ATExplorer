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

using std::list;
using dsl::PropertiesContainer;
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
        void     												populateGeneralPanel(Properties& props);
		shared_ptr<TGeneralPropertiesFrame>                     mGeneralPropertiesFrame;
//		shared_ptr<TRenderServicesFrame>      	                mGeneralPropertiesFrame;

	public:
													__fastcall 	TATESettingsForm(TComponent* Owner);
        TTreeNode*                                              append(shared_ptr<Properties> props);
        bool                                                    enablePropertyEdits();
        bool                                                    disablePropertyEdits();
        bool                                                    discardPropertyEdits();
        int                                                     applyPropertyEdits();
};

extern PACKAGE TATESettingsForm *ATESettingsForm;
#endif
