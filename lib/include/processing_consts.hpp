/** ****************************************************************
 * \file processing_consts.hpp
 * \brief Stałe dostępne we wszystkich programach w Processingu
 * \author 'borkowsk'
 * \date 2022-11-21 (last modification)
 * \defgroup Processing_compatibility Functions and classes which mimic Processing interface
 * \defgroup JAVA_compatibility Functions and classes which mimic JAVA programming language
 */
/*
    \class is used to indicate that the comment block contains documentation for the class
    \struct to document a C-struct.
    \union to document a union.
    \enum to document an enumeration type.
    \fn to document a function.
    \var to document a variable or typedef or enum value.
    \def to document a #define.
    \typedef to document a type definition.
    \file to document a file.
    \namespace to document a namespace.
    \package to document a Java package.
    \interface to document an IDL interface.
    See: https://www.doxygen.nl/manual/docblocks.html
 */

// //////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////
#pragma once
#ifndef PROCESSING_CONSTS_HPP
#define PROCESSING_CONSTS_HPP

#include <cfloat>
#define _USE_MATH_DEFINES
#include <cmath>
//#include <climits> ???
#include <limits>       // std::numeric_limits

/// \namespace Processing \brief P2C compatibility libraries
/// \addtogroup Processing_compatibility
/// @{
namespace Processing
{

///\var Internal name of the program. Typically equal to base part of main source file in Processing. \ingroup rtm
extern const char* _PROGRAMNAME;

// CHAR CONSTANTS
// //////////////

/// 'ESC' key integer representation
const char ESC=27;
/// \brief ???
const char16_t CODED=65535;

// SETTINGS CONSTANTS
// //////////////////

/// rectMode() and ellipseMode() parameter value \var CENTER
const int CENTER=1;
/// rectMode() and ellipseMode() parameter value \var RADIUS
const int RADIUS=2;
/// rectMode() and ellipseMode() parameter value \var CORNER
const int CORNER=3;
/// rectMode() and ellipseMode() parameter value \var CORNERS
const int CORNERS=4;

/// arc() parameter value \var OPENPIE
const int OPENPIE=1;
/// arc() parameter value \var  OPEN
const int OPEN=0;
/// arc() parameter value \var  CHORD
const int CHORD=2;
/// arc() parameter value \var  PIE
const int PIE=3;

/// strokeCap() parameter
const int SQUARE=1;
/// strokeCap() parameter
const int PROJECT=2;
/// strokeCap() parameter
const int ROUND=3;
/// strokeJoin() parameters
const int MITER=1;
/// strokeJoin() parameters
const int BEVEL=2;
// strokeJoin() parameters
//const int ROUND=3;

/// textAlign() parameter value \var RIGHT
const int RIGHT=39;
/// textAlign() parameter value \var LEFT
const int LEFT=37;
/// textAlign() parameter value \var TOP
const int TOP=102;
/// textAlign() parameter value \var BOTTOM
const int BOTTOM=103;
/// textAlign() parameter value \var BASELINE
const int BASELINE=104;

// MATH CONSTANTS
// //////////////

// ALSO AVAILABLE in <cmath>:
// # define M_PI_2		1.57079632679489661923	/* pi/2 */
// # define M_PI_4		0.78539816339744830962	/* pi/4 */

///  M_PI is imported from \<cmath> \var PI
const auto PI=M_PI; //3.6651914291881;
///  M_PI is imported from \<cmath> then TWO_PI is generated on this base. \var TWO_PI
const auto TWO_PI=2*M_PI; //6.2831855f
/// \a M_PI_2 is imported from \<cmath>, \var HALF_PI
const auto HALF_PI=M_PI_2;
/// \a M_PI_4 is imported from \<cmath>, \var QUARTER_PI
const auto QUARTER_PI=M_PI_4;

/// Why not TWO_PI? TODO?
const auto TAU=6.2831855f;

/// MAX_INT is imported from std::numeric_limits
const auto MAX_INT=std::numeric_limits<int>::max();
const auto MAX_FLOAT=std::numeric_limits<float>::max();

//For angles, nosie, spheres etc...

/// \brief a convert value from degrees to radians \var DEG_TO_RAD
const float DEG_TO_RAD = 0.017453292519943295769236907684886f;


/// \brief a convert value from radians to degrees \var RAD_TO_DEG
const float RAD_TO_DEG = 57.295779513082320876798154814105f;

}/// @} END of namespace Processing
/* ****************************************************************** */
/*               PROCESSING2C  version 2023                           */
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
