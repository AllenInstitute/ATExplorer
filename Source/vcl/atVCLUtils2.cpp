#pragma hdrstop
#include "atVCLUtils2.h"
#include "dslStringUtils.h"
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace dsl;

string getStringFromSelectedCB(TCheckListBox* b)
{
    string fName("");
    if(b->ItemIndex != -1)
    {
    	string* s = (string*) b->Items->Objects[b->ItemIndex];
        if(s)
        {
            fName = *s;
        }
    }

    return fName;
}

TTabSheet* getTabWithCaption(const string& c, TPageControl* pc)
{
    if(!pc)
    {
        return NULL;
    }

    for(int i = 0; i < pc->PageCount; i++)
    {
        if(compareStrings(stdstr(pc->Pages[i]->Caption), c, csCaseSensitive))
        {
            return pc->Pages[i];
        }
    }

    return NULL;
}

//---------------------------------------------------------------------------
double getCurrentImageWidth(TImage* img)
{
    //This function assumes stretch is proportional
    double origW = img->Picture->Width;
    double origH = img->Picture->Height;
    double imageR = origW / origH;

    double containerW = img->Width;
    double containerH = img->Height;
    double containerR = containerW / containerH;

    if(containerR > imageR)
    {
    	return containerH * imageR;
    }
    else
    {
    	return containerW;
    }
}

//---------------------------------------------------------------------------
double getCurrentImageHeight(TImage* img)
{
    //This function assumes stretch is proportional
    double origW = img->Picture->Width;
    double origH = img->Picture->Height;
    double imageR = origW / origH;

    double containerW = img->Width;
    double containerH = img->Height;
    double containerR = containerW / containerH;

    if(containerR > imageR)
    {
        return containerH;
    }
    else
    {
    	return containerW /imageR;
    }
}

TTreeNode* getTreeItemWithCaption(const string& c, TTreeView* tv)
{
    if(!tv->Items->Count)
    {
        return NULL;
    }

    TTreeNode* baseNode = tv->Items->GetFirstNode();
    while(baseNode)
    {
        if(baseNode->Text == vclstr(c))
        {
            return baseNode;
        }

        //Check children..
        TTreeNode* node = baseNode->getFirstChild();
        while(node != NULL)
        {
            if(node->Text == vclstr(c))
            {
                return node;
            }
            node = baseNode->GetNextChild(node);
        }
        baseNode = baseNode->GetNext();
    }
    return NULL;
}

bool checkItem(TCheckListBox* CB, const string& item, bool checked)
{
    if(!CB)
    {
        return false;
    }

    int indx = CB->Items->IndexOf(item.c_str());
    if(indx > -1)
    {
        CB->Checked[indx] = checked;
        return true;
    }
    return false;
}
