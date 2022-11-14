/// \file processing_StringDict.hpp
/// \brief IMPLEMENTATION OF Processing LIKE StringDict
/// \author 'borkowsk'
/// \ingroup JAVA_compatibility
/// \see
/// * file:///.../processing-3.5.4/modes/java/reference/StringDict.html
/// * https://processing.org/reference/StringDict.html
/// * https://en.cppreference.com/w/cpp/container/map
/// \alternative
/// * https://en.cppreference.com/w/cpp/utility/hash
/// * https://en.cppreference.com/w/cpp/container/unordered_map
//*//////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
//*//////////////////////////////////////////////////////////////////////
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

/// \brief A simple class to use a String as a lookup for an String value.
/// String "keys" are associated with String values.
/// \warning Implementation is based on an ordered_map not a hash map, and is not complete;
class StringDict: private std::map<String,String>, virtual public _self_printable {
    public:
        using     std::map<String,String>::begin;
        using     std::map<String,String>::end;
        using     std::map<String,String>::operator[];

        /// \brief Destructor
        ~StringDict() = default ;

        // Constructor(s)
        // //////////////
        StringDict() = default;                   //!< \brief default constructor
        StringDict(StringDict const&) = default;  //!< \brief copy constructor (not aggregate initialization)
        //StringDict(pairs);
        //StringDict(row);

        /// \brief Printing device for whole container
        String print() const; //!< \note Printing forced by `_self_printable::`

        int size() const; //!< \brief	Returns the number of key/value pairs
        void clear();  //!< \brief	Remove all entries

        ///file:///home/borkowsk/processing-3.5.4/modes/java/reference/StringDict_values_.html
        //iterable<String>        values(); //!< Return the internal array being used to store the values

        sarray<String> keyArray() const; //!< \brief Return a copy of the internal keys array

        ///file:///home/borkowsk/processing-3.5.4/modes/java/reference/StringDict_valueArray_.html
        sarray<String> valueArray() const; //!< Create a new array and copy each of the values into it

        ///file:///home/borkowsk/processing-3.5.4/modes/java/reference/StringDict_get_.html
        String get(const String &key) const; //!< \brief Return a value for the specified key
        String get(const String &key,const String &alternate) const;

        ///file:///home/borkowsk/processing-3.5.4/modes/java/reference/StringDict_set_.html
        void set(const String &key,const String &value); //!< \brief Create a new key/value pair or change the value of one

        bool hasKey(const String &key) const; //!< \brief Check if a key is a part of the data structure
        String remove(const String &key); //!< \brief Remove a key/value pair

        // Sorting tools:
        void sortKeys(); //!< \brief Sort the keys alphabetically
        void sortKeysReverse(); //!< \brief Sort the keys alphabetically in reverse
        void sortValues(); //!< \brief Sort by values in ascending order
        void sortValuesReverse(); //!< \brief Sort by values in descending order
    };

    inline int StringDict::size() const
    {
        return std::map<String,String>::size();
    }

    inline void StringDict::clear()
    {
        std::map<String,String>::clear();
    }

    inline void StringDict::set(const String &key, const String &value)
    {
        (*this)[key]=value;
    }

    inline String StringDict::get(const String &key)  const
    {
        auto where=find(key);
        return where->second;
    }

    inline String StringDict::get(const String &key, const String &alternate) const
    {
        auto where=find(key);
        if(where != std::map<String,String>::end())
            return where->second;
        else
            return alternate;
    }

    inline bool StringDict::hasKey(const String &key) const
    {
        auto where=find(key);
        return where != std::map<String,String>::end();
    }

    inline String StringDict::remove(const String &key)
    {
        auto where=find(key);
        String ret=where->second;
        std::map<String,String>::erase(where);
        return ret;
    }

    /// Processing like implementation produce something like that:
    /// StringDict size=3 { "coffee": "black", "flour": "white", "tea": "green" }
    inline String StringDict::print() const
    {
        String ret="StringDict size=";
        ret+= std::to_string(size());
        ret+=" {";
        for (const auto& [key, value] : *this )
        {
            ret+=" \""+ key +"\": \""+ value + "\",";
        }
        ret+=" }";
        return ret;
    }

    typedef Processing::self_printable_ptr<StringDict> pStringDict;
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

