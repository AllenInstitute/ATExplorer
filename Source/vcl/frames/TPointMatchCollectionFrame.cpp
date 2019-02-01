#pragma hdrstop
#include "TPointMatchCollectionFrame.h"
#include "dslVCLUtils.h"
#include "atRenderServiceParameters.h"
#include "dslLogger.h"
#include "dslFileUtils.h"
#include "atVCLUtils2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTPropertyCheckBox"
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "dslTFloatLabeledEdit"
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTIntegerEdit"
#pragma link "dslTSTDStringEdit"
#pragma link "dslTSTDStringLabeledEdit"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

TPointMatchCollectionFrame *PointMatchCollectionFrame;
using namespace dsl;
using namespace at;
using namespace Poco;

int pmcFrameNr(0);

TPoint controlToImage(const TPoint& p, double scale, double stretchFactor);

//---------------------------------------------------------------------------
__fastcall TPointMatchCollectionFrame::TPointMatchCollectionFrame(ATExplorer& e, PointMatchCollectionProject& pmp, TComponent* Owner)
	: TFrame(Owner),
    mRP("","","",""),
	mPMC(pmp),
    mTheCollection(mPMC.mPointMatchCollection),
    mRC()
{
    //mRC.assignOnImageCallback(onImage);
    mRC.setLocalCacheFolder("");
    this->Name = string("PMCFrame_" +  dsl::toString(pmcFrameNr++)).c_str();
    populate();
}

void TPointMatchCollectionFrame::populate()
{
    OwnerE->setValue(     mTheCollection.getOwner());
    CollectionE->setValue(mTheCollection.getName());

    //Fetch group IDs
	StringList IDs;

    IDs = mRC.PointMatchAPI.getPPointMatchGroupIDs(mTheCollection.getOwner(), mTheCollection.getName());

    populateCheckListBox(IDs, pGroupIDs);

//    IDs = mRC.getQPointMatchGroupIDs(mTheCollection.getOwner(), mTheCollection.getName());
//    populateCheckListBox(IDs, qGroupIDs);
//
//    PairsE->setValue(mTheCollection.refreshCount());
}

//---------------------------------------------------------------------------
void __fastcall TPointMatchCollectionFrame::DeletePMCAExecute(TObject *Sender)
{
    mRC.PointMatchAPI.deletePointMatchCollection(mTheCollection.getOwner(), mTheCollection.getName());
}



