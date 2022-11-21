/// \file
/// \brief PImage and cursors
/// \author 'borkowsk'
/// \date 2022-11-21 (last modification)
/// \details
///     TODO implement PImage and cursors
///
/// \ingroup PROCESSING_compatibility
// //////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////
#include "processing_consts.hpp"
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "symshell.h"
#include "_impl_errors.h"

namespace Processing
{

    //void cursor(int kind);
    //void cursor(PImage img);
    //void cursor(PImage img,int x,int y);
    void cursor()
    {
        FIRST_TIME_ERRMESSAGE( " not implemented!" );
    }

    void noCursor()
    {
        FIRST_TIME_ERRMESSAGE( " not implemented!" );
    }
    //Parameters:
    //kind 	int: either ARROW, CROSS, HAND, MOVE, TEXT, or WAIT
    //img 	PImage: any variable of type PImage
    //  x 	int: the horizontal active spot of the cursor
    //  y 	int: the vertical active spot of the cursor

}//END of namespace Processing
/* ******************************************************************
 *               PROCESSING2C  version 2022                         *
 ********************************************************************
 *           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 *
 *            W O J C I E C H   B O R K O W S K I                   *
 *          Robert Zajonc Institute for Social Studies,             *
 *                     UNIVERSITY OF WARSAW                         *
 *   (Instytut Studiów Społecznych Uniwersytetu Warszawskiego)      *
 *    WWW: http://iss.uw.edu.pl/en/ ; https://en.uw.edu.pl/         *
 *    RG : https://www.researchgate.net/profile/Wojciech-Borkowski  *
 *    GITHUB: https://github.com/borkowsk                           *
 *                                                                  *
 *                               (Don't change or remove this note) *
 ********************************************************************/


