#include "processing_consts.hpp"
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "symshell.h"
#include <iostream>

namespace Processing
{

/// Parameters:	napTime 	int: milliseconds to pause before running draw() again
void delay(int napTime)
{
    if(napTime>0)
        delay_ms(napTime);
    else
        delay_us(100);//Give system a chance!
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
