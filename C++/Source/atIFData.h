#ifndef atIFDataH
#define atIFDataH
#include "atData.h"
//---------------------------------------------------------------------------

class ATIFData : public ATData
{
    public:
                    					ATIFData(const Path& p);
        virtual bool        			validate();
        int                 			getNumberOfRibbons();
        FileFolder                      getRibbonFolder(int fldr);

    protected:
        FileFolder				 		mRibbonFolders;

};
#endif
