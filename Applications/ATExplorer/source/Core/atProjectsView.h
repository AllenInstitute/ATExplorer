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
class ProjectsView : public ATObject
{

        public:
                                            ProjectsView(TTreeView* tv);
                                            ~ProjectsView();
            Project*                        getCurrent();
            Project*             			getFirst();
            Project*             			getNext();

            Project*			            getSelectedProject();
            ATExplorerProject*              createNewATExplorerProject();
            void                            selectLast();
			TTreeNode*						addRenderProjectToView(TTreeNode* vcNode, RenderProject* rp);
            int                             mProjectCount();
            bool                            selectProject(Project* p);
            bool                            closeProject(Project* p);
            TTreeNode*                      getItemForProject(Project* p);
            void                            updateView(Project* p);

        protected:
			TTreeNode*						addProjectToView(Project* project);
			TTreeView*                      mTree;
            Projects                        mProjects;
};

}

#endif
