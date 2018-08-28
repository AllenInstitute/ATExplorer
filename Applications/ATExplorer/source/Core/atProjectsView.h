#ifndef atProjectsViewH
#define atProjectsViewH
#include "atATObject.h"
#include <Vcl.Controls.hpp>
#include "atProjects.h"
//---------------------------------------------------------------------------
namespace at
{

class ATExplorerProject;
class RenderProject;

//Rename this to ProjectTreeView
class ProjectsView : public ATObject
{

        public:
                                            ProjectsView(TTreeView* tv);
                                            ~ProjectsView();
            Project*                        getCurrent();
            Project*             			getFirst();
            Project*             			getNext();

			TTreeNode*						addProjectToView(Project* project);

                                            //!This function retraces the tree to the root project
            Project*			            getSelectedProject();

									        //!If selected item is a child, then its parent is returned
            Project*			            getParentForSelectedProject();

            ATExplorerProject*              createNewATExplorerProject();
            void                            selectLast();
			TTreeNode*						addRenderProjectToView(TTreeNode* vcNode, RenderProject* rp);
            int                             mProjectCount();
            bool                            selectProject(Project* p);
            string                          closeProject(Project* p);
            TTreeNode*                      getItemForProject(Project* p);
            void                            updateView(Project* p);
			TTreeNode* 						addChildProjectToView(Project* parent, Project* child);
            void                            expandView(Project* p);

        protected:

			TTreeView*                      mTree;
            Projects                        mProjects;
};

}

#endif
