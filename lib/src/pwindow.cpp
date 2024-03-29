/// \file pwindow.cpp
/// \brief podstawy obsługi okienka pseudo-processingowego
/// \author 'borkowsk'
/// \date 2023-03-14 (last modification)
/// \details
///         ...
///
/// \ingroup rtm
// //////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "symshell.h"
#include "_impl_errors.h"

#include <chrono>
//#include <iostream> //ONLY FOR SOME DEBUG. But these instruction were commented out!

                            //https://stackoverflow.com/questions/7889136/stdchrono-and-cout
using namespace std::chrono;//https://en.cppreference.com/w/cpp/chrono/duration
                            //https://stackoverflow.com/questions/19555121/how-to-get-current-timestamp-in-milliseconds-since-1970-just-the-way-java-gets
static milliseconds begintms;
static milliseconds firstms;
static milliseconds lastms;

static int _width=0;//processing_window_base::
static int _height=0;

static float _frameRate=0; ///Approximated frame rate achieved;
       int   _exp_frame_rate=100;///Expected frame rate

static int _frameCount=0;
static int _frameCountFromChange=0;

static bool _mousePressed=0;
static int  _mouseButton=0;
static int  _mouseX=0;
static int  _mouseY=0;
static int  _pmouseX=0;
static int  _pmouseY=0;

static bool _keyPressed=0;

extern "C" {
int WB_error_enter_before_clean=0;
}

