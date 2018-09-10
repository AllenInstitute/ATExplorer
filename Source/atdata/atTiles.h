#ifndef atTilesH
#define atTilesH
#include "atExplorerObject.h"
#include "atATDataExporter.h"
#include <map>
#include "Poco/Path.h"
//---------------------------------------------------------------------------

namespace ate
{

using std::map;
using Poco::Path;
class Tile;
class Channel;


//!A container for tiles.
//!Tiles are grouped by channel
class ATE_DATA Tiles : public ExplorerObject
{
    public:
                                    Tiles(const Channel& s);
                                    ~Tiles();
        bool                        append(Tile* t);
        int                         count(){return mTiles.size();}

    protected:
        const Channel*		        mChannel;
        map<int, Tile*>  			mTiles;
};

}

#endif
