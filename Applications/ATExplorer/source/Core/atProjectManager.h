#ifndef atProjectManagerH
#define atProjectManagerH
#include <vector>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
using std::vector;

//!The project manager class manages projects.
class ATExplorerProject;

namespace Vcl
{
	namespace Comctrls
	{
		class TTreeView;
        class TTreeNode;
    }
}

using Vcl::Comctrls::TTreeView;
using Vcl::Comctrls::TTreeNode;

class PACKAGE ProjectManager
{
	public:
    						                        ProjectManager(TTreeView& tv);
 		virtual		 		                        ~ProjectManager();
        bool										createNewProject();
        bool										selectFirst();
        bool										selectNext();
        bool										selectPrevious();
        bool										selectLast();
		bool 										selectItem(TTreeNode* item);
		bool 										selectNode(ATExplorerProject* vcp);
        ATExplorerProject*						getCurrentProject();

	private:
    	TTreeView*			                        ProjectTView;
        vector<ATExplorerProject*>			 	mVCProjects;
		vector<ATExplorerProject*>::iterator		mCurrentVCProject;

};

#endif
