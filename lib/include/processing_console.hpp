/// \file processing_console.hpp
/// \brief Związane z konsolą funkcje print i println oraz formatowanie
/// \author 'borkowsk'
/// \date 2022-11-21 (last modification)
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
             _string_param _p5="",_string_param _p6="",_string_param _p7="",_string_param _p8=""); ///< TODO MORE! (up to 10)

  void println();
  void println(_string_param _p1); //The println() function writes to the console. Each call to this function creates also a new line.
  void println(_string_param _p1,_string_param _p2);
  void println(_string_param _p1,_string_param _p2,_string_param _p3);
  void println(_string_param _p1,_string_param _p2,_string_param _p3,_string_param _p4,
               _string_param _p5="",_string_param _p6="",_string_param _p7="",_string_param _p8=""); ///< TODO MORE! (up to 10)

}//END of namespace Processing
/* ****************************************************************** */
/*               PROCESSING2C  version 2022                           */
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
