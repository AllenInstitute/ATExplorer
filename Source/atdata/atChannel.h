#ifndef atChannelH
#define atChannelH
#include "atExplorerObject.h"
#include "atTiles.h"
//---------------------------------------------------------------------------

namespace at
{

class Session;
//!A channel belong to a specific Session
class ATE_DATA Channel : public ExplorerObject
{
    public:
                                    Channel(const string& lbl, Session& s);
                                    ~Channel();
//        bool                        appendTile(TileSP t);
//        Tiles&          		    getTiles(){return mTiles;}
        string                      getLabel(){return mLabel;}

    protected:
        string                      mLabel;
        Session&                    mSession;
//        Tiles                       mTiles;
};

}


#endif
