#include <vcl.h>
#pragma hdrstop
#include "TGeneralPropertiesFrame.h"
#include "dslVCLUtils.h"
#include "dslFileUtils.h"
#include "dslLogger.h"
#include "ATExplorerUIProperties.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTPropertyCheckBox"
#pragma link "dslTSTDStringLabeledEdit"
#pragma resource "*.dfm"
TGeneralPropertiesFrame *GeneralPropertiesFrame;
//---------------------------------------------------------------------------

using namespace dsl;
using namespace at;
extern ATExplorerUIProperties gUIProperties;
//---------------------------------------------------------------------------
__fastcall TGeneralPropertiesFrame::TGeneralPropertiesFrame(ATExplorer& e, TComponent* Owner)
	:
    TFrame(Owner),
    mExplorer(e)
    {}

//---------------------------------------------------------------------------
bool TGeneralPropertiesFrame::populate(Properties& props)
{
    props.disableEdits();
    props.add(&(mExplorer.Properties.ImageMagickPath));
    props.add(&(mExplorer.Properties.LocalCacheFolder));

	ImageMagickPathE				->assignExternalProperty(dynamic_cast< Property<string>* >(&mExplorer.Properties.ImageMagickPath), 		 	false);
    ImageMagickPathE->update();

	OutputDataRootFolderE	     	->assignExternalProperty(dynamic_cast< Property<string>* >(&mExplorer.Properties.LocalCacheFolder), 	 	false);
    OutputDataRootFolderE->update();

    props.enableEdits();

    RenderServicesCB->Clear();
    RenderServiceParameters* rs =  mExplorer.getFirstRenderService();
    while(rs)
    {
		RenderServicesCB->AddItem(rs->getName().c_str(), (TObject*) rs);
        rs = mExplorer.getNextRenderService();
    }

    if (RenderServicesCB->Items->Count)
    {
    	RenderServicesCB->ItemIndex = 0;
    }

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
    else if(btn == BrowseForDataOutputPathBtn)
    {
        string res = browseForFolder(OutputDataRootFolderE->getValue());
        if(folderExists(res))
        {
            OutputDataRootFolderE->setValue(res);
        }
        else
        {
            Log(lWarning) << "Cache path was not set..";
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TGeneralPropertiesFrame::TestRenderServiceBtnClick(TObject *Sender)
{
    //Get some render owners
    MessageDlg("Not Implemented yet", mtInformation, TMsgDlgButtons() << mbOK, 0);
}
