//Funkcja drukująca błędy na konsolę
#include "_errMessage.hpp"
#include <iostream>

void _errMessage(std::string msg,const char* func,int line,const char* file)
{
        std::cerr<<func<<":"<<msg;
        if(line!=-1)
                std::cerr<<" src: "<<file<<":"<<line;
        std::cerr<<std::endl;
}
