/// \file ***.cpp
/// \brief
/// \author 'borkowsk'
///
/// Processing like console functions

#include "processing_consts.hpp"
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp"
#include <iostream>

using namespace  Processing;

namespace Processing {

static inline std::ostream& operator << (std::ostream& o,String& str)
{
    o<<str._std_str();
    return o;
}

//void print();//To bez sensu
void print(_string_param _p1)
{
    std::cout<<_p1;
}

void print(_string_param _p1,_string_param _p2)
{
    std::cout<<_p1<<' '<<_p2;
}

void print(_string_param _p1,_string_param _p2,_string_param _p3)
{
    std::cout<<_p1<<' '<<_p2<<' '<<_p3;
}

void print(_string_param _p1,_string_param _p2,_string_param _p3,_string_param _p4,
           _string_param _p5,_string_param _p6,_string_param _p7,_string_param _p8)
{
    std::cout<<_p1<<' '<<_p2<<' '<<_p3;
    if(_p4.notEmpty()) std::cout<<' '<<_p4;
    if(_p5.notEmpty()) std::cout<<' '<<_p5;
    if(_p6.notEmpty()) std::cout<<' '<<_p6;
    if(_p7.notEmpty()) std::cout<<' '<<_p7;
    if(_p8.notEmpty()) std::cout<<' '<<_p8;
}

void println()
{
    std::cout<<std::endl;
}

void println(_string_param _p1)
{
    std::cout<<_p1<<std::endl;
}

void println(_string_param _p1,_string_param _p2)
{
    std::cout<<_p1<<' '<<_p2<<std::endl;
}

void println(_string_param _p1,_string_param _p2,_string_param _p3)
{
    std::cout<<_p1<<' '<<_p2<<' '<<_p3<<std::endl;
}

void println(_string_param _p1,_string_param _p2,_string_param _p3,_string_param _p4,
             _string_param _p5,_string_param _p6,_string_param _p7,_string_param _p8)

{
    std::cout<<_p1<<' '<<_p2<<' '<<_p3;
    if(_p4.notEmpty()) std::cout<<' '<<_p4;
    if(_p5.notEmpty()) std::cout<<' '<<_p5;
    if(_p6.notEmpty()) std::cout<<' '<<_p6;
    if(_p7.notEmpty()) std::cout<<' '<<_p7;
    if(_p8.notEmpty()) std::cout<<' '<<_p8;
    std::cout<<std::endl;
}

}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2021-10-07                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
