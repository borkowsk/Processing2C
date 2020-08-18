/// podstawy obsługo okienka pseudo-processingowego
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include <iostream>

static int _width=0;//processing_window_base::
static int _height=0;
static float _frameRate=0; ///Aproximated frame rate achived;
static int _frameCount=0;

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
    //TODO!
}

void processing_window_base::check_events()
//If events are in queue, they are processed
{
    //TODO!!
}

processing_window_base::~processing_window_base()
{
    //Is anything to do here?
}

void processing_window_base::exit()
{
    //Is anything to do here?
    //Finishing the whole aplication
    ::exit(0);
}

void processing_window_base::mouseClicked()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void size(int width,int height)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void fullScreen()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void setFrameRate(float fps)
///Set desired frame rate
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
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
