/// podstawy obsługo okienka pseudo-processingowego
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "SYMSHELL/symshell.h"
#include <iostream>
#include <chrono>
                            //https://stackoverflow.com/questions/7889136/stdchrono-and-cout
using namespace std::chrono;//https://en.cppreference.com/w/cpp/chrono/duration
                            //https://stackoverflow.com/questions/19555121/how-to-get-current-timestamp-in-milliseconds-since-1970-just-the-way-java-gets
static milliseconds begintms;
static milliseconds firstms;
static milliseconds lastms;

static int _width=0;//processing_window_base::
static int _height=0;

static float _frameRate=0; ///Aproximated frame rate achived;

static int _frameCount=0;
static int _frameCountFromChange=0;

static bool _mousePressed=0;
static int  _mouseButton=0;
static int  _mouseX=0;
static int  _mouseY=0;

static bool _keyPressed=0;

extern "C" {
int WB_error_enter_before_clean=0;
}

namespace Processing
{
processing_window *const surface=&_processing_window_instance;
const int&   width  =    _width;
const int&   height =    _height;
const int&   pixelWidth= _width;
const int&   pixelHeight=_height;
const float& frameRate=  _frameRate; ///Get aproximated frame rate achived;
const int&   frameCount= _frameCount;///contains the number of frames that have been displayed since the program started.

const bool& mousePressed = _mousePressed;
const int&  mouseButton  = _mouseButton;/// When a mouse button is pressed, the value of this is set to either LEFT, RIGHT, or CENTER,
                                        /// depending on which button is pressed. If no button is pressed, mouseButton may be reset to 0.
const int&  mouseX = _mouseX;/// always contains the current horizontal coordinate of the mouse.
const int&  mouseY = _mouseY;/// always contains the current vertical coordinate of the mouse.
                             /// Note that Processing can only track the mouse position when the pointer is over the current window

const bool&   keyPressed = _keyPressed;/// is true if any key is pressed and false if no keys are pressed.

char    key;    /// always contains the value of the most recent key on the keyboard that was used (either pressed or released)
int     keyCode;/// The variable keyCode is used to detect special keys such as the arrow keys (UP, DOWN, LEFT, and RIGHT)
                             /// as well as ALT, CONTROL, and SHIFT.
                             /// There are issues with how keyCode behaves across different renderers and operating systems.
                             /// Watch out for unexpected behavior as you switch renderers and operating systems.
                             /// When checking for these keys, it can be useful to first check if the key is coded.
                             /// This is done with the conditional if (key == CODED), as shown in the example KEYBOARD.

sarray<String> args=nullptr;//WHOLE PROGRAM PARAMETERS!!!

void processing_window_base::before_draw()
{
    _mousePressed=0;
    _keyPressed=0;
}

void processing_window_base::after_draw()
//Calculate frameRate and _INTERNAL_DELAY
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

void processing_window_base::check_events()
//If events are in queue, they are processed
{
    //std::cerr<<'?';
    while(input_ready())
    {
        int inp=get_char();
        std::cerr<<inp<<' '<<char(inp);
        if(inp==EOF || inp==27 )
        {
            exit();
            ::exit(0);//Na wypadek gdyby uztkownik zapomnial wywolac super.exit
        }
        _keyPressed=true;
        key=inp;
        keyCode=0;// TODO!
    }
}

processing_window_base::~processing_window_base()
{
    //Is anything to do here?
}

void processing_window_base::exit()
{
    //Is anything to do here?
    close_plot();
    //Finishing the whole aplication
    ::exit(0);
}

void exit()
{
    _processing_window_instance.exit();
}

void processing_window_base::mouseClicked()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void processing_window_base::keyPressed()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void processing_window_base::setTitle(Processing::_string_param)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void processing_window_base::before_setup(int argc,const char *argv[])
{
    randomSeed(time(nullptr));

    sarray<String> args=new array<String>(argc);//WHOLE PROGRAM PARAMETERS!!!
    for(int i=0;i<argc;i++)
    {
        args[i]=String(argv[i]);//new String(argv[i]);???
    }

    buffering_setup(1);//buffered window!
    fix_size(1);
    set_background(256+200);

    shell_setup(_PROGRAMNAME,argc,argv);
    milliseconds ms = duration_cast< milliseconds >(
        system_clock::now().time_since_epoch()
    );
    //std::cerr<<ms.count()<<"ms"<<std::endl;
    begintms=ms;
    firstms=ms;
}

// The background() function sets the color used for the background of the Processing window. The default background is light gray.
// This function is typically used within draw() to clear the display window at the beginning of each frame, but it can be used
// inside setup() to set the background on the first frame of animation or if the backgound need only be set once.
void background(float gray)
{
    set_background(256+gray);
}

void background(float gray,float  alpha)
{
    set_background(256+gray);
    std::cerr<<__FUNCTION__<<" ignoring alpha channel!"<<std::endl;
}

void background(float v1,float v2,float v3)
{
    set_background(v1,v2,v3);
}

void background(float v1,float v2,float v3,float  alpha)
{
    set_background(v1,v2,v3);
    std::cerr<<__FUNCTION__<<" ignoring alpha channel!"<<std::endl;
}

void size(int width,int height)
{
    init_plot(width,height,0,0);
    strokeWeight(1);
    stroke(0);
    fill(255);
    _width=screen_width();
    _height=screen_height();
}

void fullScreen()
{
    init_plot(4096,2048,0,0);//Powinien dopasowac się do ekranu
    strokeWeight(1);
    stroke(0);
    fill(255);
    _width=screen_width();
    _height=screen_height();
}

void setFrameRate(float fps)
///Set desired frame rate
{
    _INTERNAL_DELAY=1000/fps;
}

/// Executes the code within draw() one time. This functions allows the program to update the display window only when necessary,
/// for example when an event registered by mousePressed() or keyPressed() occurs.
/// In structuring a program, it only makes sense to call redraw() within events such as mousePressed(). This is because redraw()
/// does not run draw() immediately (it only sets a flag that indicates an update is needed).
/// The redraw() function does not work properly when called inside draw(). To enable/disable animations, use loop() and noLoop().
void redraw()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

//void cursor(int kind);
//void cursor(PImage img);
//void cursor(PImage img,int x,int y);
void cursor()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}
void noCursor()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}
//Parameters:
//kind 	int: either ARROW, CROSS, HAND, MOVE, TEXT, or WAIT
//img 	PImage: any variable of type PImage
//  x 	int: the horizontal active spot of the cursor
//  y 	int: the vertical active spot of the cursor

}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2020-09-02                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
