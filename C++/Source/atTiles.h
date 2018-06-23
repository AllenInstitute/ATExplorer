#ifndef atTilesH
#define atTilesH
#include "atATObject.h"
#include <map>
#include "atChannel.h"
//---------------------------------------------------------------------------

namespace at
{
using std::map;

class Tile;

//!A container for tiles.
//!Tiles are grouped by channel
class Tiles : public ATObject
{
    public:
                                    Tiles(const Session& s);
                                    ~Tiles();
        bool                        append(Tile* t);

    protected:
        const Session&              mSession;
        map<int, Channel>   		mTiles;
};

}

#endif
