// PrintWriter class
#include "processing_consts.hpp"
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include <iostream>

namespace Processing
{

/// File streams output
PrintWriter::~PrintWriter()
{
    if(ptr!=nullptr)
    {
        delete ptr;// Zwalnianie zasobów
        ptr=nullptr;
    }
}

PrintWriter::PrintWriter()
{
    ptr=nullptr;
}

PrintWriter::PrintWriter(PrintWriter& w)
{
    FIRST_TIME_ERRMESSAGE( " used for ptr="<<(unsigned long long)w.ptr );
    ptr=w.ptr;w.ptr=nullptr;
}

PrintWriter&  PrintWriter::operator = (PrintWriter& w)
{
    FIRST_TIME_ERRMESSAGE( " used for ptr="<<(unsigned long long)w.ptr );
    ptr=w.ptr;w.ptr=nullptr;
    return *this;
}


PrintWriter& createWriter(_string_param name)
{
    std::ofstream* file=new std::ofstream(name);
    static PrintWriter tmp;
    tmp._set(file);
    return tmp;
}

BufferedReader& createReader(_string_param name)
{
    std::ifstream* file=new std::ifstream(name);
    file->exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    static BufferedReader tmp;
    tmp._set(file);
    return tmp;
}

//void print();//To bez sensu
//void print(PrintWriter& o,const String& ); //???
//void print(PrintWriter& o,const std::string& ); //???
//void println(PrintWriter& o,const String& ); //???
//void println(PrintWriter& o,const std::string& ); //???

void print(PrintWriter& o,_string_param _p1)
{
    (std::ostream&)o<<_p1;
}

void println(PrintWriter& o,_string_param _p1)
{
    (std::ostream&)o<<_p1<<std::endl;
}

}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2020-12-10                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/

