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
class String;
class _string_param;

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

String String::operator  & (_string_param v) const
{
    String ret=(*this);
    ret+=v;
    return ret;
}

_string_param _string_param::operator  + (_string_param v) const
{
    _string_param ret=(*this);
    ret+=v;
    return ret;
}

String operator  + (_string_param v,const String& s)
{
    String ret=v;
    ret+=s;
    return ret;
}

String operator  + (_string_param v,_string_param s)
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

_string_param::_string_param(double p)//:String( std::to_string(p) )// inline?
{
    (*this)=nf(p);//Formated more like in Processing
}

_string_param::_string_param(float  p)//:String( std::to_string(p) )// inline?
{
    (*this)=nf(p);//Formated more like in Processing
}

_string_param::_string_param(int    p):String( std::to_string(p) )// inline?
{}

_string_param::_string_param(unsigned long int    p):String( std::to_string(p) )// inline?
{}

_string_param::_string_param(const void *p):String( std::to_string( (size_t)p) )// inline?
{}

_string_param::_string_param(std::exception& e):String( e.what() )
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

String hex(int num)
{
    char bufor[1024];
    sprintf(bufor,"%x",num);
    return String(bufor);
}

String hex(int num,int dig)//String hex(int num,int digits); //TODO
{
    char bufor[1024];
    sprintf(bufor,"%*x",dig,num);//NOT TESTED - TODO
    return String(bufor);
}

//https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
static const char *bit_rep[16] = {
    [ 0] = "0000", [ 1] = "0001", [ 2] = "0010", [ 3] = "0011",
    [ 4] = "0100", [ 5] = "0101", [ 6] = "0110", [ 7] = "0111",
    [ 8] = "1000", [ 9] = "1001", [10] = "1010", [11] = "1011",
    [12] = "1100", [13] = "1101", [14] = "1110", [15] = "1111",
};


String binary(int num)
{
    char bufor[34];
    uint8_t byte0=(num & 0xff000000)>>24;
    uint8_t byte1=(num & 0x00ff0000)>>16;
    uint8_t byte2=(num & 0x0000ff00)>>8;
    uint8_t byte3=(num & 0xff);
    sprintf(bufor,"%s%s%s%s%s%s%s%s",bit_rep[byte0 >> 4], bit_rep[byte0 & 0x0F],
                                     bit_rep[byte1 >> 4], bit_rep[byte1 & 0x0F],
                                     bit_rep[byte2 >> 4], bit_rep[byte2 & 0x0F],
                                     bit_rep[byte3 >> 4], bit_rep[byte3 & 0x0F]);
    return String(bufor);
}

String binary(int value,int digits)
{
    int mask=0xffffffff;
    mask>>=32-digits;
    value&=mask;
    return binary(value);//TEMP solution - TODO!
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
