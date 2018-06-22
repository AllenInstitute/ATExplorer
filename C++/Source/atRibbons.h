#ifndef atRibbonsH
#define atRibbonsH
#include "atATObject.h"
#include <vector>
#include "atRibbon.h"
//---------------------------------------------------------------------------

namespace at
{

using std::vector;

//!The Ribbons class is a container for AT Ribbons
class Ribbons : public std::vector<Ribbon*>, public ATObject
{

        public:
                            	Ribbons();
            virtual            	~Ribbons();
        	Ribbon*             getRibbon(int i){return this->at(i);}
            int                 count(){return this->size();}

        private:
            
};

}
#endif
