// main.cpp must be for Processing derived application
// but user may generate and use its own versions
//////////////////////////////////////////////////////////////
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include <iostream>

#define DEBUG 1

using namespace Processing;

Processing::processing_window Processing::_processing_window_instance;

int Processing::_INTERNAL_DELAY=100;

int main(int argc,const char *argv[])
{
#ifdef DEBUG
    std::cout<<"DEFAULT MAIN FOR PROCESSING2C TRANSLATOR"<<std::endl;//DEBUG
    std::cout<<"SETUP:"<<std::endl;//DEBUG
#endif
    _processing_window_instance.before_setup(argc,argv);
    _processing_window_instance.setup();

    while(1)
    {
#ifdef DEBUG
        std::cout<<"DRAW:"<<std::endl;//DEBUG
#endif
        _processing_window_instance.draw();
        delay(_INTERNAL_DELAY);
        _processing_window_instance.after_draw();//Calculate frameRate and _INTERNAL_DELAY
    }

    return 0;
}
/********************************************************************/
/*               PROCESSING2C  version 2020-08-19                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
