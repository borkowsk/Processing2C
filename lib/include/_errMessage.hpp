/// \file _errMessage.hpp
/// \brief Functions for printing or logging error messages.
/// \author 'borkowsk'
/// \ingroup rtm
/// \TODO JAVA Exceptions - e.printStackTrace();
///	  file:///home/borkowsk/processing-3.5.4/modes/java/reference/try.html
///	  https://docs.oracle.com/javase/7/docs/api/java/lang/Throwable.html#getMessage()
///	  https://stackoverflow.com/questions/77005/how-to-automatically-generate-a-stacktrace-when-my-program-crashes
///       https://stackoverflow.com/questions/691719/c-display-stack-trace-on-exception 
///       https://www.boost.org/doc/libs/1_73_0/doc/html/stacktrace/getting_started.html
///       https://groups.google.com/g/comp.object.corba/c/YrExJq11cMM
// ///////////////////////////////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////
#ifndef _ERR_MESSAGE_HPP_
#define _ERR_MESSAGE_HPP_
#pragma once
#include <string>
void _errMessage(const char* msg,const char* func,int line=-1,const char* file="");
void _errMessage(std::string msg,const char* func,int line=-1,const char* file="");
/* ****************************************************************** */
/*               PROCESSING2C  version 2021-12-23                     */
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
