// main.cpp must be for Processing derived application
// but user may generate and use its own versions
//////////////////////////////////////////////////////////////
#include "processing_consts.hpp"
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include <iostream>
#include <iomanip>

extern void* _ssh_window;//From symshell.h

using namespace Processing;

Processing::processing_window Processing::_processing_window_instance;

int Processing::_INTERNAL_DELAY=10;

int main(int argc,const char *argv[])
{
    //extern sarray<String> args; //WHOLE PROGRAM PARAMETERS FOR PROCESSING
#ifndef NDEBUG
    FIRST_TIME_ERRMESSAGE( "-DEFAULT MAIN FOR PROCESSING2C TRANSLATOR" );
#endif
    std::cout<<"START:"<<year()<<std::setfill('0')
            <<std:: setw(2)<<month()
            <<std:: setw(2)<<day()<<'-'
            <<std:: setw(2)<<hour()
            <<std:: setw(2)<<minute()
            <<std:: setw(2)<<second()<<'.'
            <<std:: setw(3)<<millis()<<std::endl;
    setlocale(LC_NUMERIC,"en_US.UTF-8");//Because of thousand separator

    _processing_window_instance.before_setup(argc,argv);
#ifndef NDEBUG
    FIRST_TIME_ERRMESSAGE( "-call setup()" );
#endif
    _processing_window_instance.setup();

    if(_ssh_window==NULL)//setup nie zainicjowal okna!!!
    {
        size(100,100);
        std::cerr<<"setup() should use size() function!"<<std::endl;
    }

    if(!_processing_window_instance.inLoop())
    {
#ifndef NDEBUG
        FIRST_TIME_ERRMESSAGE( "-call draw() single time" );
#endif
        _processing_window_instance.draw();//only once
        _processing_window_instance.after_draw();
    }

    while(1)
    {
#ifndef NDEBUG
        FIRST_TIME_ERRMESSAGE( "-call draw() in loop" );
#endif
        delay(_INTERNAL_DELAY);
        if(_processing_window_instance.inLoop())
        {
            _processing_window_instance.draw();
            _processing_window_instance.after_draw();//Calculate frameRate and _INTERNAL_DELAY
        }

        extern int   _exp_frame_rate;//From pwindow
        //std::cerr<<"(("<<frameCount<<"*10)%"<<_exp_frame_rate<<")==0  == "<<(((frameCount*10)%_exp_frame_rate))<<std::endl;
        //if( ((frameCount*10)%_exp_frame_rate)==0  )//Powinno byc mniej wiecej 10 razy na sekunde zeby bylo idealnie
        {//Tak jak powyzej nie dziala, a bez tego ma krotszy czas widocznosci

            _processing_window_instance.check_events();//Should be repeated any way!
        }
    }

    return 0;
}
/********************************************************************/
/*               PROCESSING2C  version 2021-07-20                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
