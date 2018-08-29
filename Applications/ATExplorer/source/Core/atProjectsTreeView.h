#ifndef atProjectsTreeViewH
#define atProjectsTreeViewH
#include "atATObject.h"
#include <Vcl.Controls.hpp>
#include "dslProjects.h"
//---------------------------------------------------------------------------
namespace at
{

using dsl::Project;
using dsl::Projects;

class ATExplorerProject;
class RenderProject;

//Rename this to ProjectTreeView
class ProjectsTreeView : public ATObject
{
        public:
                                            ProjectsTreeView(TTreeView* tv);
                                            ~ProjectsTreeView();
            Project*                       	getCurrent();
            Project*             			getFirst();
            Project*             			getNext();

			TTreeNode*						addProjectToView(Project* project);

                                            //!This function returns the root project
            Project*			            getRootForSelectedProject();

                                            //!This function returns currently selected (sub)project
            Project*			            getSelectedProject();

									        //!If selected item is a child, then its parent is returned
            Project*			            getParentForSelectedProject();

            ATExplorerProject*			   	createNewATExplorerProject();
            void                            selectLast();
			TTreeNode*						addRenderProjectToView(ATExplorerProject* vcNode, RenderProject* rp);
            int                             mProjectCount();
            bool                            selectProject(Project* p);
            string                          closeProject(Project* p);
            bool	                        removeProject(Project* p);

            TTreeNode*                      getItemForProject(Project* p);
            void                            updateView(Project* p);
			TTreeNode* 						addChildProjectToView(Project* parent, Project* child);
            void                            expandView(Project* p);

        protected:
                                            //The View
			TTreeView*                      mTree;

                                            //The model..
                                            //This container is responsible to dispose of any projects
            Projects                        mProjects;
};

}

#endif
