#ifndef atProjectManagerH
#define atProjectManagerH
#include <vector>
#include <string>
#include <Vcl.ComCtrls.hpp>
#include "dslConstants.h"
//---------------------------------------------------------------------------
using std::vector;
using std::string;

//!The project manager class manages projects.
class ATExplorerProject;

class PACKAGE ProjectManager
{
	public:
    						                        ProjectManager(TTreeView& tv);
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
		bool 										selectItem(TTreeNode* item);
		bool 										selectNode(ATExplorerProject* vcp);
        ATExplorerProject*							getCurrentProject();
        int                                         projectCount(){return mATProjects.size();}

	private:
    	TTreeView*			                        ProjectTView;
        vector<ATExplorerProject*>			 		mATProjects;
		vector<ATExplorerProject*>::iterator		mCurrentProject;

};

#endif
