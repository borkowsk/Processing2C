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
  void exit();
};

extern class processing_window: public processing_window_base
{
  static int width;
  static int height;
  public:
  void setup();
  void draw();
  void exit();
  void mouseClicked();
} _processing_window_instance;

extern const int& width;
extern const int& height;

void size(int width,int height);


void noSmooth();
void smooth();
void frameRate(float fps);

void saveFrame();
void saveFrame(const char* filename);

void strokeWeight(float Weight);
void stroke(float Gray);
void stroke(float Gray,float Alpha);
void stroke(float Red,float Green,float Blue);
void stroke(float Red,float Green,float Blue,float Alpha);
void noStroke();

void fill(float Gray);
void fill(float Gray,float Alpha);
void fill(float Red,float Green,float Blue);
void fill(float Red,float Green,float Blue,float Alpha);
void noFill();

void point(float x,float y);
void rect(float a,float  b,float  c,float  d);
void rectMode(int mode);// Parameter: mode 	int: either CORNER, CORNERS, CENTER, or RADIUS


void text(char c, float x,float y);
void text(const char* str,float x,float y);
void text(char chars[],int start,int stop,float x,float y);
void text(const char* str,float x1,float y1,float x2,float y2);
void text(float num,float x,float y);

}//END of namespace Processing
#endif
