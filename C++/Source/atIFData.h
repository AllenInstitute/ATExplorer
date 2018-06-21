#ifndef atIFDataH
#define atIFDataH
#include "atData.h"
//---------------------------------------------------------------------------

namespace at
{

//!The ATIFData class maps the dataformats used in Smith Lab..
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

		FileFolder*						getSessionFolder(FileFolder* ribbonFolder, int n);
		FileFolders						getSessionFolders(FileFolder* ribbonFolder);

   		FileFolder*          			getChannelFolder(FileFolder* sessionFolder, const string& channel);
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
