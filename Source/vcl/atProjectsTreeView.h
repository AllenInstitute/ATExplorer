#ifndef atProjectsTreeViewH
#define atProjectsTreeViewH
#include "atATObject.h"
#include <Vcl.Controls.hpp>
#include "dslProjects.h"
#include "dslObserver.h"
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

//!This class manages Projects viewable on a TreeView
//!The ProjectsTreeView is an observer of projects, that are 'subjects'
class PACKAGE ProjectsTreeView : public dsl::Observer, public ATObject
{
    public:
                                        ProjectsTreeView(TTreeView* tv);
                                        ~ProjectsTreeView();
        void                            updateRepresentation(Subject* s);
        Project*                       	getCurrent();
        Project*             			getFirst();
        Project*             			getNext();

                                        //!start observation of the project..
        TTreeNode*						addProjectToView(Project* project);

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
        TTreeNode*						addRenderProjectToView(ATExplorerProject* vcNode, RenderProject* rp);
        TTreeNode*						addATIFDataProjectToView(ATExplorerProject* vcNode, ATIFDataProject* rp);
        int                             mProjectCount();
        bool                            selectProject(Project* p);
        string                          closeProject(Project* p);
        bool	                        removeProject(Project* p);

        TTreeNode*                      getItemForProject(Project* p);
        void                            createView(Project* p);
        TTreeNode* 						addChildProjectToView(Project* parent, Project* child);
        void                            expandView(Project* p);
        TTreeView*                      getTreeView();

    protected:
                                        //The View
        TTreeView*                      mTree;

                                        //The model..
                                        //This container (ProjectsTreeView) is responsible to dispose of any projects
        Projects                        mProjects;
};

}

#endif
