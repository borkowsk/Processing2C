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
  public:
  void setup();
  void draw();
  void exit();
  void mouseClicked();
} _processing_window_instance;

void strokeWeight(float);

void stroke(float);
void stroke(float,float);
void stroke(float,float,float);
void stroke(float,float,float,float);

void fill(float);
void fill(float,float);
void fill(float,float,float);
void fill(float,float,float,float);

}//END of namespace Processing
#endif
