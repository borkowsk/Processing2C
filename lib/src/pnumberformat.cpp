// Processing like console functions
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

//Funkcje formatujące
String nf(double num)
{
    char bufor[1024];
    sprintf(bufor,"%g",num);
    return String(bufor);
}

String nf(double num,int digits)
{
    char bufor[1024];
    sprintf(bufor,"%g",num);//TODO int digits
    return String(bufor);
}

String nf(double num,int left,int right)
{
    char bufor[1024];
    sprintf(bufor,"%g",num);//TODO int left,int right
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
    sprintf(bufor,"%+g",num);//TODO int digits
    return String(bufor);
}

String nfp(double num,int left,int right)
{
    char bufor[1024];
    sprintf(bufor,"%+g",num);//TODO int left,int right
    return String(bufor);
}

String nf(sarray<int> nums)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String nf(sarray<int> nums,int digits)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String nf(sarray<int> nums,int left,int right)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String nf(sarray<float> nums)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String nf(sarray<float> nums,int digits)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String nf(sarray<float> nums,int left,int right)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String nf(sarray<double> nums)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String nf(sarray<double> nums,int digits)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String nf(sarray<double> nums,int left,int right)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}



String nfp(sarray<int> nums)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String nfp(sarray<int> nums,int digits)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String nfp(sarray<int> nums,int left,int right)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String nfp(sarray<float> nums)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String nfp(sarray<float> nums,int digits)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String nfp(sarray<float> nums,int left,int right)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String nfp(sarray<double> nums)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String nfp(sarray<double> nums,int digits)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String nfp(sarray<double> nums,int left,int right)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2020-09-03                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
