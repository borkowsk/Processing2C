//Obsługa zmiany kroju i parametrów fontu
//NIE ZAIPLEMENTOWANA!
#include "processing_consts.hpp"
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "symshell.h"
#include <iostream>

namespace Processing
{

//typedef void* PFont;              /// Font handler
PFont createFont(String fn,int s)
/// Make font available for program
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
    return nullptr;
}

void textFont(PFont f)
/// Use font
{
     std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void textLeading(int)
/// Sets the spacing between lines of text in units of pixels.
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void textMode(int)
/// Sets the way text draws to the screen, either as texture maps or as vector geometry (MODEL or SHAPE)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void textSize(int)
/// Sets the current font size, measured in units of pixels.
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2020-11-19                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
