// Non inline methods of FloatList IntList & StringList 
#include "processing_consts.hpp"
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_lists.hpp"
#include "_impl_errors.h"

using namespace Processing;

float     FloatList::remove(int index)// 	Remove an element from the specified index
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
    return -0;//TODO!!!
}

bool      FloatList::hasValue(float what)// 	Check if a number is a part of the list
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
    return false;//TODO!!!
}

void      FloatList::add(int index,float amount)// 	Add to a value
{
    (*this)[index]+=amount;
}

void      FloatList::sub(int index,float amount)// 	Subtract from a value
{
    (*this)[index]-=amount;
}

void      FloatList::mult(int index,float amount)// 	Multiply a value
{
    (*this)[index]*=amount;
}

void      FloatList::div(int index,float amount)// 	Divide a value
{
    (*this)[index]/=amount;
}

float     FloatList::min()// 	Return the smallest value
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
    return -0;//TODO!!!
}

float     FloatList::max()// 	Return the largest value
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
    return -0;//TODO!!!
}

void      FloatList::sort()// 	Sorts an array, lowest to highest
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
}

void      FloatList::sortReverse()// 	Reverse sort, orders values from highest to lowest
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
}

void      FloatList::reverse()// 	Reverse the order of the list elements
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
}

void      FloatList::shuffle()// 	Randomize the order of the list elements
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
}

sarray<float>     FloatList::array()// 	Create a new array with a copy of all the values
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
    abort();
}

int      IntList::remove(int index)// 	Remove an element from the specified index
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
    //std::vector<int>::remove(index);//NOT SO EASY! :-D
    return -1;//TODO!!!
}

bool     IntList::hasValue(int   what)// 	Check if a number is a part of the list
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
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

int      IntList::min()// 	Return the smallest value
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
    return 0xffffffff;//TODO!!!
}

int      IntList::max()// 	Return the largest value
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
    return 0xefffffff;//TODO!!!
}

void     IntList::sort()// 	Sorts an array, lowest to highest
{
    //FIRST_TIME_ERRMESSAGE( " not implemented!" );
    std::sort(this->begin(),this->end());//TODO TEST
}

void     IntList::sortReverse()// 	Reverse sort, orders values from highest to lowest
{
    //FIRST_TIME_ERRMESSAGE( " not implemented!" );
    std::sort(this->cbegin(),this->cend());//TODO TEST
}

void     IntList::reverse()// 	Reverse the order of the list elements
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
}

void     IntList::shuffle()// 	Randomize the order of the list elements
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
}

sarray<int>  IntList::array()// 	Create a new array with a copy of all the values
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
    abort();
}

String   StringList::remove(int index)// 	Remove an element from the specified index
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
    return String("<NOT IMPLEMENTED>");//TODO!!!
}

bool     StringList::hasValue(_string_param   what)// Check if a number is a part of the list
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
    return false;//TODO!!!
}

void     StringList::sort()// 	Sorts an array, lowest to highest
{
    //FIRST_TIME_ERRMESSAGE( " not implemented!" );
     std::sort(this->begin(),this->end());//TODO TEST
}


void     StringList::sortReverse()// 	Reverse sort, orders values from highest to lowest
{
    //FIRST_TIME_ERRMESSAGE( " not implemented!" );
     std::sort(this->cbegin(),this->cend());//TODO TEST
}


void     StringList::reverse()// 	Reverse the order of the list elements
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
}


void     StringList::shuffle()// 	Randomize the order of the list elements
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
}


void     StringList::lower()// 	Make the entire list lower case
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
}


void     StringList::upper()// 	Make the entire list upper case
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
}


sarray<int>  StringList::array()// 	Create a new array with a copy of all the values ???
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
    abort();
}
/********************************************************************/
/*               PROCESSING2C  version 2021-10-26                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
