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
#endif
