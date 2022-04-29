/// A simple class to use a String as a lookup for an integer value. 
/// String "keys" are associated with int values.
/// \warning Implementation is based on an ordered_map not a hash map, and is not complete;
/// \file processing_IntDict.hpp
/// \brief IMPLEMENTATION OF Processing LIKE IntDict
/// \author 'borkowsk'
/// \ingroup JAVA_compatibility
/// \see
/// * file:///.../processing-3.5.4/modes/java/reference/IntDict.html
/// * https://processing.org/reference/IntDict.html
/// * https://en.cppreference.com/w/cpp/container/map
/// \alternative
/// * https://en.cppreference.com/w/cpp/utility/hash
/// * https://en.cppreference.com/w/cpp/container/unordered_map
// This file is part of the Processing2C++ Library. See bottom lines.
//*///////////////////////////////////////////////////////////////////
#pragma once
#ifndef PROCESSING_StringDict_H
#define PROCESSING_StringDict_H

#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_string.hpp"
#include <map>

///\namespace Processing \brief P2C compatibility libraries
namespace Processing {
//*///////////////////////////////////////////////////////////////////

class IntDict: private std::map<String,int>, virtual public _self_printable
{
public:
        using     std::map<String,int>::begin;
        using     std::map<String,int>::end;
        using     std::map<String,int>::operator[];

        /// Destructor
        ~IntDict() = default ;

        ///Constructor(s)
        IntDict() = default;
        IntDict(IntDict const&) = default;  //!< copy-constructor (not aggregate initialization)
        //IntDict(pairs);
        //IntDict(row);

        /// Printing device for whole container
        String print() const; //!< forced by _self_printable

        int     size() const; //!<	Returns the number of key/value pairs
        void    clear(); //!<	Remove all entries
        
        ///...
        //iterable<int>        values(); //!< Return the internal array being used to store the values

        sarray<String>  keyArray() const; //!< Return a copy of the internal keys array
        
        ///...
        sarray<int>  valueArray() const; //!< Create a new array and copy each of the values into it
        
        ///...
        int get(const String&) const; //!< Return a value for the specified key
        int get(const String& key,int alternate) const;
        
        ///...
        void set(const String& key,int value); //!< Create a new key/value pair or change the value of one
        
        bool hasKey(const String& key) const; //!< Check if a key is a part of the data structure
        int  remove(const String& key); //!< Remove a key/value pair
        
        /// Sorting tools:
        void sortKeys(); //!< Sort the keys alphabetically
        void sortKeysReverse(); //!< Sort the keys alphabetically in reverse
        void sortValues(); //!< Sort by values in ascending order
        void sortValuesReverse(); //!< Sort by values in descending order
        
        /// Arithmetics:
        void add(const String& key,int val); //!< Add to a value
        void sub(const String& key,int val); //!< Subtract from a value
        void div(const String& key,int val); //!< Divide a value
        void mult(const String& key,int val);//!< Multiply a value
};


    inline int IntDict::size() const
    {
        return std::map<String,int>::size();
    }

    inline void IntDict::clear()
    {
        std::map<String,int>::clear();
    }

    inline void IntDict::set(const String &key,int value)
    {
        (*this)[key]=value;
    }

    inline int IntDict::get(const String &key)  const
    {
        auto where=find(key);
        return where->second;
    }

    inline int IntDict::get(const String &key, int alternate) const
    {
        auto where=find(key);
        if(where != std::map<String,int>::end())
            return where->second;
        else
            return alternate;
    }

    inline bool IntDict::hasKey(const String &key) const
    {
        auto where=find(key);
        return where != std::map<String,int>::end();
    }

    inline int IntDict::remove(const String &key)
    {
        auto where=find(key);
        float ret=where->second;
        std::map<String,int>::erase(where);
        return ret;
    }

    /// Processing like implementation produce something like that:
    /// FloatDict size=3 { "coffee": 1, "flour": 12, "tea": 23 }
    inline String IntDict::print() const
    {
        String ret="IntDict size=";
        ret+= std::to_string(size());
        ret+=" {";
        for (const auto& [key, value] : *this )
        {
            ret+=" \""+ key +"\": "+ std::to_string(value) + ",";
        }
        ret+=" }";
        return ret;
    }

    inline void IntDict::add(const String &key, int val)
    {
        (*this)[key]+=val;
    }

    inline void IntDict::sub(const String &key, int val)
    {
        (*this)[key]-=val;
    }

    inline void IntDict::div(const String &key, int val)
    {
        (*this)[key]/=val;
    }

    inline void IntDict::mult(const String &key, int val)
    {
        (*this)[key]*=val;
    }

    typedef Processing::self_printable_ptr<IntDict> pIntDict;
}/*_endOfNamespace*/
#endif
/* ****************************************************************** */
/*               PROCESSING2C  version 2022-04-29                     */
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

