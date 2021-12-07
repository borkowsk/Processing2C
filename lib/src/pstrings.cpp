// most commonly used library functions
#include "processing_consts.hpp"
//#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
//#include "processing_console.hpp"
#include "_impl_errors.h"
#include <string>
#include <iostream> // Tylko z powodu _errMessage(Processing::String...)

//#define DEBUG 1 /* TODO??? */

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

String::String(const char c):std::string({c})
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
        FIRST_TIME_ERRMESSAGE( "NOT IMPLEMENTED");
        return 0; //TODO!
    }

    void _errMessage(Processing::String msg,const char* func,int line,const char* file)
    {
        std::cerr<<func<<":\""<<msg._std_str()<<"\"";
        if(line!=-1)
            std::cerr<<" src: "<<file<<":"<<line;
        std::cerr<<std::endl;
    }

}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2021-12-07                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiów Społecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
