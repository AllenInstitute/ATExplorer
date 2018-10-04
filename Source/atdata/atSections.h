#ifndef atSectionsH
#define atSectionsH
#include <vector>
#include "atExplorerObject.h"
#include "atATDataExporter.h"

using std::vector;

namespace at
{

class Section;
//!Sections is a container for individual AT "sections".
//!A Ribbon is a set of consecutive sections

//typedef shared_ptr<Section> SectionSP;
//---------------------------------------------------------------------------
class ATE_DATA Sections : public ExplorerObject
{
    public:
                                        Sections();
        virtual                         ~Sections();
        int                             count(){return mSections.size();}
        Section*                        getFirstSection();
        Section*                        getNextSection();
        Section*                        getPreviousSection();
        Section*                        getLastSection();
        Section*                        getSection(int sectionID);
        Section*                        at(unsigned int i);

    protected:
        vector<Section*>::iterator  	mSectionIterator;
        vector<Section*>                mSections;
};

}
#endif
