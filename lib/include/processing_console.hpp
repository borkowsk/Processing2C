/// \file processing_console.hpp
/// \brief Związane z konsolą funkcje print i println oraz formatowanie
/// \author 'borkowsk'
/// \ingroup console
///
// //////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////
#pragma once
#ifndef PROCESSING_CONSOLE_H
#define PROCESSING_CONSOLE_H

///\namespace Processing \brief P2C compatibility libraries
namespace Processing
{
  class _string_param;

  //void print();//To bez sensu
  void print(_string_param _p1);//The print() function writes to the console
  void print(_string_param _p1,_string_param _p2);
  void print(_string_param _p1,_string_param _p2,_string_param _p3);
  void print(_string_param _p1,_string_param _p2,_string_param _p3,_string_param _p4,
             _string_param _p5="",_string_param _p6="",_string_param _p7="",_string_param _p8=""); ///< TODO MORE! (up to 10)

  void println();
  void println(_string_param _p1);//The println() function writes to the console. Each call to this function creates also a new line.
  void println(_string_param _p1,_string_param _p2);
  void println(_string_param _p1,_string_param _p2,_string_param _p3);
  void println(_string_param _p1,_string_param _p2,_string_param _p3,_string_param _p4,
               _string_param _p5="",_string_param _p6="",_string_param _p7="",_string_param _p8=""); ///< TODO MORE! (up to 10)
               
  String hex(int num); //Converts an int, byte, char, or color (?) to a String containing the equivalent hexadecimal notation. 
  String hex(int num,int digits); //jest
  String binary(int num); //Converts an int, byte, char, or color (?) to a String containing the equivalent binary notation.
  String binary(int value,int digits);//TODO

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

  String nfs(double num);
  String nfs(double num,int digits);
  String nfs(double num,int left,int right);

  String nfs(sarray<int> nums);
  String nfs(sarray<int> nums,int digits);
  String nfs(sarray<int> nums,int left,int right);

  String nfs(sarray<float> nums);
  String nfs(sarray<float> nums,int digits);
  String nfs(sarray<float> nums,int left,int right);

  String nfs(sarray<double> nums);
  String nfs(sarray<double> nums,int digits);
  String nfs(sarray<double> nums,int left,int right);

  String nfc(double num);
  String nfc(double num,int digits);
  String nfc(double num,int left,int right);

  String nfc(sarray<int> nums);
  String nfc(sarray<int> nums,int digits);
  String nfc(sarray<int> nums,int left,int right);

  String nfc(sarray<float> nums);
  String nfc(sarray<float> nums,int digits);
  String nfc(sarray<float> nums,int left,int right);

  String nfc(sarray<double> nums);
  String nfc(sarray<double> nums,int digits);
  String nfc(sarray<double> nums,int left,int right);
  
}//END of namespace Processing
/* ****************************************************************** */
/*               PROCESSING2C  version 2021-12-23                     */
/* ****************************************************************** */
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                   */
/*            W O J C I E C H   B O R K O W S K I                     */
/*    Instytut Studiów Społecznych Uniwersytetu Warszawskiego         */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI    */
/*    RG : https://www.researchgate.net/profile/Wojciech-Borkowski    */
/*    GITHUB: https://github.com/borkowsk                             */
/*                                                                    */
/*                                 (Don't change or remove this note) */
/* ****************************************************************** */
#endif
