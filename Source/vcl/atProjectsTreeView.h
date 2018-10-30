#ifndef atProjectsTreeViewH
#define atProjectsTreeViewH
#include "atExplorerObject.h"
#include <Vcl.Controls.hpp>
#include "dslProjects.h"
#include "dslObserver.h"
#include "atTreeItemObservers.h"
//---------------------------------------------------------------------------
namespace at
{

using dsl::Project;
using dsl::Projects;
using dsl::Subject;
using dsl::SubjectEvent;
class ATExplorerProject;
class RenderProject;
class ATIFDataProject;
class Ribbon;
class Section;
class Session;
class Channel;

//!This class manages Projects viewable on a TreeView
//!The ProjectsTreeView is an observer of projects, that are 'subjects'
class PACKAGE ProjectsTreeView : public dsl::Observer, public ExplorerObject
{
    public:
                                        ProjectsTreeView(TTreeView& tv, TreeItemObservers& v);
                                        ~ProjectsTreeView();

        bool                            handleNodeClick(TTreeNode* node, bool isDoubleClick);

                                        //!The update representation updates a subjects rep
        void                            updateRepresentation(Subject* s);
        Project*                       	getCurrent();
        Project*             			getFirst();
        Project*             			getNext();

                                        //!start observation of the project..
        TTreeNode*						addProjectToTree(Project* project);
        TTreeNode* 						addChildProjectToTree(Project* parent, Project* child);

        virtual void                    update(Subject* theChangedSubject, SubjectEvent se = dsl::Ping);
                                        //!This function returns the root project
        Project*			            getRootForSelectedProject();

                                        //!This function returns currently selected (sub)project
        Project*			            getSelectedProject();

                                        //!This function returns currently selected (sub)project
        TTreeNode*			            getSelectedNode();

                                        //!If selected item is a child, then its parent is returned
        Project*			            getParentForSelectedProject();

        ATExplorerProject*			   	createNewATExplorerProject();
        void                            selectLast();
        TTreeNode*						addProjectToTreeView(ATExplorerProject* vcNode, Project* rp);
//        TTreeNode*						addATIFDataProjectToTreeView(ATExplorerProject* vcNode, ATIFDataProject* rp);
        int                             mProjectCount();
        bool                            selectProject(Project* p);
        string                          closeProject(Project* p);
        bool	                        removeSubProject(Project* p);

        TTreeNode*                      getTreeNodeForProject(Project* p);

        void                            createTreeViewNodes(Project* p);

        ProjectItemTabbedView*              createTabbedView(Project* p);
        void                            expandView(Project* p);
        const TTreeView*                getTreeView();

    protected:
                                        //The Tree View
        TTreeView&                      mTree;
        TreeItemObservers&              mViews;

                                        //The model..
                                        //This container (ProjectsTreeView) is responsible to dispose of any projects
        Projects                        mProjects;
		bool							handleClick(RenderProject* o, bool isDoubleClick);
		bool							handleClick(ATIFDataProject* o, bool isDoubleClick);
		bool 							handleClick(ATExplorerProject* o, bool isDoubleClick);
		bool							handleClick(Ribbon*  o, bool isDoubleClick);
		bool							handleClick(Section* o, bool isDoubleClick);
		bool							handleClick(Session* o, bool isDoubleClick);
		bool							handleClick(Channel* o, bool isDoubleClick);
};

}

#endif
