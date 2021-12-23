/// \file _errMessage.hpp
/// \brief Functions for printing or logging error messages.
/// \author 'borkowsk'
/// \ingroup rtm
///
// //////////////////////////////////////////////////////////////////////
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