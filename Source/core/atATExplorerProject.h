#ifndef atATExplorerProjectH
#define atATExplorerProjectH
#include "dslProject.h"
#include "dslConstants.h"
#include "atExplorerObject.h"
#include <vector>
#include "dslSharedPointer.h"
#include "atExplorerCoreExporter.h"
//---------------------------------------------------------------------------

namespace tinyxml2
{
	class XMLElement;
}

namespace at
{

extern const string gATExplorerProjectFileVersion;

using dsl::shared_ptr;
using dsl::gEmptyString;

//!A render project is a project as exposed by Render
class RenderProject;
class ATIFDataProject;
class TiffStack;

//!We are using an enum for process type in order to save/retrieve different processes from XML
enum ATEObjectType
{
	ateBaseType = 0,
    ateATIFDataProject,
    ateRenderProject,
    ateTiffStack,
    ateUnknown
};

string 			toString(ATEObjectType tp);
ATEObjectType 	toATEObjectType(const string& str);

//!An ATExplorerProject captures (is a container) for renderprojects and other possible objects related to a project
//!in ATExplorer
//!An ATExplorerProject is the baseclass for such objects.
class ATE_CORE ATExplorerProject : public dsl::Project, public ExplorerObject
{
    public:
                                                ATExplorerProject(const string& projectName = gEmptyString);
        virtual                                 ~ATExplorerProject();

		virtual bool 							isModified();
        virtual bool                            save(const string& fName = dsl::gEmptyString);
        virtual bool                            open(const string& fName = dsl::gEmptyString);

        virtual bool							addChild(ATExplorerProject* child);

        string                                  getPresentXMLModelVersion();
        virtual dsl::XMLElement*           		addToXMLDocument(dsl::XMLDocument& doc, dsl::XMLNode* docRoot);
		virtual dsl::XMLElement*                addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLElement* node);

        virtual bool   							loadFromXML(dsl::XMLNode* node);

        ATEObjectType                           getProjectType();
		string 									getATEObjectTypeAsString();

        										//!Info text is used if the user want to document the purpose of
                                                //a particular process
        string									mInfoText;

    protected:
        bool                                    resetXML();
        int                                     loadATObjects();

                					            //!The ATObject type help us construct
                                                //a new AT object from a file
        ATEObjectType		  		            mATEObjectType;

        ATExplorerProject*			         	createATObject(tinyxml2::XMLElement* element);
		ATIFDataProject*	 					createATIFDataProject(tinyxml2::XMLElement* element);
		RenderProject*							createRenderProject(tinyxml2::XMLElement* element);
		TiffStack*								createTiffStackProject(tinyxml2::XMLElement* element);

};

}
#endif
