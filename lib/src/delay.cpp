/// \file delay.cpp
/// \brief delay function
/// \author 'borkowsk'
/// \date 2022-11-21 (last modification)
// //////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "symshell.h"
#include <iostream>

namespace Processing
{
/// Implementation on Processing like delay() function
/// \param napTime :	napTime 	int: milliseconds to pause before running draw() again
void delay(int napTime)
{
    if(napTime>0)
        delay_ms(napTime);
    else
        delay_us(100);//Give system a chance!
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