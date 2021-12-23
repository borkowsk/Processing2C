/// \file processing_consts.hpp
/// \brief Stałe dostępne we wszystkich programach w Processingu
/// \author 'borkowsk'
/// \ingroup Processing_compatibility
///
// //////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////
#pragma once
#ifndef PROCESSING_CONSTS_HPP
#define PROCESSING_CONSTS_HPP

#include <cfloat>
#define _USE_MATH_DEFINES
#include <cmath>
//#include <climits>
#include <limits>       // std::numeric_limits

///\namespace Processing \brief P2C compatibility libraries
namespace Processing
{
//CHAR CONSTANTS
const char16_t CODED=65535;
const char ESC=27;

//SETTINGS CONSTANTS
///ellipseMode(mode) parameters
const int CENTER=1;
const int RADIUS=2;
const int CORNER=3;
const int CORNERS=4;
///for arc's
const int OPENPIE=1;
const int OPEN=0;//Open CHORD
const int CHORD=2;
const int PIE=3;
///rectMode(mode)parameters
//const int CENTER=1;
//const int RADIUS=2;
//const int CORNER=3;
//const int CORNERS=4;
///strokeCap(cap) parameters
const int SQUARE=1;
const int PROJECT=2;
const int ROUND=3;
///strokeJoin(join) parameters
const int MITER=1;
const int BEVEL=2;
//const int ROUND=3;
//for textAligment
const int RIGHT=39;
const int LEFT=37;
const int TOP=102;
const int BOTTOM=103;
const int BASELINE=104;


/// MATH CONSTANTS
/// # define M_PI_2		1.57079632679489661923	/* pi/2 */
/// # define M_PI_4		0.78539816339744830962	/* pi/4 */
///
const auto PI=M_PI;//3.6651914291881;
const auto TWO_PI=2*M_PI;//6.2831855f
const auto TAU=6.2831855f;
const auto HALF_PI=M_PI_2;
const auto QUARTER_PI=M_PI_4;
const auto MAX_INT=std::numeric_limits<int>::max();

//For angles, nosie, spheres etc...
const float DEG_TO_RAD = 0.017453292519943295769236907684886f;
const float RAD_TO_DEG = 57.295779513082320876798154814105f;

}//END of namespace Processing
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
#endif // PROCESSING_CONSTS_HPP
