// Processing like console functions
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp"
#include <iostream>

namespace Processing
{

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
    if(_p4) std::cout<<' '<<_p4;
    if(_p5) std::cout<<' '<<_p5;
    if(_p6) std::cout<<' '<<_p6;
    if(_p7) std::cout<<' '<<_p7;
    if(_p8) std::cout<<' '<<_p8;
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
    if(_p4) std::cout<<' '<<_p4;
    if(_p5) std::cout<<' '<<_p5;
    if(_p6) std::cout<<' '<<_p6;
    if(_p7) std::cout<<' '<<_p7;
    if(_p8) std::cout<<' '<<_p8;
    std::cout<<std::endl;
}


String nf(double num)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String nf(double num,int digits)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String nf(double num,int left,int right)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
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