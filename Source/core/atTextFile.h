#ifndef atTextFileH
#define atTextFileH
#include "atExplorerObject.h"
#include <string>
#include "dslConstants.h"
#include "dslSubject.h"
//---------------------------------------------------------------------------
namespace at
{

using std::string;
//!This class purpose is mainly for the representation of a
//!Text file in ATExplorers TreeView. Only ExplorerObjects can be
//stored in the Tree
class ATE_CORE TextFile : public ExplorerObject, public dsl::Subject
{
	public:
                                TextFile(const string& fName, const string& alias = dsl::gEmptyString);
                                ~TextFile();

        string                  getFileNameWithPath();
        string                  getAlias();
        void                    setAlias(const string& a);

    protected:
        string                  mFileNameWithPath;
                                //!The alias can be used for the label in the Tree. E.g. a
                                //statetable file name is statetable_ribbon_4_session_1_section_0
                                //Its alias may be R4-S1-S0
        string                  mAlias;
};

}

#endif
