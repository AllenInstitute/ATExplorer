#ifndef TATESettingsFormH
#define TATESettingsFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <list>
#include "dslSharedPointer.h"
#include "dslIniFileProperties.h"
#include "dslRegistryProperties.h"

using std::list;
typedef dsl::shared_ptr<dsl::Properties> PropertiesSP;

//---------------------------------------------------------------------------
class PACKAGE TATESettingsForm : public TForm
{
	__published:	// IDE-managed Components
        TTreeView *TreeView1;
        TPanel *Panel1;
        TButton *Button1;
        TButton *Button2;
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

	private:
                                                        	        //Each item holds a container of related properties
        list< PropertiesSP >   									mSections;
        list< PropertiesSP >::iterator    						mSectionIterator;
		TTreeNode*												BaseNode;

	public:
													__fastcall 	TATESettingsForm(TComponent* Owner);
        void                                                    append(PropertiesSP props);
};

extern PACKAGE TATESettingsForm *ATESettingsForm;
#endif
