#pragma hdrstop
#include "atApplicationSupportFunctions.h"
#include "dslUtils.h"
#include "dslLogger.h"
#include "dslRestartApplicationUtils.h"
#include "dslVCLUtils.h"

using namespace dsl;

extern string gAppDataLocation;
extern string gLogFileName;
extern string gApplicationStyle;
extern string gApplicationRegistryRoot;
extern string gAppName;
extern HWND	  gOtherAppWindow;

TPoint controlToImage(const TPoint& p, double scale, double stretchFactor)
{
	TPoint pt;
    if(scale > 0)
    {
    	pt.X = (p.X / scale) / stretchFactor;
	    pt.Y = (p.Y / scale) / stretchFactor;
    }
	return pt;
}


//---------------------------------------------------------------------------
void setupLogging()
{
	if(!folderExists(gAppDataLocation))
	{
		createFolder(gAppDataLocation);
	}

	string fullLogFileName(joinPath(gAppDataLocation, gLogFileName));
	clearFile(fullLogFileName);
	dsl::gLogger.logToFile(fullLogFileName);
	LogOutput::mShowLogLevel = true;
	LogOutput::mShowLogTime = false;
	LogOutput::mUseLogTabs = false;
	Log(lInfo) << "Logger was setup";
}

//---------------------------------------------------------------------------
void setupApplicationTheme()
{
	if(dsl::checkForCommandLineFlag("-Theme="))
	{
		string cmdLine = stdstr(GetCommandLineA());
		//User is changing the theme.
		//Parse the command line
		StringList paras(cmdLine,'-');

		//Create iniKeys for easy parsing
		for(int i = 0; i < paras.size(); i++)
		{
			string record = paras[i];
			IniKey aKey(record);
			if(aKey.mKey == "Theme")
			{
				 gApplicationStyle = aKey.mValue;
			}
		}
	}
	else
	{
		//Read from registry
		gApplicationStyle = readStringFromRegistry(gApplicationRegistryRoot, "", "Theme", "Windows");
	}

	if(gApplicationStyle.size())
	{
		try
		{
			if(gApplicationStyle != "Windows")
			{
				TStyleManager::TrySetStyle(gApplicationStyle.c_str());
			}
		}
		catch(...)
		{
			//Do nothing
		}
	}
}

int loadStyles()
{
	string themeFolder("themes");
	themeFolder = joinPath(getCWD(), themeFolder);
    int nrOfStyles(0);
	if(DirectoryExists(themeFolder.c_str()))
	{
		StringList list = getFilesInDir(themeFolder, "vsf");
		for(int i = 0; i < list.size(); i++)
		{
			string styleFile(list[i]);
			try
			{
				if(TStyleManager::IsValidStyle(vclstr(styleFile)))
				{
					TStyleManager::LoadFromFile(vclstr(styleFile));
                    nrOfStyles++;
				}
			}
			catch(...)
			{
				MessageDlg("Bad theme file", mtWarning, TMsgDlgButtons() << mbOK, 0);
			}
		}
	}
    return nrOfStyles;
}

BOOL CALLBACK FindOtherWindow(HWND hwnd, LPARAM lParam)
{
	static char buffer[50];
	GetWindowTextA(hwnd, buffer, 50);

	string wName(buffer);
	if(contains(buffer, gAppName))
	{
		// do something with hwnd here
		gOtherAppWindow = hwnd;
		return FALSE;
	}

	return TRUE;
}
