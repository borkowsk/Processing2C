/// @file
/// @note Automatically made from _ARCS.pde_ by __Processing to C++__ converter (../../scripts/procesing2cpp.sh).
/// @date 2024-10-15 16:11:03 (translation)
//
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_window.hpp"
#ifndef _NO_INLINE
#include "processing_inlines.hpp" //...is optional.
#endif // _NO_INLINE
using namespace Processing;
#include "local.h" //???.
#include <iostream>
//================================================================

/// Division of the ellipse into sectors.
/// The coordinate system is treated as rotated!
/// This is a test for Processing2C
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: "ARCS.pde"
// @date 2024-09-30 (last change)
//*//////////////////////////////////////////////////

void processing_window::setup()
{
        size(500,500);

        ellipseMode(CENTER);
        arc(0,0,200,200,radians(1),PI/2.0,OPEN); //or PIE or CHORD

        ellipse(250, 250, 200, 200);
        fill(0);
        arc(250, 250, 190, 190, PI/2.0,PI);
        fill(128);
        arc(250, 250, 190, 190, PI,PI*2-PI/10);
        fill(255);

        ellipseMode(CORNER);
        arc(400,400,100,100,radians(10),radians(180),PIE);
}

//MADE NOTE: ../../scripts did it 2024-10-15 16:11:03 !

const char* Processing::_PROGRAMNAME="ARCS";
