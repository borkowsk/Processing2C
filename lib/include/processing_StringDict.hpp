/// A simple class to use a String as a lookup for an String value. 
/// String "keys" are associated with String values.
/// \file processing_StringDict.hpp
/// \brief IMPLEMENTATION OF Processing LIKE StringDict
/// \author 'borkowsk'
/// \ingroup JAVA_compatibility
/// \see file:///.../processing-3.5.4/modes/java/reference/StringDict.html
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

class StringDict: private std::map<String,String>, virtual public _self_printable {
    public:
        ///Constructor(s)	
        StringDict() = default;
        //StringDict(pairs);
        //StringDict(row);

        /// Destructor
        ~StringDict() = default ;

        String print() const; //!< forced by _self_printable

        int size(); //!<	Returns the number of key/value pairs
        void clear() { std::map<String,String>::clear(); } //!<	Remove all entries

        ///file:///home/borkowsk/processing-3.5.4/modes/java/reference/StringDict_values_.html
        //iterable<String>        values(); //!< Return the internal array being used to store the values

        sarray<String> keyArray(); //!< Return a copy of the internal keys array

        ///file:///home/borkowsk/processing-3.5.4/modes/java/reference/StringDict_valueArray_.html
        sarray<String> valueArray(); //!< Create a new array and copy each of the values into it

        ///file:///home/borkowsk/processing-3.5.4/modes/java/reference/StringDict_get_.html
        String get(const String &key); //!< Return a value for the specified key
        String get(const String &key,const String &alternate);

        ///file:///home/borkowsk/processing-3.5.4/modes/java/reference/StringDict_set_.html
        void set(const String &key,const String &value); //!< Create a new key/value pair or change the value of one

        bool hasKey(const String &key); //!< Check if a key is a part of the data structure
        String remove(const String &key); //!< Remove a key/value pair

        /// Sorting tools:
        void sortKeys(); //!< Sort the keys alphabetically
        void sortKeysReverse(); //!< Sort the keys alphabetically in reverse
        void sortValues(); //!< Sort by values in ascending order
        void sortValuesReverse(); //!< Sort by values in descending order
    };

    inline int StringDict::size()
    {
        return 0;
    }

    String StringDict::get(const String &key)
    {
        return String();
    }

    void StringDict::set(const String &key, const String &value)
    {

    }

    String StringDict::remove(const String &key)
    {
        return String();
    }

    /// Not implemented
    inline String StringDict::print() const
    {
        return String();
    }

    typedef Processing::self_printable_ptr<StringDict> pStringDict;
}/*_endOfNamespace*/
#endif
/* ****************************************************************** */
/*               PROCESSING2C  version 2022-04-28                     */
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

