#ifndef atUtilitiesH
#define atUtilitiesH
#include <Vcl.ComCtrls.hpp>
#include <string>
//---------------------------------------------------------------------------

using std::string;

PACKAGE double 			getCurrentImageWidth(TImage* img);
PACKAGE double 			getCurrentImageHeight(TImage* img);
PACKAGE TTabSheet*      getTabWithCaption(const string& c, TPageControl* pc);


#endif
