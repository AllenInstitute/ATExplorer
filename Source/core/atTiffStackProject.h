#ifndef atTiffStackProjectH
#define atTiffStackProjectH
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

//Metadata for a tiffstack
class ATE_CORE TiffStackProject : public ATExplorerProject
{
    public:
                                        TiffStackProject(const string& fName = "", const Path& p = "");
                                        TiffStackProject(const TiffStackProject& stack);
                                        ~TiffStackProject();
        string                          getInfo();
		virtual bool                    deleteData();
        void                            setFilePath(const Path& p);
        Path                            getFilePath();

        void                            setROI(const RegionOfInterest& roi);
        RegionOfInterest                getROI();

        void                            setIntensities(int min, int max);
        pair<int,int>                   getIntensities();

        void                            setSections(const StringList& s);
        StringList                      getSections();

        void                            appendChannel(const string& ch);
        void                            setChannels(const StringList& chs);
        StringList                      getChannels();

        void                            reset();

        virtual dsl::XMLElement*        addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLElement* docRoot);
		virtual bool 					loadFromXML(dsl::XMLNode* node);
   		virtual bool 	   	            write();

    protected:
        Path                            mFilePath;
        RegionOfInterest                mROI;
        StringList                      mSections;
        int                             mMinIntensity;
        int                             mMaxIntensity;
        StringList                  	mChannels;
};

}


#endif
