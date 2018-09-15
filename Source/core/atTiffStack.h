#ifndef atTiffStackH
#define atTiffStackH
#include "atATExplorerProject.h"
#include <utility>
#include "Poco/Path.h"
#include "atRegionOfInterest.h"
#include "dslStringList.h"
//---------------------------------------------------------------------------
namespace at
{

using dsl::StringList;
using Poco::Path;
using std::pair;

class ATE_CORE TiffStack : public ATExplorerProject
{
    public:
                                        TiffStack(const string& fName, const Path& p);
                                        ~TiffStack();

        void                            setROI(const RegionOfInterest& roi);
        RegionOfInterest                getROI();

        void                            setIntensities(int min, int max);
        pair<int,int>                   getIntensities();

        void                            setSections(const StringList& s);
        StringList                      getSections();


        virtual dsl::XMLElement*        addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLElement* docRoot);
		virtual bool 					loadFromXML(dsl::XMLNode* node);
   		virtual bool 	   	            write();

    protected:
        string                          mFileName;
        Path                            mFilePath;
        RegionOfInterest                mROI;
        StringList                      mSections;
        int                             mMinIntensity;
        int                             mMaxIntensity;
};

}


#endif
