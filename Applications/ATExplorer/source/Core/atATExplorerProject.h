#ifndef atATExplorerProjectH
#define atATExplorerProjectH
#include "arraybot/atABExporter.h"
#include "dslProject.h"
#include "dslConstants.h"
#include "core/atATObject.h"
#include <vector>

//---------------------------------------------------------------------------
extern const string gATExplorerProjectFileVersion;
namespace tinyxml2
{
	class XMLElement;
}

using namespace std;
using dsl::gEmptyString;
//!A render project is a project as exposed by Render
class RenderProject;

//!We are using an enum for process type in order to save/retrieve different processes from XML
enum VCObjectType
{
	vcoBaseType = 0,
    vcoRenderProject,
    vcoVolume,
    vcoUnknown
};

string 			toString(VCObjectType tp);
VCObjectType 	toVCObjectType(const string& str);

//!A ATExplorerProject captures (is a container) for renderprojects and other possible objects related to a project
//!in volume creator
//!A ATExplorerProject is the baseclass for such objects.
class ATExplorerProject : public dsl::Project, public ATObject
{

    public:
                                                ATExplorerProject(const string& projectName = gEmptyString);
                                                ~ATExplorerProject();

		virtual bool 							isModified();
        virtual bool                            save(const string& fName = dsl::gEmptyString);
        virtual bool                            open();

        virtual bool							addChild(ATExplorerProject* child);

        string                                  getPresentXMLModelVersion();
        virtual dsl::XMLElement*           		addToXMLDocument(dsl::XMLDocument& doc, dsl::XMLNode* docRoot);
		virtual dsl::XMLElement*                addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLNode* node);

        virtual bool   							loadFromXML(dsl::XMLNode* node);

		string 									getVCObjectTypeAsString();

        										//!Info text is used if the user want to document the purpose of
                                                //a particular process
        string									mInfoText;

        int										getNumberOfChilds();
        ATExplorerProject*					getChild(int i);

    protected:
        bool                                    resetXML();
        int                                     loadVCObjects();

                					            //!The VCObject type help us construct
                                                //a new VC object from a file
        VCObjectType		  		            mVCObjectType;

        ATExplorerProject*		            createVCObject(tinyxml2::XMLElement* element);
		RenderProject*							createRenderProject(tinyxml2::XMLElement* element);

        										//!Childs can be various types of objecs, e.g. renderprojects and volumes
        vector<ATExplorerProject*>			mChilds;

};

#endif