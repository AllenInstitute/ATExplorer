#ifndef atTilesH
#define atTilesH
#include "atExplorerObject.h"
#include "atATDataExporter.h"
#include <map>
#include "Poco/Path.h"
#include "dslSharedPointer.h"
#include "atChannel.h"
//---------------------------------------------------------------------------

namespace at
{

using std::map;
using dsl::shared_ptr;
class Tile;
class Section;

//!A container for tiles.
//!Tiles are grouped by channel
typedef shared_ptr<Tile> TileSP;


class ATE_DATA Tiles : public ExplorerObject
{
    public:
                                    Tiles(const Channel& ch);
                                    ~Tiles();
        const Channel&              getChannel(){return mChannel;}
        bool                        append(TileSP t);
        int                         count(){return mTiles.size();}

    protected:
        const Channel&              mChannel;
        map<int, TileSP>  			mTiles;

};

}

#endif
