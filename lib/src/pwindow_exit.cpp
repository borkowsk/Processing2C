/// @file    pwindow_exit.cpp
/// @details Created by borkowsk on 23.03.23.
///          Only implementation of `processing_window_base::exit()`,
///          which by default closes window and calls `::exit(int)`.
/// \ingroup rtm
// //////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////

#include "processing_templates.hpp"
#include "processing_window.hpp"
#include "symshell.h"

namespace Processing
{

    /// @details
    ///     It closes windows or other plotting device connected via SymShell library,
    ///     then calls global `exit()` function wit status `0`.
    void processing_window_base::exit()
    {
        //Is anything to do here?
        close_plot();
        //Finishing the whole application
        ::exit(0);
    }

}
//END of namespace Processing
/* ******************************************************************
 *               PROCESSING2C  version 2023                         *
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