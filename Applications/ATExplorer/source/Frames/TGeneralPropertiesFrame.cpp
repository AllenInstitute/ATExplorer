#include <vcl.h>
#pragma hdrstop
#include "TGeneralPropertiesFrame.h"
#include "dslVCLUtils.h"
#include "dslFileUtils.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTPropertyCheckBox"
#pragma link "dslTSTDStringLabeledEdit"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TGeneralPropertiesFrame *GeneralPropertiesFrame;

using namespace dsl;
//---------------------------------------------------------------------------
__fastcall TGeneralPropertiesFrame::TGeneralPropertiesFrame(TComponent* Owner)
	:
    TFrame(Owner)
    {}

//---------------------------------------------------------------------------
bool TGeneralPropertiesFrame::populate(Properties& props)
{
    props.disableEdits();
    if(props.getProperty("LOCAL_CACHE_FOLDER"))
    {
 		ImageCacheFolderE			->assignExternalProperty(dynamic_cast< Property<string>* >(props.getProperty("LOCAL_CACHE_FOLDER")), 			false);
		ConnectSSHServersOnStartupCB->assignExternalProperty(dynamic_cast< Property<bool>*   >(props.getProperty("CONNECT_SERVERS_ON_STARTUP")), 	false);
    }
    props.enableEdits();
    return true;
}

//---------------------------------------------------------------------------
void __fastcall TGeneralPropertiesFrame::mBrowseForCacheFolderClick(TObject *Sender)
{
	//Browse for folder
	string res = browseForFolder(ImageCacheFolderE->getValue());
    if(folderExists(res))
    {
		ImageCacheFolderE->setValue(res);
    }
    else
    {
    	Log(lWarning) << "Cache folder was not set..";
    }
}



