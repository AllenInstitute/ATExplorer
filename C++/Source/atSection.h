#ifndef atSectionH
#define atSectionH
#include "atATObject.h"
#include <list>
#include "atTile.h"
//---------------------------------------------------------------------------

namespace at
{
using std::list;

class Ribbon;
class Session;
class Tiles;

//!An atSection is part of a ribbon.
//!It may have some associated tiles
class Section : public ATObject
{
    public:
                        Section(int id, const Ribbon& r);
        virtual         ~Section();

        int             id() const{return mID;}
        int             getNumberOfTiles() const;

        Tiles           getTiles(Session& session, Channel& ch);


    protected:
        int             mID;
        const Ribbon&   mRibbon;



    private:

};

}


#endif
