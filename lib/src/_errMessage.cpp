/// \file _errMessage.cpp
/// \brief  Funkcja drukująca błędy na konsolę
/// \author 'borkowsk'
/// \date 2022-11-21 (last modification)

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

/* ******************************************************************
 *               PROCESSING2C  version 2022                         *
 ********************************************************************
 *           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 *
 *            W O J C I E C H   B O R K O W S K I                   *
 *          Robert Zajonc Institute for Social Studies,             *
 *                     UNIVERSITY OF WARSAW                         *
 *   (Instytut Studiów Społecznych Uniwersytetu Warszawskiego)      *
 *    WWW: http://iss.uw.edu.pl/en/ ; https://en.uw.edu.pl/         *
 *    RG : https://www.researchgate.net/profile/Wojciech-Borkowski  *
 *    GITHUB: https://github.com/borkowsk                           *
 *                                                                  *
 *                               (Don't change or remove this note) *
 ********************************************************************/