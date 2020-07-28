// processing_console.h
#pragma once
#ifndef PROCESSING_CONSOLE_H
#define PROCESSING_CONSOLE_H
///
///
///
namespace Processing
{
  class _print_param:public String
  {
    public:
    _print_param(String p):String(p){}
    _print_param(const char *p):String(p){}
    _print_param(double p);
    _print_param(float  p);
    _print_param(int    p);
    _print_param(void*  p);
    template<class T>
    _print_param(ptr<T> p);
  };




  //void print();//To bez sensu
  void print(_print_param _p1);
  void print(_print_param _p1,_print_param _p2);
  void print(_print_param _p1,_print_param _p2,_print_param _p3);
  void print(_print_param _p1,_print_param _p2,_print_param _p3,_print_param _p4,
             _print_param _p5="",_print_param _p6="",_print_param _p7="",_print_param _p8="");

  void println();
  void println(_print_param _p1);
  void println(_print_param _p1,_print_param _p2);
  void println(_print_param _p1,_print_param _p2,_print_param _p3);
  void println(_print_param _p1,_print_param _p2,_print_param _p3,_print_param _p4,
             _print_param _p5="",_print_param _p6="",_print_param _p7="",_print_param _p8="");
}//END of namespace Processing
#endif
