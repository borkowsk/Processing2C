// PrintWriter class
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
    std::cerr<<__FUNCTION__<<" used for ptr="<<(unsigned long long)w.ptr<<std::endl;
    ptr=w.ptr;w.ptr=nullptr;
}

PrintWriter&  PrintWriter::operator = (PrintWriter& w)
{
    std::cerr<<__FUNCTION__<<" used for ptr="<<(unsigned long long)w.ptr<<std::endl;
    ptr=w.ptr;w.ptr=nullptr;
    return *this;
}

std::fstream* PrintWriter::operator -> ()
{
    return ptr;
}

void PrintWriter::flush()
{
    if(ptr!=nullptr) ptr->flush();
}

PrintWriter& createWriter(const String& name)
{
    std::fstream* file=new std::fstream(name);
    static PrintWriter tmp;
    tmp._set(file);
    return tmp;
}

PrintWriter& createWriter(const char* name)
{
    std::fstream* file=new std::fstream(name);
    static PrintWriter tmp;
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
/*               PROCESSING2C  version 2020-09-03                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/

