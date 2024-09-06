/// \file processing_console.hpp
/// \brief Związane z konsolą funkcje print i println oraz formatowanie
/// \author 'borkowsk'
/// @date 2024-09-06 (last modification)
/// \ingroup console
// //////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////
#pragma once
#ifndef PROCESSING_CONSOLE_H
#define PROCESSING_CONSOLE_H

///\namespace Processing \brief P2C compatibility libraries
namespace Processing
{
  class _string_param;

  //void print(); //To bez sensu
  void print(_string_param _p1); //The print() function writes to the console
  void print(_string_param _p1,_string_param _p2);
  void print(_string_param _p1,_string_param _p2,_string_param _p3);
  void print(_string_param _p1,_string_param _p2,_string_param _p3,_string_param _p4,
             _string_param _p5="",_string_param _p6="",_string_param _p7="",_string_param _p8="",
             _string_param _p9="",_string_param _pA="",_string_param _pB="",_string_param _pC="",
             _string_param _pD="",_string_param _pE="",_string_param _pF=""
                     );

  void println();
  void println(_string_param _p1); //The println() function writes to the console. Each call to this function creates also a new line.
  void println(_string_param _p1,_string_param _p2);
  void println(_string_param _p1,_string_param _p2,_string_param _p3);
  void println(_string_param _p1,_string_param _p2,_string_param _p3,_string_param _p4,
               _string_param _p5="",_string_param _p6="",_string_param _p7="",_string_param _p8="",
               _string_param _p9="",_string_param _pA="",_string_param _pB="",_string_param _pC="",
               _string_param _pD="",_string_param _pE="",_string_param _pF=""
                       );

  void flush(); //???_string_param _pD="",_string_param _pE="",_string_param _pF=""
}//END of namespace Processing
/* ****************************************************************** */
/*               PROCESSING2C  version 2024                           */
/* ****************************************************************** */
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                   */
/*            W O J C I E C H   B O R K O W S K I                     */
/*    Instytut Studiów Społecznych Uniwersytetu Warszawskiego         */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI    */
/*    RG : https://www.researchgate.net/profile/Wojciech-Borkowski    */
/*    GITHUB: https://github.com/borkowsk                             */
/*                                                                    */
/*                                 (Don't change or remove this note) */
/* ****************************************************************** */
#endif
