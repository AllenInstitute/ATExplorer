#pragma hdrstop
#include "atApplicationUtilities.h"
#include <Shlobj.h>
#include "dslUtils.h"
#include "dslFileUtils.h"
#include "dslLogger.h"
#include "atExceptions.h"
#include "dslWin32Utils.h"
#include "dslVCLUtils.h"

#pragma package(smart_init)

using namespace dsl;
using namespace at;

int __stdcall FindOtherWindow(HWND hwnd, LPARAM lParam);

//---------------------------------------------------------------------------
ApplicationUtilities::ApplicationUtilities(const string& appName, const string& regRoot, const string& appVersion)
:
AppMutex(NULL),
AppName(appName),
AppVersion(appVersion),
AppRegistryRoot(joinPath(regRoot, appVersion)),
LogFileName(AppName + ".log"),
AppDataFolder(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), AppName)),
LogFileLocation(AppDataFolder),
RestartMutexName(AppName + "RestartMutex"),
OtherAppWindow(NULL),
AppIsStartingUp(true),
AppIsClosing(false),
Style("Glow")
{
}

ApplicationUtilities::~ApplicationUtilities()
{
    closeLogFile();
}

void ApplicationUtilities::init()
{
    string appMutexName = string(AppName + "Mutex").c_str();
    AppMutex = ::CreateMutexA(NULL, FALSE, appMutexName.c_str());
    if(GetLastError() == ERROR_ALREADY_EXISTS)
    {
    	throw(ATException("Application \"" + AppName + "\" is already running!"));
    }

    setupLogging();

     try
     {
        Style = readStringFromRegistry(AppRegistryRoot, "", "Theme",  Style);
    	TStyleManager::TrySetStyle(Style.c_str());
   	   	TStyleManager::SetStyle(Style.c_str());
     }
     catch(...)
     {
     }

}

bool ApplicationUtilities::setupLogging()
{
	if(!folderExists(LogFileLocation))
	{
		createFolder(LogFileLocation);
	}

	string fullLogFileName(joinPath(LogFileLocation, LogFileName));
	clearFile(fullLogFileName);
	dsl::gLogger.logToFile(fullLogFileName);
    dsl::gLogger.setLogLevel(lDebug5);
	LogOutput::mShowLogLevel = true;
	LogOutput::mShowLogTime = true;
	LogOutput::mUseLogTabs 	= true;
	Log(lInfo) << "Logger was setup";
    return true;
}

bool ApplicationUtilities::closeLogFile()
{
    dsl::gLogger.closeLogFile();
    return true;
}
