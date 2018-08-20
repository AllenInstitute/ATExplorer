#ifndef atApplicationUtilitiesH
#define atApplicationUtilitiesH
#include "atExplorerCoreExporter.h"
#include "atATObject.h"
#include <windows.h>
#include <string>
//---------------------------------------------------------------------------

using std::string;
namespace at
{

class AT_E_CORE ApplicationUtilities : public ATObject
{
	public:
    			                            ApplicationUtilities(const string& appName, const string& regRoot, const string& appVersion);
    virtual 	                            ~ApplicationUtilities();
    HANDLE 		                            AppMutex;
	string	   	                            AppName;
	string	   	                            AppRegistryRoot;
    string		                            AppVersion;
    string		                            AppDataFolder;
    string 		                            LogFileName;
  	string		                            LogFileLocation;
  	string		                            Style;

    string                                  RestartMutexName;
    HWND                                    OtherAppWindow;
    bool       	                            AppIsStartingUp;
    bool       	                            AppIsClosing;

    void		                            init();
	bool		                            setupLogging();
	bool		                            closeLogFile();
	bool	                                otherInstanceIsRunning();
};

}

#endif
