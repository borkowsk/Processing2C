/** \brief Processing like main window
 * \file processing_window.hpp
 * \classes processing_window; color
 * \ingroup drawing , rtm
 * \author borkowsk
 * @date 2024-10-11 (last modification)
 */
// //////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////
#pragma once
#ifndef PROCESSING_WINDOW_H
#define PROCESSING_WINDOW_H

#ifndef OPT_INLINE
#define OPTINLINE /* EMPTY */
#endif

#include<cstdint>
#include<cassert>

///\namespace Processing \brief P2C compatibility libraries
namespace Processing
{
/// An announcement declaration for type that implements various conversions to a String
class _string_param;
/// An announcement declaration for mode of closing arcs
extern const int OPENPIE; //default arc open_mode

//TODO - make file for internal variables? Exp.: "processing_ivars.hpp" ?
///\brief Mode for driving ellipses \ingroup drawing
extern int _ELLIPSE_MODE; //=CENTER?
///\brief Mode for driving rectangles \ingroup drawing
extern int _RECT_MODE; //=CORNER?
///\brief Mode for driving heads of lines \ingroup drawing
extern int STROKE_CAP; //=SQUARE?;
///\brief Mode for driving conjunctions of lines \ingroup drawing
extern int STROKE_JOIN; //=MITER?;
///\brief Mode for horizontal text alignment \ingroup drawing
extern int _TEXT_HORIZONTAL_AL; //=LEFT;
///\brief Mode for vertical text alignment \ingroup drawing
extern int _TEXT_VERTICAL_AL; //=TOP;


/// \brief Interface for the main window class that mimics the Processing window
/// \ingroup rtm
class processing_window_base
{
  public:
    virtual ~processing_window_base();  //!< \brief DESTRUCTOR is virtual
    virtual void exit();
    virtual void before_setup(int argc, const char *argv[]);
    virtual void settings()=0;          //!< \brief May be provided!
    virtual void setup()=0;             //!< \brief Must be provided!
    virtual void before_draw();         //!< \brief Cleaning _keyPressed & _mousePressed - @todo TMP METHOD - do it more clever!
    virtual void draw(){}               //!< \brief EMPTY DRAW()
    virtual void after_draw();          //!< \brief Calculate frameRate and _INTERNAL_DELAY
    virtual void check_events();        //!< \brief If events are in queue, they are processed
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

/// \brief The classes of the main window that mimics the Processing window
/// \methods The methods of this class are all empty.
/// They are defined in the library in individual source files and are linked
/// only if the user does not define his own versions of these methods.
/// \note _processing_window_instance is a single allowed object of this class
/// \ingroup rtm
extern class processing_window: public processing_window_base
{
  bool _loop=true;
  public:
  bool inLoop() {return _loop;}
  void settings() override;
  void setup() override ;
  void draw() override ;
  void exit() override ;
  void onMouseClicked() override ;
  void onMousePressed() override ;
  void onMouseReleased() override ;
  void onMouseMoved() override ;
  void onMouseDragged() override ;
  void onKeyPressed() override ;
  void onKeyReleased() override ;
  friend void loop();
  friend void noLoop();
  ~processing_window() override;
} _processing_window_instance;

typedef processing_window AppletDummy;
typedef Processing::ptr<AppletDummy> pApplet;

/// \brief Alias for _processing_window_instance
/// \ingroup rtm
extern processing_window *const surface; //=&_processing_window_instance;

/// \brief Stops continuously executing the code within draw().
/// \note By default, Processing loops through draw() continuously,
/// executing the code within it. However, the draw() loop may be stopped
/// by calling noLoop(). In that case, the draw() loop can be resumed with loop().
/// \see \a https://processing.org/reference/noLoop_.html
/// \ingroup rtm
inline void noLoop()
{
    _processing_window_instance._loop=false;
}

/// \brief Resume execution of draw()
/// \note By default, Processing loops through draw() continuously,
/// executing the code within it. However, the draw() loop may be stopped
/// by calling noLoop(). In that case, the draw() loop can be resumed with loop().
/// \see \a https://processing.org/reference/loop_.html
/// \ingroup rtm
inline void loop()
{
    _processing_window_instance._loop=true;
}

/// \brief Defines the dimension of the display window width and height in units of pixels.
/// \param width
/// \param height
/// \note In Processing2C program in this point of run the window is made and begin to be visible
/// \see \a https://processing.org/reference/size_.html
void size(int width,int height);

/// \brief Defines the dimension of the display as size of whole screen
/// \note In Processing2C program in this point of run the window is made and begin to be visible
/// \see \a https://processing.org/reference/fullScreen_.html
void fullScreen();

/// \brief Specifies the number of frames to be displayed every second.
/// \note function corresponds to frameRate () in Processing. The name had to be changed because
/// 'framRate' means the variable from which you can read the currently achieved number of frames.
/// \param fps : requested number of frames per second
/// \see \a https://processing.org/reference/frameRate_.html
void setFrameRate(float fps); ///Set desired frame rate

// Global "system" variables
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//TODO - make file for internal variables? Exp.: "processing_ivars.hpp" ?

///\var width of a screen/window/virtual screen  \ingroup rtm
extern const int& width;
///\var height of a screen/window/virtual screen  \ingroup rtm
extern const int& height;
///\var width (in real pixels) of a screen/window/virtual screen  \ingroup rtm
extern const int& pixelWidth;
///\var height (in real pixels) of a screen/window/virtual screen  \ingroup rtm
extern const int& pixelHeight;

///\var Approximated frame rate achieved;  \ingroup rtm
extern const float& frameRate;
///\var The system variable frameCount contains the number of frames that have been displayed since the program started. \ingroup rtm
extern const int&   frameCount;
///\var Internal variable used by set_delay(); \ingroup rtm
/// DO NOT USE DIRECTLY!!!
extern int _INTERNAL_DELAY; //=100; //

/// The mousePressed variable stores whether or not a mouse button is currently being pressed.
/// The value is true when any mouse button is pressed, and false if no button is pressed.
/// The mouseButton variable can be used to determine which button has been pressed.
extern const bool& mousePressed;

///Writeable version. \ingroup rtm
extern       bool& mousePressedWr; ///< Rather not used in Processing examples.


extern const int&  mouseButton; ///< When a mouse button is pressed, the value of this is set to either LEFT, RIGHT, or CENTER,
                               ///< depending on which button is pressed. If no button is pressed, mouseButton may be reset to 0.
extern const int&  mouseX; ///< always contains the current horizontal coordinate of the mouse.
extern const int&  mouseY; ///< always contains the current vertical coordinate of the mouse.
                           ///< Note that Processing can only track the mouse position when the pointer is over the current window

extern const int&  pmouseX; ///< always contains the previous horizontal coordinate of the mouse.
extern const int&  pmouseY; ///< always contains the previous vertical coordinate of the mouse.
                            ///< Note that Processing can only track the mouse position when the pointer is over the current window

/// For non-ASCII keys, use the `keyCode` variable. The keys included in the ASCII specification (BACKSPACE, TAB, ENTER, RETURN, ESC, and DELETE)
/// do not require checking to see if the key is coded, and you should simply use the key variable instead of keyCode
/// If you're making cross-platform projects, note that the ENTER key is commonly used on PCs and Unix and the RETURN key is used instead on Macintosh.
/// Check for both ENTER and RETURN to make sure your program will work for all platforms.
extern       char    key;     ///< always contains the value of the most recent key on the keyboard that was used (either pressed or released)
extern       int     keyCode; ///< The variable keyCode is used to detect special keys such as the arrow keys (UP, DOWN, LEFT, and RIGHT)
                              ///< as well as ALT, CONTROL, and SHIFT.
                              ///< There are issues with how keyCode behaves across different renderers and operating systems.
                              ///< Watch out for unexpected behavior as you switch renderers and operating systems.
                              ///< When checking for these keys, it can be useful to first check if the key is coded.
                              ///< This is done with the conditional if (key == CODED), as shown in the example KEYBOARD.
extern const bool&   keyPressed; ///< is true if any key is pressed and false if no keys are pressed.

//  The most important drawing functions
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @todo Not implemented!
void noSmooth();

/// @todo Not implemented!
void smooth();

/// \brief The background() function sets the color used for the background of the Processing window.
/// \note The default background is light gray.
/// \details
///     This function is typically used within draw() to clear the display window at the beginning of each frame,
///     but it can be used inside setup() to set the background on the first frame of animation or
///     if the background need only be set once.
void background(float gray);
void background(float gray,float  alpha);
void background(float v1,float v2,float v3);
void background(float v1,float v2,float v3,float  alpha);

/// \param col - 3D color + alpha channel
inline void background(const color& col)
{
    background(col.red(),col.green(),col.blue(),col.alfa());
}

#ifndef PROCESSING_INLINES_H
void stroke(float Gray);
void stroke(float Gray,float Alpha);
void stroke(float Red,float Green,float Blue);
void stroke(float Red,float Green,float Blue,float Alpha);
void stroke(const color col);
void noStroke();
void strokeWeight(float Weight); // Parameters	weight 	float: the weight (in pixels) of the stroke
#endif

void strokeCap(int cap);   ///< \param	cap 	int: either SQUARE, PROJECT, or ROUND
void strokeJoin(int join); ///< \param	join 	int: either MITER, BEVEL, ROUND

#ifndef PROCESSING_INLINES_H
void noFill();
void fill(float Gray);
void fill(float Gray,float Alpha);
void fill(float Red,float Green,float Blue);
void fill(float Red,float Green,float Blue,float Alpha);
void fill(const color col);
#endif


#ifndef PROCESSING_INLINES_H
void point(float x,float y);
#endif

#ifndef PROCESSING_INLINES_H
void line(float  x1,float  y1,float  x2,float  y2);
#endif

#ifndef PROCESSING_INLINES_H
/// \brief "ellipse" draws an ellipse (oval) to the screen.
/// An ellipse with equal width and height is a circle.
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
void ellipse(float a,float  b,float  c,float  d);
void ellipseMode(int mode); /// Parameters	mode 	int: either CENTER, RADIUS, CORNER, or CORNERS

/// \brief Simplified circle.
void circle(int x,int y,int r);
#endif

/// \brief Functions for driving elliptical arc.
///  \param a 	float: x-coordinate of the ellipse
///  \param b 	float: y-coordinate of the ellipse
///  \param c 	float: width of the ellipse by default
///  \param d 	float: height of the ellipse by default
///  \param start 	float: angle to start the arc, specified in radians
///  \param stop 	float: angle to stop the arc, specified in radians
///  \param mode arc connecting mode (STILL IGNORED?)
void arc(float a,float  b,float  c,float  d,float  start,float  stop,int  mode=Processing::OPENPIE);

/// @brief A triangle is a plane created by connecting three points.
/// @details
///         The first two arguments specify the first point, the middle two arguments specify the second point,
///         and the last two arguments specify the third point.
void triangle(
        float     x1,      //!< x-coordinate of the first point
        float     y1,      //!< y-coordinate of the first point
        float     x2,      //!< x-coordinate of the second point
        float     y2,      //!< y-coordinate of the second point
        float     x3,      //!< x-coordinate of the third point
        float     y3       //!< y-coordinate of the third point
    );

/// \brief 	A quad is a quadrilateral, a four sided polygon.
/// \details
///         It is similar to a rectangle, but the angles between its edges are not constrained to ninety degrees.
///         The first pair of parameters (x1,y1) sets the first vertex and the subsequent pairs should proceed
///         clockwise or counter-clockwise around the defined shape.
/// \param x1 float: x-coordinate of the first corner
/// \param y1 float: y-coordinate of the first corner
/// \param x2 float: x-coordinate of the second corner
/// \param y2 float: y-coordinate of the second corner
/// \param x3 float: y-coordinate of the second corner
/// \param y3 float: x-coordinate of the third corner
/// \param x4 float: x-coordinate of the fourth corner
/// \param y4 float: y-coordinate of the fourth corner
void quad( float  x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

#ifndef PROCESSING_INLINES_H

/// "rect" draws a rectangle to the screen. A rectangle is a four-sided shape with every angle at ninety degrees.
/// By default, the first two parameters set the location of the upper-left corner, the third sets the width, and
/// the fourth sets the height.
///
//  Parameters:
/// \param a 	float: x-coordinate of the rectangle by default
/// \param b 	float: y-coordinate of the rectangle by default
/// \param c 	float: width of the rectangle by default
/// \param d 	float: height of the rectangle by default
void rect(float a,float  b,float  c,float  d);

/// \param r 	float: radii for all four corners
/// @todo NOT IGNORE CORNERS WHERE POSSIBLE.
void rect(float a,float  b,float  c,float  d,float r);

/// \param tl 	float: radius for top-left corner
/// \param tr 	float: radius for top-right corner
/// \param br 	float: radius for bottom-right corner
/// \param bl 	float: radius for bottom-left corner
/// @todo NOT IGNORE CORNERS WHERE POSSIBLE.
void rect(float a,float b,float c,float d,float tl,float tr,float br,float bl);

/// \note Rect mode could be either CORNER, CORNERS, CENTER, or RADIUS
void rectMode(int mode); /// Parameter: mode 	int: either CORNER, CORNERS, CENTER, or RADIUS

//  Parameters:
/// \param a 	float: x-coordinate of the rectangle by default
/// \param b 	float: y-coordinate of the rectangle by default
/// \param extent float: lenght of side.
/// \note Meaning of parameters depends on rectMode() but in mode CORNERS
///       this particular function behave stupid in Processing 3.x at least.
void square(float a,float  b,float extent);
#endif

/// Executes the code within draw() one time. This functions allows the program to update the display window only when necessary, for example when an event registered by mousePressed() or keyPressed() occurs.
/// In structuring a program, it only makes sense to call redraw() within events such as mousePressed(). This is because redraw() does not run draw() immediately (it only sets a flag that indicates an update is needed).
/// The redraw() function does not work properly when called inside draw(). To enable/disable animations, use loop() and noLoop().
void redraw();

/// \param kind 	int: either ARROW, CROSS, HAND, MOVE, TEXT, or WAIT
/// \todo Cursors not implemented!
void cursor(int kind);
void cursor();
void noCursor();

// \param img 	PImage: any variable of type PImage
// \param   x 	int: the horizontal active spot of the cursor
// \param   y 	int: the vertical active spot of the cursor
//void cursor(PImage img);
//void cursor(PImage img,int x,int y);

void delay(int napTime); ///< The delay() function halts for a specified time. Delay times are specified in thousandths of a second.
                         ///< \Param	napTime 	int: milliseconds to pause before running draw() again

inline
void pixelDensity(int density){} ///< DO NOTHING! \Param	density 	int: 1 or 2

inline
int displayDensity(int display=0) {return 1;} ///< \Param	display 	int: the display number to check

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
#endif
