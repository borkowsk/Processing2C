/**
 * \file pprintwriter.cpp
 * \brief JAVA like streams
 * \classes BufferedReader; PrintWriter;
 * \ingroup file_streams
 * \author 'borkowsk'
 * \last_modification  see the bottom lines
 */
// //////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////
//#include "processing_consts.hpp"
//#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_string.hpp"
#include "processing_library.hpp"
#include "processing_files.hpp"
#include "_impl_errors.h"
#include <cstdio>
#include <iostream>
#include <fstream>

///\namespace Processing2C compatibility libraries
namespace Processing
{

static inline std::ostream& operator << (std::ostream& o,String& str)
{                               assert(str.notEmpty());
    o<<str._std_str();
    return o;
}

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

/// Create opaque std::ofstream connected to file 'name'
/// \param name : any form of text/string
/// \return opaque handle to writable std::ofstream
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
        perror("STORAGE ERROR");
        ALWAYS_ERRMESSAGE( concat("FILE '",name,"' can't be open!") )
        std::cerr.flush();std::cout.flush();
        auto res=system("sleep 1;echo \"\\nSee directory:\\n $PWD\\n\";ls -l");
        //system("/bin/bash ");
        delete file;
    }

    return tmp;
}

/// Create opaque std::ifstream connected to file 'name'
/// \param name : any form of text/string
/// \return opaque handle to readable std::ifstream
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
        perror("STORAGE ERROR");
        ALWAYS_ERRMESSAGE( concat("FILE '",name,"' can't be open!") )
        std::cerr.flush();std::cout.flush();
        auto res=system("sleep 1;echo \"\\nSee directory:\\n $PWD\\n\";ls -l");
        //system("/bin/bash ");
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
/* ******************************************************************
 *               PROCESSING2C  version 2021-12-23                   *
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



