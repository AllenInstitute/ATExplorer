#ifndef atIFDataH
#define atIFDataH
#include "atData.h"
//---------------------------------------------------------------------------

class ATIFData : public ATData
{
    public:
                    					ATIFData(const Path& p, bool validate = false);
        virtual bool        			validate();

                                        //!Ribbonfolder functions..
		FileFolders                     getRibbonFolders();
        FileFolder*                     getRibbonFolder(int fldr);
        FileFolder*                     getRibbonsDataFolder();
        int                 			getNumberOfRibbonFolders();

		FileFolder*						getSessionFolder(FileFolder* ribbonFolder, int n);
		FileFolders						getSessionFolders(FileFolder* ribbonFolder);

   		FileFolder*                     getChannelFolder(FileFolder* sessionFolder, const string& channel);
   		FileFolders                     getChannelFolders(FileFolder* sessionFolder);

    protected:
        Path 							ribbonFolderSubPath;

};
#endif
