//Domyślna obsługa konfiguracji okna (setup) aplikacji polegająca jedynie 
//na otwarciu okna o rozmiarze 100x100
#include "processing_window.hpp"
#include "processing_templates.hpp"
//#include "processing_library.hpp"
//#include "processing_console.hpp"
namespace Processing
{

void processing_window::setup()
{
        size(100,100);
}

}//END of namespace Processing
