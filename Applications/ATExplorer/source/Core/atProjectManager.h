#ifndef atProjectManagerH
#define atProjectManagerH
#include <vector>
#include <string>
#include "dslConstants.h"
#include "atProjects.h"
//---------------------------------------------------------------------------


namespace at
{
using std::vector;
using std::string;

//!The project manager class manages projects.
//The onChange callback can be used to synch an External TreeView component
class ATExplorerProject;

class PACKAGE ProjectManager
{
	public:
    						                        ProjectManager();
 		virtual		 		                        ~ProjectManager();
        bool                                        closeProject(ATExplorerProject* p);
        bool                                        saveProject(ATExplorerProject* p);
        bool                                        saveProjectAs(ATExplorerProject* p);

        ATExplorerProject*							createNewProject(const string& projName = dsl::gEmptyString);
        bool                                        selectNone();
        bool										selectFirst();
        bool										selectNext();
        bool										selectPrevious();
        bool										selectLast();

		bool 										selectNode(ATExplorerProject* vcp);
        ATExplorerProject*							getCurrentProject();
        int                                         projectCount(){return mProjects.count();}

	private:
        Projects                                    mProjects;

};

}
#endif
