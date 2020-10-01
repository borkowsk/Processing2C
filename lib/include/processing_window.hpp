// processing_window.hpp
#pragma once
#ifndef PROCESSING_WINDOW_H
#define PROCESSING_WINDOW_H

#ifndef OPTINLINE
#define OPTINLINE /* EPMTY */
#endif

namespace Processing
{
//CHAR CONSTANTS
const char ESC=27;

//SETTINGS CONSTANTS
///ellipseMode(mode) parameters
const int CENTER=1;
const int RADIUS=2;
const int CORNER=3;
const int CORNERS=4;
///rectMode(mode)parameters
//const int CENTER=1;
//const int RADIUS=2;
//const int CORNER=3;
//const int CORNERS=4;
///strokeCap(cap) parameters
const int SQUARE=1;
const int PROJECT=2;
const int ROUND=3;
///strokeJoin(join) parameters
const int MITER=1;
const int BEVEL=2;
//const int ROUND=3;
//textAligment
const int LEFT=101;
const int TOP=102;
const int BOTTOM=103;

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
  bool _loop=true;
  public:
  bool inLoop() {return _loop;}
  void setup();
  void draw();
  void exit();
  void mouseClicked();
  friend void loop();
  friend void noLoop();
} _processing_window_instance;

inline void loop()
{
    _processing_window_instance._loop=true;
}

inline void noLoop()
{
    _processing_window_instance._loop=false;
}

/// Global "system" variables
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern const char* _PROGRAMNAME;
extern const int& width;
extern const int& height;
extern const int& pixelWidth;
extern const int& pixelHeight;

/// The mousePressed variable stores whether or not a mouse button is currently being pressed.
/// The value is true when any mouse button is pressed, and false if no button is pressed.
/// The mouseButton variable can be used to determine which button has been pressed.
extern const bool& mousePressed;
extern       int&  mouseButton;/// When a mouse button is pressed, the value of this is set to either LEFT, RIGHT, or CENTER,
                               /// depending on which button is pressed. If no button is pressed, mouseButton may be reset to 0.
extern       int&  mouseX;/// always contains the current horizontal coordinate of the mouse.
extern       int&  mouseY;/// always contains the current vertical coordinate of the mouse.
                          /// Note that Processing can only track the mouse position when the pointer is over the current window

/// For non-ASCII keys, use the keyCode variable. The keys included in the ASCII specification (BACKSPACE, TAB, ENTER, RETURN, ESC, and DELETE)
/// do not require checking to see if the key is coded, and you should simply use the key variable instead of keyCode
/// If you're making cross-platform projects, note that the ENTER key is commonly used on PCs and Unix and the RETURN key is used instead on Macintosh.
/// Check for both ENTER and RETURN to make sure your program will work for all platforms.
extern const bool&   keyPressed;/// is true if any key is pressed and false if no keys are pressed.
extern       char    key;/// always contains the value of the most recent key on the keyboard that was used (either pressed or released)
extern       int     keyCode;/// The variable keyCode is used to detect special keys such as the arrow keys (UP, DOWN, LEFT, and RIGHT)
                             /// as well as ALT, CONTROL, and SHIFT.
                             /// There are issues with how keyCode behaves across different renderers and operating systems.
                             /// Watch out for unexpected behavior as you switch renderers and operating systems.
                             /// When checking for these keys, it can be useful to first check if the key is coded.
                             /// This is done with the conditional if (key == CODED), as shown in the example KEYBOARD.

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

OPTINLINE
void stroke(float Gray);
void stroke(float Gray,float Alpha);
OPTINLINE
void stroke(float Red,float Green,float Blue);
void stroke(float Red,float Green,float Blue,float Alpha);
OPTINLINE
void noStroke();

OPTINLINE
void strokeWeight(float Weight);/// Parameters	weight 	float: the weight (in pixels) of the stroke
void strokeCap(int cap);/// Parameters	cap 	int: either SQUARE, PROJECT, or ROUND
void strokeJoin(int join);/// Parameters	join 	int: either MITER, BEVEL, ROUND

OPTINLINE
void fill(float Gray);
void fill(float Gray,float Alpha);
OPTINLINE
void fill(float Red,float Green,float Blue);
void fill(float Red,float Green,float Blue,float Alpha);
OPTINLINE
void noFill();

void point(float x,float y);
OPTINLINE
void line(float  x1,float  y1,float  x2,float  y2);
OPTINLINE
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

OPTINLINE
void rect(float a,float  b,float  c,float  d);
void rect(float a,float  b,float  c,float  d,float r);
OPTINLINE
void rectMode(int mode);/// Parameter: mode 	int: either CORNER, CORNERS, CENTER, or RADIUS

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
