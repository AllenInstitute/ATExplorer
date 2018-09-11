#ifndef atSectionH
#define atSectionH
#include "atExplorerObject.h"
#include "atATDataExporter.h"
//---------------------------------------------------------------------------

namespace at
{

class Ribbon;
class Session;
class Channel;
class Tiles;

//!An atSection is part of a ribbon.
//!It may have some associated tiles
class ATE_DATA Section : public ExplorerObject
{
    public:
                                                    Section(int id, const Ribbon& r);
        virtual                                     ~Section();

        int                                         id() const{return mID;}
        Tiles&                                      getTiles(Channel& ch);

    protected:
        int                                         mID;
        const Ribbon&                               mRibbon;
};

}


#endif
