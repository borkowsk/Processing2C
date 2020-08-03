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


void strokeWeight(float Weight)
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

void rect(float a,float  b,float  c,float  d)
{}

void rectMode(int mode)
// Parameter: mode 	int: either CORNER, CORNERS, CENTER, or RADIUS
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


void saveFrame()
{}

void saveFrame(const char* filename)
{}


}//END of namespace Processing
