// main.cpp must be for Processing derived application
// but user may generate and use its own versions
//////////////////////////////////////////////////////////////
#include "processing_consts.hpp"
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include <iostream>

#define DEBUG 1

using namespace Processing;

Processing::processing_window Processing::_processing_window_instance;

int Processing::_INTERNAL_DELAY=10;

int main(int argc,const char *argv[])
{
#ifdef DEBUG
    std::cout<<"DEFAULT MAIN FOR PROCESSING2C TRANSLATOR"<<std::endl;//DEBUG
    std::cout<<"SETUP:"<<std::endl;//DEBUG
#endif
    setlocale(LC_NUMERIC,"en_US.UTF-8");//Because of thousand separator
    _processing_window_instance.before_setup(argc,argv);
    _processing_window_instance.setup();

    if(!_processing_window_instance.inLoop())
    {
        _processing_window_instance.draw();//only once
        _processing_window_instance.after_draw();
    }

    while(1)
    {
#ifdef DEBUG
        //std::cout<<"DRAW:"<<std::endl;//DEBUG
#endif
        delay(_INTERNAL_DELAY);
        if(_processing_window_instance.inLoop())
        {
            _processing_window_instance.draw();
            _processing_window_instance.after_draw();//Calculate frameRate and _INTERNAL_DELAY
        }
        _processing_window_instance.check_events();//Should be repeated any way!
    }

    return 0;
}
/********************************************************************/
/*               PROCESSING2C  version 2020-11-15                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
