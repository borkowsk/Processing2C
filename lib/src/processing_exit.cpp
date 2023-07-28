/// \file processing_exit.cpp
/// \brief Processing-owa wersja funkcjo exit - bez parametrów.
/// \author 'borkowsk'
/// @date 2023-03-23 (last modification)
/// \details
///     Created by borkowsk on 23.03.23.
///     Uruchamia obsługę `exit()` z dla okna.
///     Jeśli będzie to domyślna obsługa zakończenia aplikacji to
///     polega ona jedynie na wywołaniu metody exit klasy bazowej
///     a ta posprząta i zawoła globalne `exit(int)`.
///
/// \ingroup rtm
// //////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////
#include "processing_templates.hpp"
#include "processing_window.hpp"

namespace Processing
{

/// @details
///     Just calls  `_processing_window_instance.exit()`.
void exit()
{
    _processing_window_instance.exit();
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
