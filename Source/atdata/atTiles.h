#ifndef atTilesH
#define atTilesH
#include "atExplorerObject.h"
#include "atATDataExporter.h"
#include <map>
#include "Poco/Path.h"
#include "dslSharedPointer.h"
//---------------------------------------------------------------------------

namespace at
{

using std::map;
using dsl::shared_ptr;
class Tile;
class Channel;

//!A container for tiles.
//!Tiles are grouped by channel
typedef shared_ptr<Tile> TileSP;
class ATE_DATA Tiles : public ExplorerObject
{
    public:
                                    Tiles(const Channel& s);
                                    ~Tiles();
        bool                        append(TileSP t);
        int                         count(){return mTiles.size();}

    protected:
        const Channel*		        mChannel;
        map<int, TileSP>  			mTiles;
};

}

#endif
