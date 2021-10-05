// processing_window.hpp
#pragma once
#ifndef PROCESSING_WINDOW_H
#define PROCESSING_WINDOW_H

#ifndef OPTINLINE
#define OPTINLINE /* EPMTY */
#endif

#include<cstdint>

namespace Processing
{

extern int _ELLIPSE_MODE;//=CENTER?
extern int _RECT_MODE;//=CORNER?
extern int _STROKE_CAP;//=SQUARE?;
extern int _STROKE_JOIN;//=MITER?;
extern int _TEXT_HORIZONTAL_AL;//=LEFT;
extern int _TEXT_VERTICAL_AL;//=TOP;

class _string_param;//Zapowiadająca

class processing_window_base
{
  public:
    virtual ~processing_window_base();
    virtual void exit();
    virtual void before_setup(int argc, const char *argv[]);
    virtual void setup()=0;//Must be provided!
    virtual void before_draw();//Cleaning _keyPressed & _mousePressed - TMP METHOD - TODO more clever!
    virtual void draw(){} //EMPTY DRAW()
    virtual void after_draw();//Calculate frameRate and _INTERNAL_DELAY
    virtual void check_events();//If events are in queue, they are processed
    virtual void setTitle(_string_param bar);
    //Event handlers
    virtual void onMouseClicked()=0;
    virtual void onMousePressed()=0;
    virtual void onMouseReleased()=0;
    virtual void onMouseMoved()=0;
    virtual void onMouseDragged()=0;
    virtual void onKeyPressed()=0;
    virtual void onKeyReleased()=0;
};

extern class processing_window: public processing_window_base
{
  bool _loop=true;
  public:
  bool inLoop() {return _loop;}
  void setup();
  void draw();
  void exit();
  void onMouseClicked();
  void onMousePressed();
  void onMouseReleased();
  void onMouseMoved();
  void onMouseDragged();
  void onKeyPressed();
  void onKeyReleased();
  friend void loop();
  friend void noLoop();
} _processing_window_instance;

extern processing_window *const surface;//=&_processing_window_instance;

inline void loop()
{
    _processing_window_instance._loop=true;
}

inline void noLoop()
{
    _processing_window_instance._loop=false;
}

/// Class color
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class color
{
  public:
    std::uint32_t val;
    color(std::uint32_t value):val(value){}

    color(std::uint8_t R,std::uint8_t G,std::uint8_t B)
    {
        val=B + 256*G + 256*256*R;
    }

    color(std::uint8_t R,std::uint8_t G,std::uint8_t B,std::uint8_t alfa):color(R,G,B)
    {
        val|=alfa<<24;//??? TODO! TEST IT!
    }

    std::uint8_t alfa() const  { return (val & 0xFF000000)>>24; }

    std::uint8_t red() const   { return (val & 0x00FF0000)>>16; }

    std::uint8_t green() const { return (val & 0x0000FF00)>>8; }

    std::uint8_t blue() const  { return (val & 0x000000FF); }
    
    operator const std::uint32_t () const { return val; }
};

//inline String hex(const color& col) { return Processing::hex(col.val); }
//inline String binary(const color& col) { return Processing::binary(col.val); }

inline float  alfa(const color& col) { return col.alfa(); }
inline float   red(const color& col) { return col.red(); }
inline float green(const color& col) { return col.green(); }
inline float  blue(const color& col) { return col.blue(); }

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
extern       bool& mousePressedWr;//Writeable version. Rather not used in Processing examples.

extern const int&  mouseButton;/// When a mouse button is pressed, the value of this is set to either LEFT, RIGHT, or CENTER,
                               /// depending on which button is pressed. If no button is pressed, mouseButton may be reset to 0.
extern const int&  mouseX;/// always contains the current horizontal coordinate of the mouse.
extern const int&  mouseY;/// always contains the current vertical coordinate of the mouse.
                          /// Note that Processing can only track the mouse position when the pointer is over the current window

extern const int&  pmouseX;/// always contains the previous horizontal coordinate of the mouse.
extern const int&  pmouseY;/// always contains the previous vertical coordinate of the mouse.
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

// The background() function sets the color used for the background of the Processing window. The default background is light gray.
// This function is typically used within draw() to clear the display window at the beginning of each frame, but it can be used
// inside setup() to set the background on the first frame of animation or if the backgound need only be set once.
void background(float gray);
void background(float gray,float  alpha);
void background(float v1,float v2,float v3);
void background(float v1,float v2,float v3,float  alpha);

OPTINLINE
void stroke(float Gray);
void stroke(float Gray,float Alpha);
OPTINLINE
void stroke(float Red,float Green,float Blue);
void stroke(float Red,float Green,float Blue,float Alpha);
void stroke(const color& col);
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
void fill(const color& col);
OPTINLINE
void noFill();

void point(float x,float y);
OPTINLINE
void line(float  x1,float  y1,float  x2,float  y2);

/// "ellipse" draws an ellipse (oval) to the screen. An ellipse with equal width and height is a circle.
/// By default, the first two parameters set the location, and the third and fourth parameters set
/// the shape's width and height.
///
/// Parameters:
///  a 	float: x-coordinate of the ellipse
///  b 	float: y-coordinate of the ellipse
///  c 	float: width of the ellipse by default
///  d 	float: height of the ellipse by default
///  start 	float: angle to start the arc, specified in radians
///  stop 	float: angle to stop the arc, specified in radians

OPTINLINE
void ellipse(float a,float  b,float  c,float  d);
void arc(float a,float  b,float  c,float  d,float  start,float  stop,int  mode=Processing::OPENPIE);


void ellipseMode(int mode);/// Parameters	mode 	int: either CENTER, RADIUS, CORNER, or CORNERS


/// "rect" draws a rectangle to the screen. A rectangle is a four-sided shape with every angle at ninety degrees.
/// By default, the first two parameters set the location of the upper-left corner, the third sets the width, and
/// the fourth sets the height.
///
/// Parameters
/// a 	float: x-coordinate of the rectangle by default
/// b 	float: y-coordinate of the rectangle by default
/// c 	float: width of the rectangle by default
/// d 	float: height of the rectangle by default
/// r 	float: radii for all four corners
/// tl 	float: radius for top-left corner
/// tr 	float: radius for top-right corner
/// br 	float: radius for bottom-right corner
/// bl 	float: radius for bottom-left corner
/// Rect mode could be either CORNER, CORNERS, CENTER, or RADIUS
OPTINLINE
void rect(float a,float  b,float  c,float  d);
OPTINLINE
void rect(float a,float  b,float  c,float  d,float r);
OPTINLINE
void rect(float a,float b,float c,float d,float tl,float tr,float br,float bl);
OPTINLINE
void rectMode(int mode);/// Parameter: mode 	int: either CORNER, CORNERS, CENTER, or RADIUS

/// Executes the code within draw() one time. This functions allows the program to update the display window only when necessary, for example when an event registered by mousePressed() or keyPressed() occurs.
/// In structuring a program, it only makes sense to call redraw() within events such as mousePressed(). This is because redraw() does not run draw() immediately (it only sets a flag that indicates an update is needed).
/// The redraw() function does not work properly when called inside draw(). To enable/disable animations, use loop() and noLoop().
void redraw();


/// Parameters:
/// kind 	int: either ARROW, CROSS, HAND, MOVE, TEXT, or WAIT
/// img 	PImage: any variable of type PImage
///   x 	int: the horizontal active spot of the cursor
///   y 	int: the vertical active spot of the cursor
void cursor();
void cursor(int kind);
void noCursor();
//void cursor(PImage img);
//void cursor(PImage img,int x,int y);

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
/*               PROCESSING2C  version 2020-11-15                   */
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
