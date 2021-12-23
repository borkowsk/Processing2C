/// \file _errMessage.cpp
/// \brief  Funkcja drukująca błędy na konsolę
/// \author 'borkowsk'
///
#include "_errMessage.hpp"
#include <iostream>

void _errMessage(const char* msg,const char* func,int line,const char* file)
{
    std::cerr<<func<<":"<<msg;
    if(line!=-1)
        std::cerr<<"\nSource: "<<file<<":"<<line;
    std::cerr<<std::endl;
}


void _errMessage(std::string msg,const char* func,int line,const char* file)
{
        std::cerr<<func<<":"<<msg;
        if(line!=-1)
                std::cerr<<"\nSource: "<<file<<":"<<line;
        std::cerr<<std::endl;
}
