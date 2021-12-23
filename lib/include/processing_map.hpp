/// \file processing_map.hpp
/// \brief Java like map template
/// \author 'borkowsk'
/// \ingroup JAVA_compatibility
///
// //////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////
#pragma once
#ifndef PROCESSING_MAP_H
#define PROCESSING_MAP_H

#include "processing_lists.hpp"
#include <map>
#include <set>

///\namespace Processing \brief P2C compatibility libraries
namespace Processing
{

/** Hash table based implementation of the Map interface.
 * See: https://docs.oracle.com/javase/8/docs/api/java/util/HashMap.html
 * See: https://en.cppreference.com/w/cpp/container/map
 */
template<class K,class V>
class HashMap:public std::map<K,V>
{
public:
    class Entry:public std::map<K,V>::value_type
    {
    public:
        K getKey() const { return this->first;}
        V getValue() const { return this->second; }
        //Entry& operator -> () const { return *this;} //circular pointer references are not allowed
    };

    V   get(K key) ///Returns the value to which the specified key is mapped, or null if this map contains no mapping for the key.
    { return (*this)[key]; }

    V   put(K key, V value) ///Associates the specified value with the specified key in this map.
    { (*this)[key]=value;return value;}

    V   replace(K key, V value) ///Replaces the entry for the specified key only if it is currently mapped to some value.
    { (*this)[key]=value;return value;}

    sarray<const Entry*>    entrySet()///Returns a Set view of the mappings contained in this map.
    {
        sarray<const Entry*> ret{ new array<const Entry*>{ this->size() } };
        int i=0;
        for (auto&  ent: *this)
        {
            ret[i++]=(const Entry*)&ent;//HACK!!! Entry must not have any fields or virtual methods!
        }
        return ret;
    }

    String  print() const
    {
        String ret;
        ret+='{';
        for(auto val:*this)
        {
            ret+=val.first;
            ret+='=';
            ret+=val.second;
            ret+=' ';
        }
        ret+='}';
        return ret;
    }
};

template<class K,class V>
using pHashMap = self_printable_ptr< HashMap<K,V> >;

/*
template<class K,class V>
class sHashMap:public self_printable_ptr< HashMap<K,V> >
{
    ///INFO: Processing semantics for hash map
public:
    ~sHashMap(){}// Zwalnianie zasobów
    sHashMap(){}
    //sArrayList(std::initializer_list<T> lst);
    sHashMap(HashMap<K,V>* tab): self_printable_ptr< HashMap<K,V> >(tab){}
    HashMap<K,V>* operator -> () { return this->get();}

    auto    begin() { return this->get()->begin(); } //need C++14 !
    auto    end() { return this->get()->end(); } //need C++14 !
    int     size() const //Returns the number of elements in this list.
    { return this->get()->size(); }
};
*/

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
