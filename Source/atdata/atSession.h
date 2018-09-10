#ifndef atSessionH
#define atSessionH
#include "atExplorerObject.h"
#include "atChannel.h"
#include "atChannels.h"
#include "atTiles.h"
#include "atRibbon.h"
//---------------------------------------------------------------------------

namespace ate
{

class ATE_DATA Session : public ExplorerObject
{
        public:
                            Session(const string& lbl);//, Ribbon& r);
                            ~Session();
            string          getLabel(){return mLabel;}
            bool        	appendChannel(Channel* channel);
            Channels*       getChannels(){return &mChannels;}
            Channel*        getFirstChannel();
            Channel*        getNextChannel();
//            Ribbon*         getRibbon(){return &mRibbon;}

	protected:
            string          mLabel;
//            Ribbon&   		mRibbon;
            Channels        mChannels;
};

}

#endif
