/// podstawy obsługo okienka pseudo-processingowego
#include "processing_window.hpp"

static int width=0;//processing_window_base::
static int height=0;
static float frameRate=0; ///Aproximated frame rate achived;

namespace Processing
{

const int& width=::width;
const int& height=::height;
const float& frameRate=::frameRate; ///Get aproximated frame rate achived;

processing_window_base::~processing_window_base()
{}

void processing_window_base::exit()
{}

void processing_window_base::mouseClicked()
{}

void size(int width,int height)
{}

void loop()
{}

void noLoop()
{}

void setFrameRate(float fps)
///Set desired frame rate
{}

void noSmooth()
{}

void smooth()
{}


void stroke(float Gray)
{}

void stroke(float Gray,float Alpha)
{}

void stroke(float Red,float Green,float Blue)
{}

void stroke(float Red,float Green,float Blue,float Alpha)
{}

void noStroke()
{}


void fill(float Gray)
{}

void fill(float Gray,float Alpha)
{}

void fill(float Red,float Green,float Blue)
{}

void fill(float Red,float Green,float Blue,float Alpha)
{}

void noFill()
{}


void point(float x,float y)
{}

void line(float  x1,float  y1,float  x2,float  y2)
{}

void rect(float a,float  b,float  c,float  d)
{}

void rect(float a,float  b,float  c,float  d,float r)
{}

/// Parameter: mode 	int: either CORNER, CORNERS, CENTER, or RADIUS
void rectMode(int mode)
{}


/// Parameters
///  a 	float: x-coordinate of the ellipse
///  b 	float: y-coordinate of the ellipse
///  c 	float: width of the ellipse by default
///  d 	float: height of the ellipse by default
///  start 	float: angle to start the arc, specified in radians
///  stop 	float: angle to stop the arc, specified in radians
void ellipse(float a,float  b,float  c,float  d)
{}

void arc(float a,float  b,float  c,float  d,float  start,float  stop)
{}

void arc(float a,float  b,float  c,float  d,float  start,float  stop,int  mode)
{}

/// Parameters	mode 	int: either CENTER, RADIUS, CORNER, or CORNERS
void ellipseMode(int mode)
{}


void text(char c, float x,float y)
{}

void text(const char* str,float x,float y)
{}

void text(char chars[],int start,int stop,float x,float y)
{}

void text(const char* str,float x1,float y1,float x2,float y2)
{}

void text(float num,float x,float y)
{}

void strokeWeight(float Weight)/// Parameters	weight 	float: the weight (in pixels) of the stroke
{}

void strokeCap(int cap)/// Parameters	cap 	int: either SQUARE, PROJECT, or ROUND
{}

void strokeJoin(int join)/// Parameters	join 	int: either MITER, BEVEL, ROUND
{}

}//END of namespace Processing
