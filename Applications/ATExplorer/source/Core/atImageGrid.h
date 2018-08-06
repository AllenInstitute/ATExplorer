#ifndef atImageGridH
#define atImageGridH
#include "atATObject.h"
#include <VCL.ExtCtrls.hpp>
//---------------------------------------------------------------------------

//namespace Vcl
//{
//namespace Extctrls
//{
//
//    class TImage;
//}
//}
//
//namespace Vcl
//{
//namespace Graphics
//{
//
//    class TCanvas;
//
//}
//}
//

namespace at
{

//using Vcl::Extctrls::TImage;
//using Vcl::Graphics::TCanvas;

class ImageGrid : public ATObject
{

        public:
                                ImageGrid(TImage* img, TCanvas* canvas);
                                ~ImageGrid();
            void                paint();
            void                hide();

        protected:
			TImage*				mImage;
        	TCanvas*             mCanvas;

};

}


#endif