namespace Processing
{
/// \brief Alias for _processing_window_instance
/// \ingroup rtm
processing_window *const surface=&_processing_window_instance;

const int&   width=       _width;
const int&   height=      _height;
const int&   pixelWidth=  _width;
const int&   pixelHeight= _height;

///Get approximated frame rate achieved;
const float& frameRate=   _frameRate;
///contains the number of frames that have been displayed since the program started.
const int&   frameCount=  _frameCount;

const bool& mousePressed = _mousePressed;
bool&       mousePressedWr = _mousePressed;///Writable version! ADVANCED USAGE!

const int&  mouseButton  = _mouseButton;/// When a mouse button is pressed, the value of this is set to either LEFT, RIGHT, or CENTER,
                                        /// depending on which button is pressed. If no button is pressed, mouseButton may be reset to 0.
const int&  mouseX = _mouseX;/// always contains the current horizontal coordinate of the mouse.
const int&  mouseY = _mouseY;/// always contains the current vertical coordinate of the mouse.
                             /// Note that Processing can only track the mouse position when the pointer is over the current window

const int&  pmouseX=_pmouseX;/// always contains the previous horizontal coordinate of the mouse.
const int&  pmouseY=_pmouseY;/// always contains the previous vertical coordinate of the mouse.
                             /// Note that Processing can only track the mouse position when the pointer is over the current window

const bool&   keyPressed = _keyPressed;/// is true if any key is pressed and false if no keys are pressed.
bool&         keyPressedWr = _keyPressed;///Writable version! ADVANCED USAGE!

char    key;    /// always contains the value of the most recent key on the keyboard that was used (either pressed or released)

int     keyCode;/// TODO!
                             ///The variable keyCode is used to detect special keys such as the arrow keys (UP, DOWN, LEFT, and RIGHT)
                             /// as well as ALT, CONTROL, and SHIFT.
                             /// There are issues with how keyCode behaves across different renderers and operating systems.
                             /// Watch out for unexpected behavior as you switch renderers and operating systems.
                             /// When checking for these keys, it can be useful to first check if the key is coded.
                             /// This is done with the conditional if (key == CODED), as shown in the example KEYBOARD.

sarray<String> args;//WHOLE PROGRAM PARAMETERS!!!

/// @details
///     Clears events flags.
void processing_window_base::before_draw()
{
    _mousePressed=0;
    _keyPressed=0;
}

/// @details
///     It realises drawing, updates counters, then calculates `frameRate` and `_INTERNAL_DELAY`
void processing_window_base::after_draw()
{
    flush_plot();

    _frameCount++;
    _frameCountFromChange++;

    //... Calculate frameRate:
    milliseconds ms = duration_cast< milliseconds >(
        system_clock::now().time_since_epoch()
    );
    _frameRate=((double)_frameCountFromChange)/((ms-firstms).count()/1000.0);
    //std::cerr<<_frameCountFromChange<<"frames /"<<((ms-firstms).count()/1000.0)<<"s = "<<_frameRate<<std::endl;
    //... Calculate _INTERNAL_DELAY: TODO!
    // ...
}

/// @details
///     If events are in queue, they are processed
///     Apart frame rate, messages in Processing are get only 10 times per second!
void processing_window_base::check_events()
{
    //std::cerr<<'?';
    _mousePressed=false;
    _keyPressed=false;
    while(input_ready())
    {
        //new input is ready for reading
        _keyPressed=false;

        int inp=get_char();
        //std::cerr<<inp<<' '<<char(inp);
        switch(inp){
        case EOF:
        case 27:
            exit();
            ::exit(0); //!< Na wypadek gdyby użytkownik zapomniał wywołać `super.exit`
            break;
        case '\b':
            _pmouseX=_mouseX; //!< `_pmouseX` always contains the previous horizontal coordinate of the mouse.
            _pmouseY=_mouseY; //!< `_pmouseX` always contains the previous vertical coordinate of the mouse.
            get_mouse_event(_mouseX,_mouseY,_mouseButton);
            if(_mouseButton==1) _mouseButton=LEFT;
            else
            if(_mouseButton==3) _mouseButton=RIGHT;
            else
            if(_mouseButton==2) _mouseButton=3;
            _mousePressed=true;
            onMousePressed();
            _mousePressed=false;
            onMouseReleased();
            onMouseClicked();
            _mousePressed=true;
            break;
        case '\n':
        case '\r': draw();
            break;
        default:
            key=inp;
            keyCode=0;// TODO!
            _keyPressed=true;
            onKeyPressed();
            _keyPressed=false;
            onKeyReleased();
            _keyPressed=true;
            break;
        }
    }
}

/// @details
///     It does all jobs with program parameters, then sets all defaults.
void processing_window_base::before_setup(int argc,const char *argv[])
{
    extern sarray<String> args; ///< JAVA LIKE PROGRAM PARAMETERS!!!
                                ///< So, without program name at the beginning.

    args=new array<String>(argc-1); ///< Allocation of JAVA LIKE PROGRAM PARAMETERS!!!
    int argpos=0;                      ///< When parameters beginning with '-' exist on list,
                                       ///< some empty parameters appeared at the end of args table.

    for(int i=1;i<argc;i++) //In JAVA name of the program is not available as par0!!!
        if(argv[i][0]!='-') //Parameters for X11 or symshell are skipped here.
        {
            args[argpos++]=String(argv[i]); //new String(argv[i]);???
        }

    randomSeed(time(nullptr));
    //fix_size(SSH_YES); //NOT WORK UNDER X11 - TODO?
    set_background(256+200);
    print_transparently(SSH_YES);
    buffering_setup(SSH_YES);//buffered window!
    mouse_activity(SSH_YES);

    shell_setup(_PROGRAMNAME,argc,argv);

    milliseconds ms = duration_cast< milliseconds >(
        system_clock::now().time_since_epoch()
    );
    //std::cerr<<ms.count()<<"ms"<<std::endl;
    begintms=ms;
    firstms=ms;
}

/// @details
///     It initializes SymShell graphic output, then set defaults for it.
void size(int width,int height)
{
    init_plot(width,height,0,0);
                                                                                                 assert(_ssh_window!=0);
    strokeWeight(1);
    stroke(0);
    fill(255);
    _width=screen_width();
    _height=screen_height();
}

/// @details
///     By declaring a very large window, usually larger than any screen, it tries to force the system to limit.
void fullScreen()
{
    init_plot(3600,2400,0,0); //Powinien dopasować się do ekranu
    strokeWeight(1);
    stroke(0);
    fill(255);
    _width=screen_width();
    _height=screen_height();
}

/// @details
///     Set desired frame rate, which, however, only works approximately!
void setFrameRate(float fps)
{
    _exp_frame_rate=fps;
    _INTERNAL_DELAY=1000/fps;
}

/// @details
///     This function sets the title in the window bar if it is possible with the given way of
///     displaying in the SymShell module used.
void processing_window_base::setTitle(Processing::_string_param bar)
{
    set_title(bar.c_str());
}

/// @details
///     Executes the code within `draw()` one time. This functions allows the program to update the display window only
///     when necessary, for example when an event registered by `mousePressed()` or `keyPressed()` occurs.
///     In structuring a program, it only makes sense to call `redraw()` within events such as `mousePressed()`. This is
///     because `redraw()` does not run `draw()` immediately (it only sets a flag that indicates an update is needed).
///     The `redraw()` function does not work properly when called inside `draw()`.
///     To enable/disable animations, use `loop()` and `noLoop()`.
void redraw()
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
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


