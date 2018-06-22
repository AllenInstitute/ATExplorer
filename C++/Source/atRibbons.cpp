#pragma hdrstop
#include "atRibbons.h"
//---------------------------------------------------------------------------
namespace at
{


Ribbons::Ribbons()
{}

Ribbons::~Ribbons()
{
    for(int i = 0; i < size(); i++)
    {
        delete this->operator[](i);
    }
}

}
