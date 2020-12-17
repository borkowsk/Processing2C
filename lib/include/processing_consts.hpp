#ifndef PROCESSING_CONSTS_HPP
#define PROCESSING_CONSTS_HPP
namespace Processing
{
//CHAR CONSTANTS
const char16_t CODED=65535;
const char ESC=27;

//SETTINGS CONSTANTS
///ellipseMode(mode) parameters
const int CENTER=1;
const int RADIUS=2;
const int CORNER=3;
const int CORNERS=4;
///for arc's
const int OPENPIE=1;
const int OPEN=0;//Open CHORD
const int CHORD=2;
const int PIE=3;
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
//for textAligment
const int RIGHT=100;
const int LEFT=101;
const int TOP=102;
const int BOTTOM=103;
const int BASELINE=104;
}//END of namespace Processing

//FOR NOT IMPLEMENTED OR BADLY USED FUNCTIONS isted also in 'not_implemented.h'
#define FIRST_TIME_ERRMESSAGE( _XXX_ )   {  static int flag=0;\
                                            if(0==flag++) \
                                                std::cerr<<__FUNCTION__<< _XXX_ <<std::endl;\
                                         }

#define ALWAYS_ERRMESSAGE( _XXX_ )       { \
                                               std::cerr<<__FUNCTION__<< _XXX_ <<std::endl;\
                                         }



/********************************************************************/
/*               PROCESSING2C  version 2020-12-17                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
#endif // PROCESSING_CONSTS_HPP
