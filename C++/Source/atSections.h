#ifndef atSectionsH
#define atSectionsH
#include "atATObject.h"
#include <vector>
#include "atSection.h"
using std::vector;

namespace at
{
//!Sections is a container for individual AT "sections". A Ribbon is a set of consecutive sections
//---------------------------------------------------------------------------
class Sections : public vector<Section>, public ATObject
{

        public:
                            Sections();
                            ~Sections();
            int             count(){return this->size();}

        protected:

        private:

};

Sections::Sections()
{}

Sections::~Sections()
{}

}
#endif
