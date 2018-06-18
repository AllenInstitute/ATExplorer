#ifndef atIFDataH
#define atIFDataH
#include "atData.h"
//---------------------------------------------------------------------------

class ATIFData : public ATData
{
    public:
                    					ATIFData(const Path& p, bool validate = false);
        virtual bool        			validate();
        int                 			getNumberOfRibbonFolders();
        FileFolder                      getRibbonFolder(int fldr);

    protected:


};
#endif
