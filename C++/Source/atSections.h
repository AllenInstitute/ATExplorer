#ifndef atSectionsH
#define atSectionsH
#include "atATObject.h"
#include <vector>
#include "atSection.h"
using std::vector;

namespace at
{

class Ribbon;
//!Sections is a container for individual AT "sections". A Ribbon is a set of consecutive sections
//---------------------------------------------------------------------------
class Sections : public vector<Section*>, public ATObject
{

        public:
                                            Sections(const Ribbon& r);
            virtual                         ~Sections();
            int                             count(){return this->size();}
            Section*                        getFirstSection();
            Section*                        getNextSection();
            Section*                        getPreviousSection();
            Section*                        getLastSection();

        protected:
            const Ribbon&                   mRibbon;
        	vector<Section*>::iterator  	mSectionIterator;

        private:

};


}
#endif
