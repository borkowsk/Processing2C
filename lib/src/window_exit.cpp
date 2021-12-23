/// \file window_exit.cpp
/// \brief Domyślna obsługa zakończenia aplikacji
/// \author 'borkowsk'
/// \ingroup rtm
///
/// Domyślna obsługa zakończenia aplikacji polegająca jedynie na wywołaniu metody exit klasy bazowej
///
#include "processing_consts.hpp"
#include "processing_window.hpp"
#include "processing_templates.hpp"
//#include "processing_library.hpp"
//#include "processing_console.hpp"
namespace Processing
{

void processing_window::exit()          //it is called whenever a window is closed.
{
  processing_window_base::exit();       //What library superclass have to do at exit
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


