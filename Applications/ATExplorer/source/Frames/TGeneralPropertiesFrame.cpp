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
// 		ImageCacheFolderE			->assignExternalProperty(dynamic_cast< Property<string>* >(props.getProperty("LOCAL_CACHE_FOLDER")), 			false);
		ConnectSSHServersOnStartupCB->assignExternalProperty(dynamic_cast< Property<bool>*   >(props.getProperty("CONNECT_SERVERS_ON_STARTUP")), 	false);
    }
	ImageMagickPathE				->assignExternalProperty(dynamic_cast< Property<string>* >(props.getProperty("IMAGE_MAGICK_PATH")), 			false);
    props.enableEdits();
    return true;
}

//---------------------------------------------------------------------------
void __fastcall TGeneralPropertiesFrame::BrowseForFolderClick(TObject *Sender)
{
    TButton* btn = dynamic_cast<TButton*>(Sender);

    if(btn == BrowseForImageMagickPathBtn)
    {
        //Browse for folder
        string res = browseForFolder(ImageMagickPathE->getValue());
        if(folderExists(res))
        {
            ImageMagickPathE->setValue(res);
        }
        else
        {
            Log(lWarning) << "Image Magick Path was not set..";
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TGeneralPropertiesFrame::TestRenderServiceBtnClick(TObject *Sender)
{
    //Get some render owners
    MessageDlg("Not Implemented yet", mtInformation, TMsgDlgButtons() << mbOK, 0);
}


