#include <vcl.h>
#pragma hdrstop
#include "TATESettingsForm.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "ATExplorerUIProperties.h"
#include "atVCLUtils2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

TATESettingsForm *ATESettingsForm;

using namespace dsl;
using namespace at;

extern ATExplorerUIProperties gUIProperties;
//---------------------------------------------------------------------------
__fastcall TATESettingsForm::TATESettingsForm(ATExplorer& e, TComponent* Owner)
	: TForm(Owner),
    BaseNode(NULL),
    gATExplorer(e),
    DockerContainersBaseNode(NULL),
    RenderServiceBaseNode(NULL)
{}

//---------------------------------------------------------------------------
void __fastcall TATESettingsForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}

TTreeNode* TATESettingsForm::append(shared_ptr<Properties> props)
{
    mSections.append(props);
    TTreeNode* n(nullptr);
    if(startsWith("RENDER_SERVICE", props->getSectionName()))
    {
        if(RenderServiceBaseNode == NULL)
        {
			RenderServiceBaseNode = TreeView1->Items->Add(NULL, "Render Services");
        }
    }
    else
    {
	    n = TreeView1->Items->AddChild(BaseNode, props->getSectionName().c_str());
    }
    return n;
}

//---------------------------------------------------------------------------
void __fastcall TATESettingsForm::TreeView1Change(TObject *Sender, TTreeNode *Node)
{
    if(Node->Selected)
    {
        Log(lInfo) << "User selected: " << stdstr(Node->Text);
        gUIProperties.LastSelectedSettingsSection.setValue(stdstr(Node->Text));

        //Extract the properties
        if(compareNoCase(stdstr(Node->Text), "General") == true)
        {
	        shared_ptr<Properties> props = mSections.getSection("General");
            populateGeneralPanel(*props);
			if(mRenderServicesPropertiesFrame)
            {
            	mRenderServicesPropertiesFrame->Hide();
            }
			if(mDockerContainersPropertiesFrame)
            {
            	mDockerContainersPropertiesFrame->Hide();
            }
        }
        else if(Node == RenderServiceBaseNode)
        {
          	populateRenderServicesFrame();
			if(mGeneralPropertiesFrame)
		    {
                mGeneralPropertiesFrame->Hide();
        	}
			if(mDockerContainersPropertiesFrame)
            {
            	mDockerContainersPropertiesFrame->Hide();
            }
        }

        else if(Node == DockerContainersBaseNode)
        {
          	populateDockerContainersFrame();
			if(mGeneralPropertiesFrame)
		    {
                mGeneralPropertiesFrame->Hide();
        	}
			if(mRenderServicesPropertiesFrame)
            {
            	mRenderServicesPropertiesFrame->Hide();
            }
        }
        else
        {
			if(mGeneralPropertiesFrame)
		    {
                mGeneralPropertiesFrame->Hide();
        	}
			if(mRenderServicesPropertiesFrame)
            {
            	mRenderServicesPropertiesFrame->Hide();
            }
        }
    }
}

void TATESettingsForm::populateGeneralPanel(Properties& props)
{
	if(!mGeneralPropertiesFrame)
    {
    	mGeneralPropertiesFrame = shared_ptr<TGeneralPropertiesFrame>(new TGeneralPropertiesFrame(gATExplorer, this));
    }

    mGeneralPropertiesFrame->Parent = this;
    mGeneralPropertiesFrame->Align = alClient;
    mGeneralPropertiesFrame->populate(props);
    mGeneralPropertiesFrame->Show();
}

void TATESettingsForm::populateRenderServicesFrame()
{
	if(!mRenderServicesPropertiesFrame)
    {
    	mRenderServicesPropertiesFrame = shared_ptr<TRenderServicesFrame>(new TRenderServicesFrame(gATExplorer, this));
    }

    mRenderServicesPropertiesFrame->Parent = this;
    mRenderServicesPropertiesFrame->Align = alClient;
    mRenderServicesPropertiesFrame->populate();
    mRenderServicesPropertiesFrame->Show();
}

void TATESettingsForm::populateDockerContainersFrame()
{
	if(!mDockerContainersPropertiesFrame)
    {
    	mDockerContainersPropertiesFrame = shared_ptr<TDockerContainersFrame>(new TDockerContainersFrame(gATExplorer, this));
    }

    mDockerContainersPropertiesFrame->Parent = this;
    mDockerContainersPropertiesFrame->Align = alClient;
    mDockerContainersPropertiesFrame->populate();
    mDockerContainersPropertiesFrame->Show();
}

//---------------------------------------------------------------------------
void __fastcall TATESettingsForm::FormShow(TObject *Sender)
{
	addRenderServices();
	addDockerContainers();

    //Enabling property edits causes any values changed in the UI to be stored
    //in a properties "Edit" value. The Edit value is propagated to
    //the properties real value if the user selects OK
    enablePropertyEdits();

    string c = gUIProperties.LastSelectedSettingsSection;

	//Find the last expanded item
    TTreeNode* n = getTreeItemWithCaption(c, TreeView1);
    if(n)
    {
        n->Selected = true;
        n->Expanded = true;
    }
}

//---------------------------------------------------------------------------
void __fastcall TATESettingsForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    if(ModalResult == mrOk)
    {
        applyPropertyEdits();
        if(mRenderServicesPropertiesFrame)
        {
        	mRenderServicesPropertiesFrame->applyEditsForNewServices();
        }

        if(mDockerContainersPropertiesFrame)
        {
			mDockerContainersPropertiesFrame->applyEditsForNewContainers();
        }
	}

    disablePropertyEdits();
}

//---------------------------------------------------------------------------
void __fastcall TATESettingsForm::TreeView1Click(TObject *Sender)
{
;
}

bool TATESettingsForm::addRenderServices()
{
    //Add a renderservices root node
	RenderServiceBaseNode = TreeView1->Items->Add(NULL, "Render Services");

    //Add any services
    RenderServiceParameters* rs = gATExplorer.getFirstRenderService();
    while(rs)
    {
        mSections.append(rs->getProperties());
        rs = gATExplorer.getNextRenderService();
    }
    return true;
}

bool TATESettingsForm::addDockerContainers()
{
    //Add a renderservices root node
	DockerContainersBaseNode = TreeView1->Items->Add(NULL, "Docker Containers");

    //Add any services
    DockerContainer* item = gATExplorer.getFirstDockerContainer();
    while(item)
    {
        mSections.append(item->getProperties());
        item = gATExplorer.getNextDockerContainer();
    }

    return true;
}

bool TATESettingsForm::enablePropertyEdits()
{
    return mSections.enableEdits();
}

bool TATESettingsForm::disablePropertyEdits()
{
    return mSections.disableEdits();
}

bool TATESettingsForm::discardPropertyEdits()
{
    return mSections.discardEdits();
}

int TATESettingsForm::applyPropertyEdits()
{
    //Check general setting
	return mSections.applyEdits();
}

