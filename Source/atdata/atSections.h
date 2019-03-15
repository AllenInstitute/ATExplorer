#ifndef atSectionsH
#define atSectionsH
#include <vector>
#include "atExplorerObject.h"
#include "atATDataExporter.h"
#include "dslSharedPointer.h"
using std::vector;

namespace at
{

class Section;
//!Sections is a container for individual AT "sections".
//!A Ribbon is a set of consecutive sections

typedef std::shared_ptr<Section> SectionSP;
//---------------------------------------------------------------------------
class ATE_DATA Sections : public ExplorerObject
{
    public:
                                                        Sections();
        virtual                                         ~Sections();
	    virtual string 	    				    		getTypeName() const;
        int                                             count(){return mSections.size();}
        virtual void                                    clear();
        SectionSP                                       getFirstSection();
        SectionSP                                       getNextSection();
        SectionSP                                       getPreviousSection();
        SectionSP                                       getLastSection();
        SectionSP                                       getSection(int sectionID);
        SectionSP                                       at(unsigned int i);

    protected:
        vector<SectionSP>::iterator  	                mSectionIterator;
        vector<SectionSP>                               mSections;
};

}
#endif
