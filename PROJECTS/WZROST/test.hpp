#include "processing_templates.hpp"
using namespace Processing;
#include "local.h"

void tests()
{
    smatrix<bool>         bools = new matrix<bool>(50,2);// OK

    sarray<bool>          test1 = new array<bool>(2);// Compiler error?
    sarray<bool>          test2;

    test2 = new array<bool>(2);//OK

    sarray<bool>   test3 { new array<bool>(2) };//OK

    sarray<pRGB> dummy;
    dummy = new array<pRGB>(Side);
    dummy[Side/2] = new RGB();//OK
}

