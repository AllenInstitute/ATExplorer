#pragma hdrstop
#include "atTextFileItemView.h"
#include "atRenderProject.h"
#include "dslLogger.h"
#include "atTextFile.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace at
{

using namespace dsl;
TextFileItemView::TextFileItemView(TPageControl& pc, TextFile& p)
:
ProjectItemTabbedView(pc, p)
{
    this->mObserverTag = "TextFileItemView";

    mTextFileFrame = unique_ptr<TTextFileFrame>(new TTextFileFrame(p, &mPC));
    mTextFileFrame->Parent =  mTabSheet.get();
    mTextFileFrame->Align = alClient;
    mTabSheet->Caption = p.getAlias().c_str();
}

TextFileItemView::~TextFileItemView()
{
    Log(lInfo) << "Closing TextFileItemView..";
}

//Views are managed by shared pointers so no need to call delete..
void TextFileItemView::update(Subject* theChangedSubject, SubjectEvent se)
{
    if(se == SubjectEvent::SubjectBeingDestroyed)
    {
        //Go away..
        Log(lInfo) << "Subject being destroyed..";
    }
}

}

