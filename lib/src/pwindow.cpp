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

static int _width=0;//processing_window_base::
static int _height=0;

static float _frameRate=0; ///Aproximated frame rate achived;

static int _frameCount=0;
static int _frameCountFromChange=0;

static milliseconds begintms;
static milliseconds firstms;
static milliseconds lastms;

extern "C" {
int WB_error_enter_before_clean=0;
}

namespace Processing
{

const int&   width  =    _width;
const int&   height =    _height;
const int&   pixelWidth= _width;
const int&   pixelHeight=_height;
const float& frameRate=  _frameRate; ///Get aproximated frame rate achived;
const int&   frameCount= _frameCount;///contains the number of frames that have been displayed since the program started.

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
    while(input_ready())
    {
        int inp=get_char();
        if(inp==EOF) exit();
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

void processing_window_base::mouseClicked()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void processing_window_base::before_setup(int argc,const char *argv[])
{
    randomSeed(time(nullptr));
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

void size(int width,int height)
{
    init_plot(width,height,0,0);
    strokeWeight(1);
    stroke(0);
    fill(255);
}

void fullScreen()
{
    init_plot(4096,2048,0,0);//Powinien dopasowac się do ekranu
    strokeWeight(1);
    stroke(0);
    fill(255);
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

void loop()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void noLoop()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

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
