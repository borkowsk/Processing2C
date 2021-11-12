// PrintWriter class
#include "processing_consts.hpp"
#include "processing_window.hpp"
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
PrintWriter::~PrintWriter()
{
    if(ptr!=nullptr)
    {
        ptr->close();
        delete ptr;// Zwalnianie zasobów
        ptr=nullptr;
    }
}

// Real ;-) constructor - TRANSFERING!
PrintWriter::PrintWriter(PrintWriter& w)
{
#ifndef NDEBUG
    String tmp{" performed PrintWriter copy constructor "};
    tmp+=w.ptr;
    FIRST_TIME_ERRMESSAGE( tmp );
#endif
    ptr=w.ptr;w.ptr=nullptr;
}

//TRANSFERING assigment
PrintWriter&  PrintWriter::operator = (PrintWriter& w)
{
#ifndef NDEBUG
    String tmp{" performed PrintWriter operator= "};
    tmp+=w.ptr;
    FIRST_TIME_ERRMESSAGE( tmp );
#endif
    ptr=w.ptr;w.ptr=nullptr;
    return *this;
}

PrintWriter& createWriter(_string_param name)
{
    std::ofstream* file=new std::ofstream(name._std_str());             assert(file!=nullptr);

    static PrintWriter tmp;

    if(file->is_open())
    {
        tmp._set(file);                                                 assert(tmp._ok());
    }
    else
    {
        ALWAYS_ERRMESSAGE( String("FILE ")+name+String("can't be open!") );
        delete file;
    }

    return tmp;
}

/// File streams input
BufferedReader::~BufferedReader()
// Zwalnianie zasobów
{
    if(ptr!=nullptr)
    {
        ptr->close();
        delete ptr;// Zwalnianie zasobów
        ptr=nullptr;
    }
}

// Real ;-) constructor - TRANSFERING!
BufferedReader::BufferedReader(BufferedReader& w)
{
#ifndef NDEBUG
    String tmp{" performed BufferedReader copy constructor "};
    tmp+=w.ptr;
    FIRST_TIME_ERRMESSAGE( tmp );
#endif
    ptr=w.ptr;w.ptr=nullptr;
}


//TRANSFERING assigment
BufferedReader& BufferedReader::operator = (BufferedReader& w)
{
#ifndef NDEBUG
    String tmp{" performed BufferedReader operator= "};
    tmp+=w.ptr;
    FIRST_TIME_ERRMESSAGE( tmp );
#endif
    ptr=w.ptr;w.ptr=nullptr;
    return *this;
}


BufferedReader& createReader(_string_param name)
{
    std::ifstream* file=new std::ifstream(name._std_str());                        assert(file!=nullptr);

    static BufferedReader tmp;

    if(file->is_open())
    {
        file->exceptions( /*std::ifstream::failbit |*/ std::ifstream::badbit );
        tmp._set(file);                                                 assert(tmp._ok());
    }
    else
    {
        ALWAYS_ERRMESSAGE( String("FILE ")+name+String("can't be open!") );
        delete file;
    }

    return tmp;
}

std::ofstream* PrintWriter::_get() const
{
                                        assert(ptr!=nullptr);
    return ptr;
}

std::ifstream* BufferedReader::_get() const
{
                                       assert(ptr!=nullptr);
return ptr;
}

//void print();//To bez sensu
//void print(PrintWriter& o,const String& ); //???
//void print(PrintWriter& o,const std::string& ); //???
//void println(PrintWriter& o,const String& ); //???
//void println(PrintWriter& o,const std::string& ); //???

void print(PrintWriter& o,_string_param _p1)
{
    *o._get()<<_p1;
}

void println(PrintWriter& o,_string_param _p1)
{
    *o._get()<<_p1<<std::endl;
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

