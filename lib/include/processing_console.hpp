// processing_console.h
#pragma once
#ifndef PROCESSING_CONSOLE_H
#define PROCESSING_CONSOLE_H
///
///
///
namespace Processing
{
  //void print();//To bez sensu
  void print(_string_param _p1);
  void print(_string_param _p1,_string_param _p2);
  void print(_string_param _p1,_string_param _p2,_string_param _p3);
  void print(_string_param _p1,_string_param _p2,_string_param _p3,_string_param _p4,
             _string_param _p5="",_string_param _p6="",_string_param _p7="",_string_param _p8="");

  void println();
  void println(_string_param _p1);
  void println(_string_param _p1,_string_param _p2);
  void println(_string_param _p1,_string_param _p2,_string_param _p3);
  void println(_string_param _p1,_string_param _p2,_string_param _p3,_string_param _p4,
               _string_param _p5="",_string_param _p6="",_string_param _p7="",_string_param _p8="");

  String nf(double num);
  String nf(double num,int digits);
  String nf(double num,int left,int right);

  String nf(sarray<int> nums);
  String nf(sarray<int> nums,int digits);
  String nf(sarray<int> nums,int left,int right);

  String nf(sarray<float> nums);
  String nf(sarray<float> nums,int digits);
  String nf(sarray<float> nums,int left,int right);

  String nf(sarray<double> nums);
  String nf(sarray<double> nums,int digits);
  String nf(sarray<double> nums,int left,int right);

  String nfp(double num);
  String nfp(double num,int digits);
  String nfp(double num,int left,int right);

  String nfp(sarray<int> nums);
  String nfp(sarray<int> nums,int digits);
  String nfp(sarray<int> nums,int left,int right);

  String nfp(sarray<float> nums);
  String nfp(sarray<float> nums,int digits);
  String nfp(sarray<float> nums,int left,int right);

  String nfp(sarray<double> nums);
  String nfp(sarray<double> nums,int digits);
  String nfp(sarray<double> nums,int left,int right);

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
