#ifndef atSectionH
#define atSectionH
#include "atATObject.h"
#include <list>
#include "atTile.h"
//---------------------------------------------------------------------------

namespace at
{
using std::list;
class Tile;
//!An atSection is a list of tiles
class Section : public list<Tile>, public ATObject
{

        public:
                            Section();
                            ~Section();

        protected:

        private:

};

}


#endif
