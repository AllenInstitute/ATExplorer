#ifndef atIFDataH
#define atIFDataH
#include "atData.h"
//---------------------------------------------------------------------------

class ATIFData : public ATData
{
    public:
                    					ATIFData(const Path& p, bool validate = false);
        virtual bool        			validate();
		FileFolders                     getRibbonFolders();
        FileFolder*                     getRibbonFolder(int fldr);
        int                 			getNumberOfRibbonFolders();

		FileFolders						getSessionFolders(int fldr);
		FileFolders						getSessionFolders(FileFolder* ribbonFolder);
   		FileFolders                     getChannelFolders(FileFolder* sessionFolder);

    protected:


};
#endif
