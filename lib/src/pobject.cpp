/// \file pobject.cpp
/// \brief  Processing & Java Object base class
/// \author 'borkowsk'
/// \ingroup JAVA_compatibility
///
// //////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////
#include "processing_consts.hpp"
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "_impl_errors.h"

namespace Processing
{

    long Object::hashCode() const
    ///	returns the hashcode number for this object
    {
        FIRST_TIME_ERRMESSAGE( " - not implemented! " );
        return (size_t)this;
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


