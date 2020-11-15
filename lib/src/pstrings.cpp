// most commonly used library functions
#include "processing_consts.hpp"
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp"
#include <iostream>

//#define DEBUG 1

namespace Processing
{

String::~String()// Zwalnianie zasobów przez destruktor klasy bazowej
{
#ifdef DEBUG
    std::cerr<<__FUNCTION__<<" called!"<<std::endl;
#endif
}

String::String(const String& par):std::string( par.c_str() )
{}

String::String(char  c):std::string({c,'\0'})
{}

bool String::operator == (nullptr_t v)
{
    std::cerr<<__FUNCTION__<<" should not be used for nullptr!"<<std::endl;
    return empty();
}

bool String::operator != (nullptr_t)
{
    std::cerr<<__FUNCTION__<<" should not be used for nullptr!"<<std::endl;
    return !empty();
}

 sarray<String> split(_string_param string2parse,_string_param delimiter)
 {

     std::cerr<<__FUNCTION__<<"called for:'"
               <<string2parse.get().c_str()<<"' with delimiter '"
               <<delimiter.get().c_str()<<"'"<<std::endl;
     //Calculate number of strings?
     // ..... TODO
     int numberOfstrings=1;
     //Make output array
     sarray<String> out=new array<String>(numberOfstrings);
     //Find substrings
     //..... TODO
     out[0]=String("Not implemented!");
     return out;
 }
}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2020-11-15                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
