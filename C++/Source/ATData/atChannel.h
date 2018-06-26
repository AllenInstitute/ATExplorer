#ifndef atChannelH
#define atChannelH
#include "atATObject.h"
#include "atTiles.h"
//---------------------------------------------------------------------------

namespace at
{

class Session;
class ATDATA Channel : public ATObject
{

        public:
                                        Channel(const string& lbl, Session* s);
                                        ~Channel();
            bool                        appendTile(Tile* t);
            Tiles&          		    getTiles(){return mTiles;}
            string                      getLabel(){return mLabel;}
        protected:
            string                      mLabel;
            Session*                    mSession;
            Tiles                       mTiles;
};

}


#endif
