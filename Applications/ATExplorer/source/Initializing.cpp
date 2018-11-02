#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslLogger.h"
#include "ateAppUtilities.h"
#include "dslVCLUtils.h"
#include "atATExplorer.h"
//---------------------------------------------------------------------------
using namespace dsl;
using namespace at;

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
    static bool firstShow(true);

    if(mIsStyleMenuPopulated == false)
    {
        populateStyleMenu(ThemesMenu, ThemesMenuClick);
        mIsStyleMenuPopulated = true;
	}

    if(gAU.LastOpenedProject.getValue().size() > 0 && firstShow == true)
    {
        FileOpen1Accept(NULL);
    }
    firstShow = false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	this->Caption = vclstr(createWindowTitle("ATExplorer", Application));
    this->DoubleBuffered = true;

	gLogger.setLogLevel(gAU.LogLevel);
    TLogMemoFrame1->init();
}

bool TMainForm::setupAndReadIniParameters()
{

	//Setup parameters
    gAU.setupIniParameters();
	gAU.GeneralProperties->read();

    //Setup UI
	BottomPanel->Height 		= gAU.BottomPanelHeight;
    ProjectManagerPanel->Width 	= gAU.ProjectPanelWidth == 0 ? 100 : gAU.ProjectPanelWidth; //Gotta be at least 100px on startup

	if(gAU.LastOpenedProject.getValue().size())
    {
        Log(lInfo) << "Last opened project: " << gAU.LastOpenedProject;
		TMenuItem *Item = new TMenuItem(ReopenMenu);
        Item->Caption = gAU.LastOpenedProject.getValue().c_str();
        FileOpen1->Dialog->FileName = gAU.LastOpenedProject.getValue().c_str();
        Item->OnClick = FileOpen1Accept;
        ReopenMenu->Add(Item);
        ReopenMenu->Enabled = true;
    }

    //Add RENDER_SERVICE sections
    IniFile& iniFile = gAU.getIniFile();
    for(int i = 0; i < iniFile.getNumberOfSections(); i++)
    {
        IniSection* iniSection = iniFile.getSection(i);
        if(iniSection)
        {
            PropertiesSP props = PropertiesSP(new IniFileProperties(&iniFile, iniSection->mName));
            gAU.append(props);
        }
    }


    PropertiesSP propertiesSection = gAU.getFirstSection();
    while(propertiesSection)
    {
        if(startsWith("RENDER_SERVICE", propertiesSection->getSectionName()))
        {
            //Create a RenderService
            Log(lDebug) << "Found section: " << propertiesSection->getSectionName();

            IniFileProperties* ifp = dynamic_cast<IniFileProperties*>(propertiesSection.get());

            if(!ifp)
            {
				Log(lError) << "syntax error...";
                return false;
            }

            //We need to populate the Properties container with the data in the ini section
	        IniSection* iniSection = iniFile.getSection(propertiesSection->getSectionName());
            if(!iniSection)
            {
                //bisare, as we just added this one above...
                Log(lError) << "syntax error...";
                return false;
            }

            if(iniSection->getKey("NAME"))
            {
            	ifp->addStringProperty("NAME", iniSection->getKey("NAME")->mValue);
            }
            else
            {
                Log(lError) << "The NAME record is missing in iniSection: " << iniSection->mName;
            }

            if(iniSection->getKey("HOST"))
            {
            	ifp->addStringProperty("HOST", iniSection->getKey("HOST")->mValue);
            }
            else
            {
                Log(lError) << "The HOST record is missing in iniSection: " << iniSection->mName;
            }

            if(iniSection->getKey("PORT"))
            {
            	ifp->addIntProperty("PORT", iniSection->getKey("PORT")->asInt());
            }
            else
            {
                Log(lError) << "The PORT record is missing in iniSection: " << iniSection->mName;
            }

            if(iniSection->getKey("PROTOCOL"))
            {
            	ifp->addStringProperty("PROTOCOL", iniSection->getKey("PROTOCOL")->mValue);
            }
            else
            {
                Log(lError) << "The PROTOCOL record is missing in iniSection: " << iniSection->mName;
            }

            if(iniSection->getKey("VERSION"))
            {
            	ifp->addStringProperty("VERSION", iniSection->getKey("VERSION")->mValue);
            }
            else
            {
                Log(lError) << "The VERSION record is missing in iniSection: " << iniSection->mName;
            }

        }
		propertiesSection = gAU.getNextSection();
    }


    return true;
}

