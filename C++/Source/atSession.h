#ifndef atSessionH
#define atSessionH
#include "atATObject.h"
#include "atChannel.h"
#include "atChannels.h"
#include "atTiles.h"
#include "atRibbon.h"
//---------------------------------------------------------------------------

namespace at
{

class Session : public ATObject
{
        public:
                            Session(const string& lbl, Ribbon& r);
                            ~Session();
            bool        	appendChannel(const Channel& channel);
            Channels        getChannels(){return mChannels;}

        protected:
            string          mLabel;
            Ribbon&   		mRibbon;
            Channels        mChannels;
            Tiles           mTiles;
};

}

#endif
