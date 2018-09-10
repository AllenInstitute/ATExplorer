#ifndef atTileH
#define atTileH
#include "atATObject.h"
#include "atChannel.h"
#include "Poco/Path.h"
//---------------------------------------------------------------------------
namespace at
{
class Section;
using Poco::Path;

//!A tile is a (TIFF) image (on disk), typically part of an imaged section
//A tile knows which section it belongs too, its id, its channel, and z-stack.
class AT_DATA Tile : public ATObject
{

        public:
                            Tile(Channel& c, Section& s, int tileID, const Path& p);
            virtual         ~Tile();

            bool            assignPath(Path& p, bool checkIfExists = false);
            int             getID(){return mID;}
            Path            getPath(){return mRawDataPath;}

        protected:
                            //!Assign from path
            int            	mID;

                            //!This will point to the tiles 'file'
            Path            mRawDataPath;

                            //!Any tile 'belong' to a section
                            //!and channel
            Section&        mSection;
            Channel&        mChannel;
};

}

#endif
