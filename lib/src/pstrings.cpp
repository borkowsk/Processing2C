// most commonly used library functions
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

String& String::operator += (const String& v)
{
    std::string::operator += (v.c_str());
    return *this;
}

String String::operator  + (const String& v) const
{
    std::string tmp(this->c_str());
    tmp+=v.c_str();
    return tmp;
}

_string_param::~_string_param()// Zwalnianie zasobów przez destruktor klasy bazowej
{
#ifdef DEBUG
    std::cerr<<__FUNCTION__<<" called!"<<std::endl;
#endif
}

_string_param::_string_param(char p):String( p )
{}

_string_param::_string_param(double p):String( std::to_string(p) )
{}

_string_param::_string_param(float  p):String( std::to_string(p) )
{}

_string_param::_string_param(int    p):String( std::to_string(p) )
{}

_string_param::_string_param(const void *p):String( std::to_string( (size_t)p) )
{}

}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2020-08-19                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
