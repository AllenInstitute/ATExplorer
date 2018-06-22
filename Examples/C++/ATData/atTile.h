#ifndef atTileH
#define atTileH
#include "atATObject.h"
#include "atChannel.h"
//---------------------------------------------------------------------------
namespace at
{
class Section;

//!A tile is a (TIFF) image, typically part of an imaged section
//A tile knows which section it belongs too, its id, and z-stack.
class Tile : public ATObject
{

        public:
                            Tile(int id, Section& s, Channel& c);
            virtual         ~Tile();

            int             getID(){return mID;}

        protected:
            int            	mID;

                            //!Any tile 'belong' to a section
            Section&        mSection;
            Channel&        mChannel;
};

}

#endif
