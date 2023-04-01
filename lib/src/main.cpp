/// \file main.cpp
/// \brief  main() function for Processing like application
/// \author 'borkowsk'
/// \date 2023-03-14 (last modification)
/// \details
///     main() function must exists for Processing2C++ applications
///     but user may generate and use its own versions
/// \ingroup rtm
///
// //////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////

#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "_impl_errors.h"

#include <iostream>
#include <iomanip>

extern unsigned long _ssh_window;//From symshell, ale to juz nie jest ptr!

using namespace Processing;

Processing::processing_window Processing::_processing_window_instance;

int Processing::_INTERNAL_DELAY=10;

int main(int argc,const char *argv[])
{
    //extern sarray<String> args; //WHOLE PROGRAM PARAMETERS FOR PROCESSING
#ifndef NDEBUG
    FIRST_TIME_ERRMESSAGE( "DEFAULT MAIN FOR PROCESSING2C TRANSLATOR" );
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
    FIRST_TIME_ERRMESSAGE( "settings() called" );
#endif
    //processing_window::settings()
    _processing_window_instance.settings();
#ifndef NDEBUG
    FIRST_TIME_ERRMESSAGE( "setup() called" );
#endif
    _processing_window_instance.setup();

    if(_ssh_window==0)//setup nie zainicjował okna!!! Zabezpiecza jeśli nie ma rysowania w `setup()`
    {
        size(100,100);
        std::cerr<<"setup() should use size() function!"<<std::endl;
    }

    if(!_processing_window_instance.inLoop())
    {
#ifndef NDEBUG
        FIRST_TIME_ERRMESSAGE( "draw() called for single time" );
#endif
        _processing_window_instance.draw();//only once
        _processing_window_instance.after_draw();
    }
    else
    while(true)
    {
#ifndef NDEBUG
        FIRST_TIME_ERRMESSAGE( "call a draw() in loop" );
#endif
        delay(_INTERNAL_DELAY);
        if(_processing_window_instance.inLoop())
        {
            _processing_window_instance.draw();
            _processing_window_instance.after_draw();//Calculate frameRate and _INTERNAL_DELAY
        }

        extern int   _exp_frame_rate;//From pwindow
        //std::cerr<<"(("<<frameCount<<"*10)%"<<_exp_frame_rate<<")==0  == "<<(((frameCount*10)%_exp_frame_rate))<<std::endl;
        //if( ((frameCount*10)%_exp_frame_rate)==0  )//Powinno byc mniej więcej 10 razy na sekundę żeby było idealnie
        {//Tak jak powyżej nie działa, a bez tego ma krótszy czas widoczności

            _processing_window_instance.check_events();//Should be repeated any way!
        }
    }

    return 0;
}
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

