/// podstawy obsługo okienka pseudo-processingowego
#include "processing_window.hpp"
#include <iostream>

static int width=0;//processing_window_base::
static int height=0;
static float frameRate=0; ///Aproximated frame rate achived;

namespace Processing
{

const int& width=::width;
const int& height=::height;
const float& frameRate=::frameRate; ///Get aproximated frame rate achived;

processing_window_base::~processing_window_base()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void processing_window_base::exit()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void processing_window_base::mouseClicked()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void size(int width,int height)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void loop()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void noLoop()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void setFrameRate(float fps)
///Set desired frame rate
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void noSmooth()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void smooth()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}


void stroke(float Gray)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void stroke(float Gray,float Alpha)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void stroke(float Red,float Green,float Blue)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void stroke(float Red,float Green,float Blue,float Alpha)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void noStroke()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}


void fill(float Gray)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void fill(float Gray,float Alpha)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void fill(float Red,float Green,float Blue)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void fill(float Red,float Green,float Blue,float Alpha)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void noFill()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}


void point(float x,float y)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void line(float  x1,float  y1,float  x2,float  y2)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void rect(float a,float  b,float  c,float  d)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void rect(float a,float  b,float  c,float  d,float r)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

/// Parameter: mode 	int: either CORNER, CORNERS, CENTER, or RADIUS
void rectMode(int mode)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}


/// Parameters
///  a 	float: x-coordinate of the ellipse
///  b 	float: y-coordinate of the ellipse
///  c 	float: width of the ellipse by default
///  d 	float: height of the ellipse by default
///  start 	float: angle to start the arc, specified in radians
///  stop 	float: angle to stop the arc, specified in radians
void ellipse(float a,float  b,float  c,float  d)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void arc(float a,float  b,float  c,float  d,float  start,float  stop)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void arc(float a,float  b,float  c,float  d,float  start,float  stop,int  mode)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

/// Parameters	mode 	int: either CENTER, RADIUS, CORNER, or CORNERS
void ellipseMode(int mode)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}


void text(char c, float x,float y)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void text(const char* str,float x,float y)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void text(char chars[],int start,int stop,float x,float y)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void text(const char* str,float x1,float y1,float x2,float y2)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void text(float num,float x,float y)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void strokeWeight(float Weight)/// Parameters	weight 	float: the weight (in pixels) of the stroke
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void strokeCap(int cap)/// Parameters	cap 	int: either SQUARE, PROJECT, or ROUND
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void strokeJoin(int join)/// Parameters	join 	int: either MITER, BEVEL, ROUND
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

/// Executes the code within draw() one time. This functions allows the program to update the display window only when necessary, for example when an event registered by mousePressed() or keyPressed() occurs.
/// In structuring a program, it only makes sense to call redraw() within events such as mousePressed(). This is because redraw() does not run draw() immediately (it only sets a flag that indicates an update is needed).
/// The redraw() function does not work properly when called inside draw(). To enable/disable animations, use loop() and noLoop().
void redraw()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

}//END of namespace Processing
