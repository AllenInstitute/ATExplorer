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
        virtual void                    reset();
        virtual bool        			validate();
        virtual bool                    populate();

                                        //!Ribbonfolder functions..
		FileFolders                     getRibbonFolders();
        FileFolderSP					getRibbonFolder(int fldr);
        FileFolderSP 	       			getRibbonsDataFolder();
        int                 			getNumberOfRibbonFolders();

		FileFolders						getSessionFolders(FileFolderSP ribbonFolder);
   		FileFolders                     getChannelFolders(FileFolderSP sessionFolder);

    protected:
        Path 							mRibbonsFolderPath;
        FileFolderSP			        mRibbonsDataFolder;
        FileFolderSP   	    			mProcessedDataFolder;
        FileFolderSP        			mScriptsDataFolder;
        bool                            populateRibbons();
        bool                            populateSessions();
};
}
#endif
