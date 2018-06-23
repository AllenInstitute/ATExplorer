#ifndef atRibbonH
#define atRibbonH
#include "atATObject.h"
#include "atSections.h"
//---------------------------------------------------------------------------

namespace at
{

//!The ribbon class abstracts a AT Ribbon..
//!A Ribbon is a bunch of consecutive sections
class Ribbon : public Sections
{
        public:
                            Ribbon(int id, const string& alias = "");
            virtual         ~Ribbon();
            bool            clear();

        	int             sectionCount();
            void            appendSection(Section* sec);

        protected:

                            //!Within a data set, each ribbon have a short and long ID
            int             mShortRibbonID;

                            //!This id is generated by the microtome and logged in ATDB
            string          mLongRibbonID;

                            //!Alias can be used to refer original data folders, names etc..
            string          mAlias;
};

}


#endif
