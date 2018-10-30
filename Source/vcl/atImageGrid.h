#ifndef atImageGridH
#define atImageGridH
#include "atExplorerObject.h"
#include <VCL.ExtCtrls.hpp>
//---------------------------------------------------------------------------

namespace at
{

class PACKAGE ImageGrid : public ExplorerObject
{
    public:
                            ImageGrid(TImage* img, TCanvas* canvas);
                            ~ImageGrid();
        void                paint();
        void                hide();

    protected:
        TImage*				mImage;
        TCanvas*            mCanvas;
};
}

#endif
