#ifndef TATIFDataProjectFrameH
#define TATIFDataProjectFrameH
#include "atATIFDataProject.h"
#include <System.Classes.hpp>
#include <Vcl.CheckLst.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Graphics.hpp>
//---------------------------------------------------------------------------


class TCreateLocalVolumesForm;

using at::ATIFDataProject;
//---------------------------------------------------------------------------
class PACKAGE TATIFDataProjectFrame : public TFrame
{
    __published:	// IDE-managed Components

    private:
                                                        //A Reference to a atifdata project
        ATIFDataProject&		      	                mRP;
        void                                            populate();

    public:
    						__fastcall 					TATIFDataProjectFrame(ATIFDataProject& rp, TComponent* Owner);

};

extern PACKAGE TATIFDataProjectFrame *ATIFDataProjectFrame;
#endif
