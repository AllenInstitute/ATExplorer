#ifndef atVCLUtils2H
#define atVCLUtils2H
#include <Vcl.ComCtrls.hpp>
#include <Vcl.CheckLst.hpp>
#include <string>
//---------------------------------------------------------------------------

using std::string;

PACKAGE double 			getCurrentImageWidth(TImage* img);
PACKAGE double 			getCurrentImageHeight(TImage* img);
PACKAGE TTabSheet*      getTabWithCaption(const string& c, TPageControl* pc);
PACKAGE TTreeNode* 		getTreeItemWithCaption(const string& c, TTreeView* tv);
PACKAGE bool			checkItem(TCheckListBox* CB, const string& item, bool checked);

#endif
