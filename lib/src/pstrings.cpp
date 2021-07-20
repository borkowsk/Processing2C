// most commonly used library functions
#include "processing_consts.hpp"
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp"
#include <iostream>

//#define DEBUG 1

namespace Processing
{

String::~String()// Zwalnianie zasobów przez destruktor klasy bazowej
{
#ifdef DEBUG
    FIRST_TIME_ERRMESSAGE( " called!" );
#endif
}

String::String(const String& par):std::string( par.c_str() )
{}

String::String(char  c):std::string({c})
{}

bool String::operator == (nullptr_t v)
{
    //FIRST_TIME_ERRMESSAGE( " should not be performed for nullptr!" );// WHY???
    return empty();
}

bool String::operator != (nullptr_t)
{
    //FIRST_TIME_ERRMESSAGE( " should not be performed for nullptr!" );// WHY???
    return !empty();
}

static int count_substrings(const char *str,const char *substr)
{
              //https://www.sanfoundry.com/c-program-count-occurence-substring/
    return 0; //TODO!
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

 sarray<String> split(_string_param string2parse,_string_param delimiter)
 {

#ifndef NDEBUG
     if(0)//DEBUG
     std::cerr<<__FUNCTION__<<" called for:'"
               <<string2parse.get().c_str()<<"' with delimiter '"
               <<delimiter.get().c_str()<<"'"<<std::endl;
#endif
     //Calculate number of strings?
     int numberOfstrings=1+count_characters(string2parse.c_str(),delimiter[0]);
     //Make output array
     sarray<String> out=new array<String>(numberOfstrings);
     //Find substrings
     if(numberOfstrings>1)
     { //https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c POPRAWIONE!
         size_t ind = 0;
         size_t pos = 0;
         size_t dln = delimiter.length(); //std::cout << dln <<  std::endl;
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
/*               PROCESSING2C  version 2021-07-20                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
