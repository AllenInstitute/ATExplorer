#ifndef atATProjectH
#define atATProjectH
#include "atExplorerCoreExporter.h"
#include "atATObject.h"
#include "dslProject.h"
#include "dslConstants.h"
#include "core/atATObject.h"
#include <vector>
//---------------------------------------------------------------------------

namespace at
{

extern const string gATProjectFileVersion;
using namespace std;
using dsl::gEmptyString;

//!A render project is a project as exposed by Render
class RenderProject;

//!We are using an enum for process type in order to save/retrieve different processes from XML
enum ATProjectObjectType
{
	atpBaseType = 0,
    atpRenderProject,
	atpATDataProjectObject,
    atpVolume,
    atpUnknown
};

string 					toString(ATProjectObjectType tp);
ATProjectObjectType 	toATProjectObjectType(const string& str);


//!A ATProject captures (is a container) for renderprojects and other possible objects related to a project
//!in a ATExplorer UI
//!ATProject is the baseclass for such objects.

class AT_E_CORE ATProject : public dsl::Project, public ATObject
{

    public:

			                                    ATProject(ATProjectObjectType type);
                                                ATProject(const string& projectName = gEmptyString);
                                                ~ATProject();

		virtual bool 							isModified();
        virtual bool                            save(const string& fName = dsl::gEmptyString);

        virtual bool                            open(const string& fName = dsl::gEmptyString);

        virtual bool							addChild(ATProject* child);
        virtual bool							addProjectObject(ATObject* child);


		string 									getATObjectTypeAsString();

        										//!Info text is used if the user want to document the purpose of
                                                //a particular process
        string									mInfoText;
        int										getNumberOfChilds();
        ATProject*								getChild(int i);

    protected:
        bool                                    resetXML();
        int                                     createProjectObjects();

                					            //!The VCObject type help us construct
                                                //a new VC object from a file
        ATProjectObjectType		  		        mATProjectObjectType;

        ATProjectItem*		           			createATProjectItem(tinyxml2::XMLElement* element);
		RenderProjectItem*		 				createRenderProjectItem(tinyxml2::XMLElement* 	element);
		ATDataProjectItem*						createATDataProjectItem(tinyxml2::XMLElement* 	element);

        										//!Childs can be various types of objecs, e.g. renderprojects and volumes, ATData
        vector<ATProject*>						mChilds;
        string                                  getPresentXMLModelVersion();
        virtual dsl::XMLElement*           		addToXMLDocument(dsl::XMLDocument& doc, dsl::XMLNode* docRoot);
		virtual dsl::XMLElement*                addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLNode* node);
        virtual bool   							createProjectFromXML(dsl::XMLNode* node);
};

}
#endif
