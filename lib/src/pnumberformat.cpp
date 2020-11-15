/// Processing like numbers 2 string and string 2 number conversions
///////////////////////////////////////////////////////////////////////
#include "processing_consts.hpp"
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp"
#include <iostream>
namespace Processing
{

String& String::operator = (_string_param v)// inline?
{
    std::string::operator = (v);return *this;
}

String& String::operator += (_string_param v)// inline?
{
    std::string::operator += (v);return *this;
}

String String::operator  + (_string_param v) const
{
    String ret=(*this);
    ret+=v;
    return ret;
}

String operator  + (_string_param v,const String& s)
{
    String ret=v;
    ret+=s;
    return ret;
}

_string_param::~_string_param()// Zwalnianie zasobów przez destruktor klasy bazowej
{
#ifdef DEBUG
    std::cerr<<__FUNCTION__<<" called!"<<std::endl;
#endif
}

_string_param::_string_param(char p):String( p )// inline?
{}

_string_param::_string_param(double p):String( std::to_string(p) )// inline?
{}

_string_param::_string_param(float  p):String( std::to_string(p) )// inline?
{}

_string_param::_string_param(int    p):String( std::to_string(p) )// inline?
{}

_string_param::_string_param(unsigned long int    p):String( std::to_string(p) )// inline?
{}

_string_param::_string_param(const void *p):String( std::to_string( (size_t)p) )// inline?
{}

//Funkcje formatujące pojedyncze liczby
String nf(double num)
{
    char bufor[1024];
    sprintf(bufor,"%g",num);
    return String(bufor);
}

String nf(double num,int digits)
{
    char bufor[1024];
    sprintf(bufor,"%0*g",digits+(num<0?+1:0),num);
    return String(bufor);
}

String nf(double num,int left,int right)
{
    char bufor[1024];
    sprintf(bufor,"%0*.*f",left+right+(num<0?+2:+1),right,num);
    return String(bufor);
}

String nfs(double num,int digits)
{
    char bufor[1024];
    bool minus=num<0;
    sprintf(bufor,"%s%0*g",minus?"":" ",digits+(minus?1:0),num);
    return String(bufor);
}

String nfs(double num,int left,int right)
{
    char bufor[1024];
    bool minus=num<0;
    sprintf(bufor,"%s%0*.*f",minus?"":" ",left+right+(minus?2:1),right,num);
    return String(bufor);
}

String nfp(double num)
{
    char bufor[1024];
    sprintf(bufor,"%+g",num);
    return String(bufor);
}

String nfp(double num,int digits)
{
    char bufor[1024];
    sprintf(bufor,"%+0*g",digits+1,num);
    return String(bufor);
}

String nfp(double num,int left,int right)
{
    char bufor[1024];
    sprintf(bufor,"%+0*.*f",left+right+2,right,num);
    return String(bufor);
}


String nfc(double num)
{
    char bufor[1024];
    sprintf(bufor,"%'g",num);
    return String(bufor);
}

String nfc(double num,int digits)
{
    char bufor[1024];
    //setlocale(LC_NUMERIC,"en_US.UTF-8");
    sprintf(bufor,"%'0.*f",digits,num);
    //setlocale(LC_NUMERIC,"de_DE.UTF-8");
    return String(bufor);
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
/*
String& String::operator += (const String& v)
{
    std::string::operator += (v.c_str());
    return *this;
}

String& String::operator += (int v)
{
    (*this)+=nf(v);return *this;
}

String& String::operator += (float v)
{
    (*this)+=nf(v);return *this;
}

String& String::operator += (double v)
{
    (*this)+=nf(v);return *this;
}


String String::operator  + (int v) const
{
    String tmp(*this);
    tmp+=nf(v);
    return tmp;
}

String String::operator  + (float v) const
{
    String tmp(*this);
    tmp+=nf(v);
    return tmp;
}

String String::operator  + (double v) const
{
    String tmp(*this);
    tmp+=nf(v);
    return tmp;
}

String operator  + (int v,const String& self)
{
    std::string tmp=nf(v);
    tmp+=self.c_str();
    return tmp;
}

String operator  + (float v,const String& self)
{
    std::string tmp=nf(v);
    tmp+=self.c_str();
    return tmp;
}

String operator  + (double v,const String& self)
{
    std::string tmp=nf(v);
    tmp+=self.c_str();
    return tmp;
}
*/
