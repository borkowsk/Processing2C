//Domyślna obsługa zakończenia aplikacji polegająca jedynie na wywołaniu metody exit klasy bazowej
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
