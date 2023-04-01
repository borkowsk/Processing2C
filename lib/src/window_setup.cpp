/// \file window_setup.cpp
/// \brief Domyślna obsługa konfiguracji okna
/// \author 'borkowsk'
/// @date 2023-03-23 (last modification)
/// \details
///
///     Domyślna obsługa konfiguracji okna (setup) aplikacji
///     polegająca jedynie na otwarciu okna o rozmiarze 100x100.
///
/// \ingroup rtm
// //////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////

//#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_window.hpp"
//#include "processing_library.hpp"
//#include "processing_console.hpp"

namespace Processing
{

/// @details The default setup only starts window of size 100x100.
void processing_window::setup()
{
        size(100,100);
}

}//END of namespace Processing
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

