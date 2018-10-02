#ifndef atATIFDataH
#define atATIFDataH
#include "atATData.h"
//---------------------------------------------------------------------------

namespace at
{

//!The ATIFData class maps the dataformats used in Smith Lab..
//!Some assumptions:
//!Number of tiles for a particular section, for a particular ribbon, are equal across channels(sessions)
//!A section do always belong to a ribbon

class ATE_DATA ATIFData : public ATData
{
    public:
                    					ATIFData(const string& basePath,	bool populate = false);
                    					ATIFData(const Path&   basePath, 	bool populate = false);
		ATDataFileFormat            	getFileFormat();
        virtual bool        			validate();
        virtual bool                    populate();

                                        //!Ribbonfolder functions..
		FileFolders                     getRibbonFolders();
        FileFolder* 					getRibbonFolder(int fldr);
        FileFolder*          			getRibbonsDataFolder();
        int                 			getNumberOfRibbonFolders();

		FileFolders						getSessionFolders(FileFolder* ribbonFolder);
   		FileFolders                     getChannelFolders(FileFolder* sessionFolder);

    protected:
        Path 							mRibbonsFolderPath;
        FileFolder				        mRibbonsDataFolder;
        FileFolder   	    			mProcessedDataFolder;
        FileFolder	        			mScriptsDataFolder;
        bool                            populateRibbons();
        bool                            populateSessions();
};
}
#endif
