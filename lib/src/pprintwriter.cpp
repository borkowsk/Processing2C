// PrintWriter class
//#include "processing_consts.hpp"
//#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_files.hpp"
#include "_impl_errors.h"
#include <iostream>
#include <fstream>

namespace Processing
{

static inline std::ostream& operator << (std::ostream& o,String& str)
{
    o<<str._std_str();
    return o;
}

/// File streams output
//PrintWriter::~PrintWriter()
//{
//    if (_ok() && (*this)->is_open()) //
//        this->get()->close();// Czy podwójne zamknięcie jest bezpieczne?
//}

void BufferedReader::_set(std::ifstream* p)
{
    // HACK!!!
    (*this)=(_JAVAInputStream*)p;//TODO DEBUG - looks like it works
}

void PrintWriter::_set(std::ofstream* p)
{
    // HACK!!!
    (*this)=(_JAVAOutputStream*)p;//TODO DEBUG - looks like it works
}

PrintWriter& createWriter(_string_param name)
{
    auto file=new std::ofstream(name._std_str());                       assert(file!=nullptr);

    static PrintWriter tmp;

    if(file->is_open())
    {
        tmp._set(file);                                                 assert(tmp._ok());
    }
    else
    {
        ALWAYS_ERRMESSAGE( concat("FILE ",name,"can't be open!") )
        delete file;
    }

    return tmp;
}

BufferedReader& createReader(_string_param name)
{
    auto file=new std::ifstream(name._std_str());                        assert(file!=nullptr);

    static BufferedReader tmp;

    if(file->is_open())
    {
        file->exceptions( /*std::ifstream::failbit | ???*/ std::ifstream::badbit );
        tmp._set(file);                                                 assert(tmp._ok());
    }
    else
    {
        ALWAYS_ERRMESSAGE( concat("FILE ",name,"can't be open!") )
        delete file;
    }

    return tmp;
}

void print(PrintWriter& o,_string_param _p1)
{
    o<<_p1;
}

void println(PrintWriter& o,_string_param _p1)
{
    o<<_p1<<std::endl;
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

