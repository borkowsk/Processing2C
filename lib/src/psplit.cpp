/// \file psplit.cpp
/// \brief split & concat functions
/// \author 'borkowsk'
/// \date 2022-11-21 (last modification)
/// \details
///         ...
///
/// \ingroup strings
// //////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////
#include "processing_consts.hpp"
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
//#include "processing_console.hpp"
#include "_impl_errors.h"
#include <string>
//#define DEBUG 1

namespace Processing
{
    String concat(const _string_param& a1,const _string_param& a2)
    {
        String ret=a1; ret+=a2;
        return ret;
    }

    String concat(const _string_param& a1,const _string_param& a2,const _string_param& a3)
    {
        String ret=a1; ret+=a2; ret+=a3;
        return ret;
    }

    String concat(const _string_param& a1,const _string_param& a2,const _string_param& a3,const _string_param& a4)
    {
        String ret=a1; ret+=a2; ret+=a3;ret+=a4;
        return ret;
    }

    String concat(const _string_param& a1,const _string_param& a2,const _string_param& a3,const _string_param& a4,const _string_param& a5)
    {
        String ret=a1; ret+=a2; ret+=a3;ret+=a4;ret+=a5;
        return ret;
    }

    String concat(const _string_param& a1,const _string_param& a2,const _string_param& a3,const _string_param& a4,const _string_param& a5,const _string_param& a6)
    {
        String ret=a1; ret+=a2; ret+=a3;ret+=a4;ret+=a5;ret+=a6;
        return ret;
    }

    static int count_characters(const char *str, char character)
    {
        const char *p = str;
        int count = 0;

        do {
            if (*p == character)
                count++;
        } while (*(p++));

        return count;
    }

sarray<String> split(_string_param string2parse,_string_param delimiter) // TODO tab-shift ->
{
#ifndef NDEBUG
   if(false)//DEBUG
    ERRMESSAGE( concat(" called for:'",string2parse._str(),"' with delimiter '",delimiter._str(),"'") )
#endif
    //Calculate number of strings?
    int numberOfStrings=1+count_characters(string2parse._std_str().c_str(),delimiter[0]);
    //Make output array
    sarray<String> out=new array<String>(numberOfStrings);
    //Find substrings
    if(numberOfStrings>1)
    { //https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c Is ok!
        std::size_t ind = 0;
        std::size_t pos = 0;
        std::size_t dln = delimiter.length(); //std::cout << dln <<  std::endl;
        while ((pos = string2parse.find(delimiter.c_str())) != std::string::npos)
        {
            Processing::String token{ string2parse.substr(0, pos) }; //std::cout << token << std::endl;
            string2parse.erase(0, pos + dln); //std::cout << string2parse << std::endl;
            out[ind++]=token;
        }
        out[ind]=string2parse; //std::cout << string2parse << std::endl;
    }
    else
        out[0]=string2parse;
    return out;
}

}//END of namespace Processing
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


