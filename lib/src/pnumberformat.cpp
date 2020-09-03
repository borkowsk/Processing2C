// Processing like console functions
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp"
#include <iostream>
namespace Processing
{

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

//DLA bool
/*
String& String::operator += (bool v)
{
    std::cerr<<__FUNCTION__<<" (1)!"<<std::endl;
    if(v) (*this)+="true";
    else  (*this)+="false";
    return *this;
}

String String::operator  + (bool v) const
{
    std::cerr<<__FUNCTION__<<" (2)!"<<std::endl;
    String tmp(*this);
    tmp+=v;
    return tmp;
}

String operator  + (bool v,const String& self)
{
    std::cerr<<__FUNCTION__<<" (3)!"<<std::endl;
    String tmp;
    tmp+=v;
    tmp+=self.c_str();
    return tmp;
}
*/
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
