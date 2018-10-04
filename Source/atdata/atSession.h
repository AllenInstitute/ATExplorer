#ifndef atSessionH
#define atSessionH
#include "atExplorerObject.h"
#include "atChannel.h"
#include "atChannels.h"
#include "atTiles.h"
#include "atRibbon.h"
//---------------------------------------------------------------------------

namespace at
{

class ATE_DATA Session : public ExplorerObject
{
        public:
                            Session(const string& lbl);
                            ~Session();
            string          getLabel(){return mLabel;}
            bool        	appendChannel(Channel* channel);
            Channels*       getChannels(){return &mChannels;}
            Channel*        getFirstChannel();
            Channel*        getNextChannel();

	protected:
            string          mLabel;
            Channels        mChannels;
};

}

#endif
