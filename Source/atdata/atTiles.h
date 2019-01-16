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
class Tile;
class Section;

//!A container for tiles.
//!Tiles are grouped by channel
typedef std::tr1::shared_ptr<Tile> TileSP;

class ATE_DATA Tiles : public ExplorerObject
{
    public:
                                    Tiles(const Channel& ch);
                                    ~Tiles();
        const Channel&              getChannel() const;
        int                         count();
        bool                        append(TileSP t);


    protected:
        const Channel&              mChannel;
        map<int, TileSP>  			mTiles;
};

}

#endif
