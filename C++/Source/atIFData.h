#ifndef atIFDataH
#define atIFDataH
#include "atData.h"
//---------------------------------------------------------------------------

namespace at
{

//!The ATIFData class maps the dataformats used in Smith Lab..
//!Some assumptions:
//!		Number of sections, for a particular ribbon, are equal across channels(sessions)
//!     A section do always belong to a ribbon

class ATIFData : public ATData
{
    public:
                    					ATIFData(const Path& p, bool populate = false);
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
                                	    //!Basepath of raw data. All IF data need to be accesible
                            	        //below this folder
        Path	     			        mBasePath;
        Path 							mRibbonsFolderPath;
        FileFolder				        mRibbonsDataFolder;
        FileFolder   	    			mProcessedDataFolder;
        FileFolder	        			mScriptsDataFolder;
};
}
#endif
