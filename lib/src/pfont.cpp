/// \file ***.cpp
/// \brief
/// \author 'borkowsk'
///
//Obsługa zmiany kroju i parametrów fontu
// TODO - FONTY NIE ZAIPLEMENTOWANE!
#include "processing_consts.hpp"
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "symshell.h"
#include "_impl_errors.h"

namespace Processing
{

//typedef void* PFont;              /// Font handler
PFont createFont(String fn,int s)
/// Make font available for program
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
    return nullptr;
}

void textFont(PFont f)
/// Use font
{
     FIRST_TIME_ERRMESSAGE( " not implemented!" );
}

void textLeading(int)
/// Sets the spacing between lines of text in units of pixels.
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
}

void textMode(int)
/// Sets the way text draws to the screen, either as texture maps or as vector geometry (MODEL or SHAPE)
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
}

void textSize(int)
/// Sets the current font size, measured in units of pixels.
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
}

}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2021-10-26                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
