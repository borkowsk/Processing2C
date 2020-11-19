//Domyślna obsługa zakończenia aplikacji polegająca jedynie na wywołaniu metody exit klasy bazowej
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
/********************************************************************/
/*               PROCESSING2C  version 2020-11-19                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
