// most commonly used library functions
#include "processing_consts.hpp"
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp"
#include "_impl_errors.h"
#include <string>
//#define DEBUG 1

namespace Processing
{

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

sarray<String> split(_string_param string2parse,_string_param delimiter)
{

#ifndef NDEBUG
    if(0)//DEBUG
    ERRMESSAGE( (String(" called for:'")+string2parse._str()+String("' with delimiter '")+delimiter._str()+String("'")) );
#endif
    //Calculate number of strings?
    int numberOfstrings=1+count_characters(string2parse._std_str().c_str(),delimiter[0]);
    //Make output array
    sarray<String> out=new array<String>(numberOfstrings);
    //Find substrings
    if(numberOfstrings>1)
    { //https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c POPRAWIONE!
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
/********************************************************************/
/*               PROCESSING2C  version 2021-11-12                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
