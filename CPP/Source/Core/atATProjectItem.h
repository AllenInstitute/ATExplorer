#ifndef atATProjectItemH
#define atATProjectItemH
#include "atExplorerCoreExporter.h"
#include "atATObject.h"
#include "dslProject.h"
#include "dslConstants.h"
#include "atATObject.h"
#include "atATProjectItems.h"
#include <vector>
//---------------------------------------------------------------------------

namespace at
{

extern const string gATProjectFileVersion;
using namespace std;
using dsl::gEmptyString;


class RenderProjectItem;
class ATDataProjectItem;

//!We are using an enum for process type in order to save/retrieve different processes from XML
enum ATProjectItemType
{
	atpATProjectItem = 0,
    atpRenderProjectItem,
	atpATDataProjectItem,
    atpVolumeProjectItem,
    atpUnknownProjectItem
};

string 					toString(ATProjectItemType tp);
ATProjectItemType 		toATProjectItemType(const string& str);


//!A ATProject captures (is a container) for renderprojects and other possible objects related to a project
//!in a ATExplorer UI
//!ATProject is the baseclass for such objects.

class AT_E_CORE ATProjectItem : public dsl::Project, public ATObject
{

    public:

//			                                    ATProjectItem(ATProjectItemType type);
                                                ATProjectItem(const string& projectName = gEmptyString);
                                                ~ATProjectItem();

		virtual bool 							isModified();
        virtual bool                            save(const string& fName = dsl::gEmptyString);
        virtual bool                            open(const string& fName = dsl::gEmptyString);
        virtual bool							addChild(ProjItemPtr child);
        virtual bool							addProjectObject(ATObject* child);

		string 									getATObjectTypeAsString();

        										//!Info text is used if the user want to document the purpose of
                                                //a particular process
        string									mInfoText;
        int										getNumberOfChilds();
        ProjItemPtr								getChild(int i);

    protected:
        bool                                    resetXML();
        int                                     createProjectObjects();

                					            //!The VCObject type help us construct
                                                //a new VC object from a file
        ATProjectItemType		  		        mATProjectItemType;

        ProjItemPtr			       				createATProjectItem(tinyxml2::XMLElement* element);
		ProjItemPtr				 				createRenderProjectItem(tinyxml2::XMLElement* 	element);
		ProjItemPtr								createATDataProjectItem(tinyxml2::XMLElement* 	element);

        										//!Childs can be various types of objecs, e.g. renderprojects and volumes, ATData
        ATProjectItems							mItems;
        string                                  getPresentXMLModelVersion();
        virtual dsl::XMLElement*           		addToXMLDocument(dsl::XMLDocument& doc, dsl::XMLNode* docRoot);
		virtual dsl::XMLElement*                addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLNode* node);
        virtual bool   							createProjectFromXML(dsl::XMLNode* node);
};

}
#endif
