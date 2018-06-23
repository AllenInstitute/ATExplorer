#ifndef atChannelH
#define atChannelH
#include "atATObject.h"
//---------------------------------------------------------------------------

namespace at
{

class Tile;
class Session;

class Channel : public ATObject
{

        public:
                                        Channel(Session& s, const string& lbl);
                                        ~Channel();
//                                        Channel(const Channel& c);
//            Channel&                    operator=(const Channel& rhs);

        protected:
            string                      mLabel;
            Session&     		       	mSession;

};

}


#endif
