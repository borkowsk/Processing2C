/// \file  plist.cpp
/// \brief Non inline methods of FloatList IntList & StringList
/// \author 'borkowsk'
/// \date 2022-11-21 (last modification)
/// \ingroup PROCESSING_compatibility
/// \details
///     TODO - implement more of them!
///
/// \ingroup PROCESSING_compatibility
// //////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_lists.hpp"
#include "_impl_errors.h"

using namespace Processing;
using std::string;

float     FloatList::remove(int index)// 	Remove an element from the specified index
{
    //FIRST_TIME_ERRMESSAGE( string(" not implemented!") );
    //Processing::exit();
    FIRST_TIME_ERRMESSAGE( string(" This is very inefficient!") );
    float ret=*(this->begin() + index);
    std::vector<float>::erase(this->begin() + index);//Very slow in std::vector implementation!
    return ret;//TODO - is it compatible?
}

bool      FloatList::hasValue(float what)// 	Check if a number is a part of the list
{
    FIRST_TIME_ERRMESSAGE( string(" not implemented!") );
    Processing::exit(); std::exit(-1);
    return false;//TODO!!!
}

void      FloatList::add(int index,float amount)// 	Add to a value
{
    std::vector<float>::operator [] (index) += amount;
}

void      FloatList::sub(int index,float amount)// 	Subtract from a value
{
    std::vector<float>::operator [] (index) -= amount;
}

void      FloatList::mult(int index,float amount)// 	Multiply a value
{
    std::vector<float>::operator [] (index) *= amount;
}

void      FloatList::div(int index,float amount)// 	Divide a value
{
    std::vector<float>::operator [] (index) /=amount;
}

float     FloatList::min() // 	Return the smallest value
{
    FIRST_TIME_ERRMESSAGE(  string(" not implemented!")  );
    Processing::exit(); std::exit(-1);
    return -0;//TODO!!!
}

float     FloatList::max() // 	Return the largest value
{
    FIRST_TIME_ERRMESSAGE(  string(" not implemented!")  );
    Processing::exit(); std::exit(-1);
    return -0;//TODO!!!
}

void      FloatList::sort() // 	Sorts an array, lowest to highest
{
    std::sort(begin(),end());
}

void      FloatList::sortReverse() // 	Reverse sort, orders values from highest to lowest
{
    FIRST_TIME_ERRMESSAGE(  string(" not implemented!")  );
    Processing::exit(); std::exit(-1);
}

void      FloatList::reverse()// 	Reverse the order of the list elements
{
    FIRST_TIME_ERRMESSAGE(  string(" not implemented!")  );
    Processing::exit();  std::exit(-1);
}

void      FloatList::shuffle()// 	Randomize the order of the list elements
{
    FIRST_TIME_ERRMESSAGE(  string(" not implemented!")  );
    Processing::exit();  std::exit(-1);
}

sarray<float>     FloatList::array() const // 	Create a new array with a copy of all the values
{
    FIRST_TIME_ERRMESSAGE(  string(" not implemented!")  );
    Processing::exit();  std::exit(-1);
    return nullptr;
}

int      IntList::remove(int index)// 	Remove an element from the specified index
{
    FIRST_TIME_ERRMESSAGE( string(" This is very inefficient!") );
    int ret=*(this->begin() + index);
    std::vector<int>::erase(this->begin() + index);//Very slow in std::vector implementation!
    return ret;//TODO - is it compatible?
}

bool     IntList::hasValue(int   what) // 	Check if a number is a part of the list
{
    FIRST_TIME_ERRMESSAGE(  string(" not implemented!")  );
    Processing::exit(); std::exit(-1);
    return false;//TODO!!!
}

void     IntList::add(int index,int   amount)// 	Add to a value
{
    (*this)[index]+=amount;
}

void     IntList::sub(int index,int   amount)// 	Subtract from a value
{
    (*this)[index]-=amount;
}

void     IntList::mult(int index,int   amount)// 	Multiply a value
{
    (*this)[index]*=amount;
}

void     IntList::div(int index,int   amount)// 	Divide a value
{
    (*this)[index]/=amount;
}

int      IntList::min() // 	Return the smallest value
{
    FIRST_TIME_ERRMESSAGE(  string(" not implemented!")  );
    Processing::exit(); std::exit(-1);
    return 0xffffffff;//TODO!!!
}

int      IntList::max() // 	Return the largest value
{
    FIRST_TIME_ERRMESSAGE(  string(" not implemented!")  );
    Processing::exit(); std::exit(-1);
    return 0xefffffff;//TODO!!!
}

void     IntList::sort() // 	Sorts an array, lowest to highest
{
    std::sort(begin(),end());
}

void     IntList::sortReverse()// 	Reverse sort, orders values from highest to lowest
{
    FIRST_TIME_ERRMESSAGE(  string(" not implemented!")  );
    //std::sort(this->cbegin(),this->cend());//TODO TEST
    Processing::exit(); std::exit(-1);
}

void     IntList::reverse() // 	Reverse the order of the list elements
{
    FIRST_TIME_ERRMESSAGE(  string(" not implemented!")  );
    Processing::exit(); std::exit(-1);
}

void     IntList::shuffle() // 	Randomize the order of the list elements
{
    FIRST_TIME_ERRMESSAGE(  string(" not implemented!")  );
    Processing::exit(); std::exit(-1);
}

sarray<int>  IntList::array() const // 	Create a new array with a copy of all the values
{
    FIRST_TIME_ERRMESSAGE(  string(" not implemented!")  );
    Processing::exit(); std::exit(-1);
    return nullptr;
}

String   StringList::remove(int index) // 	Remove an element from the specified index
{
    FIRST_TIME_ERRMESSAGE( string(" This is very inefficient!") );
    String ret=*(this->begin() + index);
    std::vector<String>::erase(this->begin() + index);//Very slow in std::vector implementation!
    return ret;//TODO - is it compatible?
}

bool     StringList::hasValue(_string_param   what) // Check if a number is a part of the list
{
    FIRST_TIME_ERRMESSAGE(  string(" not implemented!")  );
    Processing::exit(); std::exit(-1);
    return false;//TODO!!!
}

void     StringList::sort() // 	Sorts an array, lowest to highest
{
    std::sort(this->begin(),this->end());
}


void     StringList::sortReverse() // 	Reverse sort, orders values from highest to lowest
{
    FIRST_TIME_ERRMESSAGE(  string(" not implemented!")  );
    //std::sort(this->cbegin(),this->cend());//TODO TEST
    Processing::exit(); std::exit(-1);
}


void     StringList::reverse() // 	Reverse the order of the list elements
{
    FIRST_TIME_ERRMESSAGE(  string(" not implemented!")  );
    Processing::exit(); std::exit(-1);
}


void     StringList::shuffle() // 	Randomize the order of the list elements
{
    FIRST_TIME_ERRMESSAGE(  string(" not implemented!")  );
    Processing::exit(); std::exit(-1);
}


void     StringList::lower() // 	Make the entire list lower case
{
    FIRST_TIME_ERRMESSAGE(  string(" not implemented!")  );
    Processing::exit(); std::exit(-1);
}


void     StringList::upper() // 	Make the entire list upper case
{
    FIRST_TIME_ERRMESSAGE(  string(" not implemented!")  );
    Processing::exit(); std::exit(-1);
}


sarray<int>  StringList::array()  const // 	Create a new array with a copy of all the values ???
{
    FIRST_TIME_ERRMESSAGE(  string(" not implemented!")  );
    Processing::exit(); std::exit(-1);
    return nullptr;
}
/* ******************************************************************
 *               PROCESSING2C  version 2022                         *
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

