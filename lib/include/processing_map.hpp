// processing_map.h
#pragma once
#ifndef PROCESSING_MAP_H
#define PROCESSING_MAP_H
///
///
///
#include "processing_lists.hpp"
#include <map>
namespace Processing
{

template<class T,class X>
class HashMap:public std::map<T,X>
{

};


}//END of namespace Processing
#endif
