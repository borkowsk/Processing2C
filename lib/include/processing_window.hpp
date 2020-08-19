// processing_window.hpp
#pragma once
#ifndef PROCESSING_WINDOW_H
#define PROCESSING_WINDOW_H
///
///
///
namespace Processing
{

class processing_window_base
{
  public:
    virtual ~processing_window_base();
    virtual void exit();
    virtual void mouseClicked();
    virtual void before_setup(int argc, const char *argv[]);
    virtual void setup()=0;//Must be provided!
    virtual void draw(){} //EMPTY DRAW()
    virtual void after_draw();//Calculate frameRate and _INTERNAL_DELAY
    virtual void check_events();//If events are in queue, they are processed
};

extern class processing_window: public processing_window_base
{
  public:
  void setup();
  void draw();
  void exit();
  void mouseClicked();
} _processing_window_instance;

extern const char* _PROGRAMNAME;
extern const int& width;
extern const int& height;
extern const int& pixelWidth;
extern const int& pixelHeight;

void size(int width,int height);
void fullScreen();
void loop();
void noLoop();
void setFrameRate(float fps); ///Set desired frame rate

extern const float& frameRate; /// Get aproximated frame rate achived;
extern const int&   frameCount;/// The system variable frameCount contains the number of frames that have been displayed since the program started.
extern int _INTERNAL_DELAY;//=100; // Used by set_delay();

void noSmooth();
void smooth();

void stroke(float Gray);
void stroke(float Gray,float Alpha);
void stroke(float Red,float Green,float Blue);
void stroke(float Red,float Green,float Blue,float Alpha);
void noStroke();

void strokeWeight(float Weight);/// Parameters	weight 	float: the weight (in pixels) of the stroke
void strokeCap(int cap);/// Parameters	cap 	int: either SQUARE, PROJECT, or ROUND
void strokeJoin(int join);/// Parameters	join 	int: either MITER, BEVEL, ROUND

void fill(float Gray);
void fill(float Gray,float Alpha);
void fill(float Red,float Green,float Blue);
void fill(float Red,float Green,float Blue,float Alpha);
void noFill();

void point(float x,float y);
void line(float  x1,float  y1,float  x2,float  y2);

void ellipse(float a,float  b,float  c,float  d);
void arc(float a,float  b,float  c,float  d,float  start,float  stop);
void arc(float a,float  b,float  c,float  d,float  start,float  stop,int  mode);
/// Parameters:
///  a 	float: x-coordinate of the ellipse
///  b 	float: y-coordinate of the ellipse
///  c 	float: width of the ellipse by default
///  d 	float: height of the ellipse by default
///  start 	float: angle to start the arc, specified in radians
///  stop 	float: angle to stop the arc, specified in radians

void ellipseMode(int mode);/// Parameters	mode 	int: either CENTER, RADIUS, CORNER, or CORNERS


void rect(float a,float  b,float  c,float  d);
void rect(float a,float  b,float  c,float  d,float r);
void rectMode(int mode);/// Parameter: mode 	int: either CORNER, CORNERS, CENTER, or RADIUS


void text(char c, float x,float y);
void text(const char* str,float x,float y);
void text(char chars[],int start,int stop,float x,float y);
void text(const char* str,float x1,float y1,float x2,float y2);
void text(float num,float x,float y);

/// Executes the code within draw() one time. This functions allows the program to update the display window only when necessary, for example when an event registered by mousePressed() or keyPressed() occurs.
/// In structuring a program, it only makes sense to call redraw() within events such as mousePressed(). This is because redraw() does not run draw() immediately (it only sets a flag that indicates an update is needed).
/// The redraw() function does not work properly when called inside draw(). To enable/disable animations, use loop() and noLoop().
void redraw();


//void cursor(int kind);
//void cursor(PImage img);
//void cursor(PImage img,int x,int y);
void cursor();
void noCursor();
/// Parameters:
/// kind 	int: either ARROW, CROSS, HAND, MOVE, TEXT, or WAIT
/// img 	PImage: any variable of type PImage
///   x 	int: the horizontal active spot of the cursor
///   y 	int: the vertical active spot of the cursor

void delay(int napTime); ///The delay() function halts for a specified time. Delay times are specified in thousandths of a second.
/// Parameters	napTime 	int: milliseconds to pause before running draw() again

inline
void pixelDensity(int density){} //DO NOTHING!
// Parameters	density 	int: 1 or 2

inline
int displayDensity(int display=0) {return 1;}
/// Parameters	display 	int: the display number to check

}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2020-08-19                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
#endif
