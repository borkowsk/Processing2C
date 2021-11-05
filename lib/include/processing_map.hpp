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


template<class T,class X>
class sHashMap:public self_printable_ptr< HashMap<T,X> >
{
    ///INFO: Processing semantics for hash map
public:
    ~sHashMap(){}// Zwalnianie zasobów
    sHashMap(){}
    //sArrayList(std::initializer_list<T> lst);
    sHashMap(HashMap<T,X>* tab): self_printable_ptr< HashMap<T,X> >(tab){}
    HashMap<T,X>* operator -> () { return this->get();}
    auto  begin() { return this->get()->begin(); } //need C++14 !
    auto  end() { return this->get()->end(); } //need C++14 !
    int 	size() const //Returns the number of elements in this list.
    { return this->get()->size(); }
};


}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2021-11-05                   */
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
