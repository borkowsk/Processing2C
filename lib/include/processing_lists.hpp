// processing_lists.h
#pragma once
#ifndef PROCESSING_LISTS_H
#define PROCESSING_LISTS_H
///
///
///
#include <vector>
namespace Processing
{

template<class T>
class ArrayList:public std::vector<T>
{
    ArrayList& add(const T&);
};


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
