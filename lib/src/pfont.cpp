/// \file ***.cpp
/// \brief Obsługa zmiany kroju i parametrów fontu
/// \author 'borkowsk'
/// \date 2022-11-21 (last modification)
/// \details
///     TODO: INNE FONTY NIE ZAIMPLEMENTOWANE!
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

/// Make font available for program
/// `typedef void* PFont;              /// Font handler`
PFont createFont(String fn,int s)
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
    return nullptr;
}

/// Use font
void textFont(PFont f)
{
     FIRST_TIME_ERRMESSAGE( " not implemented!" );
}

/// Sets the spacing between lines of text in units of pixels.
void textLeading(int)
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
}

/// Sets the way text draws to the screen, either as texture maps or as vector geometry (MODEL or SHAPE)
void textMode(int)
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
}

/// Sets the current font size, measured in units of pixels.
void textSize(int)
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
}

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

