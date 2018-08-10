#ifndef TRStackViewH
#define TRStackViewH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
class TRStackView : public TFrame
{
    __published:
    private:

    public:
        __fastcall TRStackView(TComponent* Owner);
};

extern PACKAGE TRStackView *RStackView;
#endif
