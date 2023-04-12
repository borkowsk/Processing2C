/**
 * \file pstrings.cpp
 * \brief Most commonly used strings functions
 * \ingroup strings
 * \author 'borkowsk'
 * \date 2023-03-17 (last modification)
 * \details
 *            see the bottom lines
 * \ingroup strings
 */
// //////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////
#include "processing_consts.hpp"
//#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
//#include "processing_console.hpp"
#include "_impl_errors.h"
#include <string>
#include <iostream> // Tylko z powodu _errMessage(Processing::String...)

//#define DEBUG 1 /* TODO??? */

///\namespace Processing2C compatibility libraries
namespace Processing
{

// /// @details ???
//String::~String()// Zwalnianie zasobów przez destruktor klasy bazowej
//{
//#ifdef DEBUG
//    FIRST_TIME_ERRMESSAGE( " called for " + (*this) );
//#endif
//}

// /// @details ???
//String::String(const String& par):std::string( par.c_str() )
//{
//    FIRST_TIME_ERRMESSAGE( " called for " + (*this) );
//}

// /// @details ???
//String::String(const char* cptr):std::string({cptr})
//{
//   FIRST_TIME_ERRMESSAGE( " called for " + (*this) );
//}

/// @details ???
String::String(const String* from_new):std::string({*from_new})
{
    FIRST_TIME_ERRMESSAGE( "Used ineffective constructor from = new Processing::String();\nUse =\"....\"; instead! " );
}

/// @details ???
String::String( String* from_new):std::string({*from_new})
{
    FIRST_TIME_ERRMESSAGE( "Used ineffective constructor from = new Processing::String();\nUse =\"....\"; instead! " );
}

/// From procsesing array of characters.
/// std::string(from._raw_ptr(),from.length()) available until C++20.
String::String(const sarray<char16_t> from): std::string(from.begin(),from.end())
{}

/// @details ???
String::String(const char c):std::string({c})
{}

/// @details ???
bool String::operator == (nullptr_t v)
{
    //FIRST_TIME_ERRMESSAGE( " should not be performed for nullptr!" );// WHY???
    return empty();
}

/// @details ???
bool String::operator != (nullptr_t)
{
    //FIRST_TIME_ERRMESSAGE( " should not be performed for nullptr!" );// WHY???
    return !empty();
}

/// @details XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
///          ------------------------------
///          ....
/// \param substring - pattern to find.
/// \param fromIndex - index of firsts searching position.
/// @returns:	An int value, representing the index of the first occurrence of the character in the string,
///             or -1 if it never occurs
/// See: https://www.w3schools.com/java/ref_string_indexof.asp
/// @internal
///         `size_t find (const string& str, size_t pos = 0) const noexcept;`
///      Returns: The position of the first character of the first match.
///               If no matches were found, the function returns `string::npos`.
///               `size_t` is an unsigned integral type (the same as member type `string::size_type`).
///      See: https://cplusplus.com/reference/string/string/find/
///
int String::indexOf(String substring, int fromIndex) const
{
    auto ret=std::string::find(substring,fromIndex);
    FIRST_TIME_ERRMESSAGE( "NOT INLINE VERSION USED!");
    return (ret==std::string::npos?-1:ret);
}

/// @details XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
///          -------------------------------
///          ....
/// \param character - what to find?
/// \param fromIndex - index of firsts searching position.
/// \return
/// See: https://www.w3schools.com/java/ref_string_indexof.asp
/// @internal
///      See: https://cplusplus.com/reference/string/string/find/
///
int String::indexOf(const char character, int fromIndex) const
{
    auto ret=std::string::find(character,fromIndex);
    FIRST_TIME_ERRMESSAGE( "NOT INLINE VERSION USED!");
    return (ret==std::string::npos?-1:ret);
}

/// @details Java like substring extraction.
///          -------------------------------
///          .........
/// \param startIndex - inclusive
/// \param endIndex - exclusive
/// \return string containing requested characters.
/// @internal
///     Using: string substr (size_t pos = 0, size_t len = npos) const;
///
///     See: https://cplusplus.com/reference/string/string/substr/
///
String String::substring(int startIndex,int endIndex) const
{                                                                                                 assert(startIndex>=0);
                                                                                                    assert(endIndex>=1);
                                                                                            assert(startIndex<endIndex);
    std::string ret=std::string::substr(startIndex,
                                        endIndex-startIndex);
    FIRST_TIME_ERRMESSAGE( "NOT INLINE VERSION USED!");
    return ret;
}

/// @details Java like to upper case conversion.
///          -------------------------------
///          ....
/// @internal
///     See: https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case
///     Use regular C++ `for` inside, so is it not so fast.
String String::toUpperCase() const
{
    std::string str=*this; // copy!
    for (auto & c: str) c = (char)toupper(c);
    //FIRST_TIME_ERRMESSAGE( "NOT INLINE VERSION USED!");
    return str;
}

/// @details More flexible version.
/// @internal Use regular C++ `for` inside, so is it not so fast.
String String::toUpperCase(int startIndex,int endIndex) const
{
    std::string str=*this; // copy!
    for(std::string::size_type i=startIndex;i<endIndex;i++)
    {
        str[i]=(char)toupper((*this)[i]);
    }
    //FIRST_TIME_ERRMESSAGE( "NOT INLINE VERSION USED!");
    return str;
}

/// @details ### Java like to lower case conversion.
///
///          ....
/// @internal
///     See: https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case
///     Use regular C++ `for` inside, so is it not so fast.
String String::toLowerCase() const
{
    std::string str=*this; // copy!
    for (auto & c: str) c = (char)tolower(c);
    //FIRST_TIME_ERRMESSAGE( "NOT INLINE VERSION USED!");
    return str;
}

/// @details More flexible version.
/// @internal Use regular C++ `for` inside, so is it not so fast.
String String::toLowerCase(int startIndex,int endIndex) const
{
    std::string str=*this; // copy!
    for(std::string::size_type i=startIndex;i<endIndex;i++)
    {
        str[i]=(char)tolower((*this)[i]);
    }
    //FIRST_TIME_ERRMESSAGE( "NOT INLINE VERSION USED!");
    return str;
}

/// @details Java `getchars()` for transfer char from string to array of chars.
///          -----------------------------------------------------------------
///
///     The Java String class getChars() method copies the content of this string into a specified char array.
///     There are four arguments passed in the getChars() method.
///          ....
/// @internal
///         `size_t` is an unsigned integral type (the same as member type `string::size_type`.
///         Use regular C++ `for` inside, so is it not so fast.
void String::getChars(int srcBeginIndex, int srcEndIndex, sarray<char16_t> dest, int dstBeginIndex) const
{
    for(std::string::size_type i=srcBeginIndex;i<srcEndIndex;i++)
    {
        dest[dstBeginIndex++]=(*this)[i];
    }
    FIRST_TIME_ERRMESSAGE( "NOT EFFECTIVE IMPLEMENTATION.");
}

/// @details ???
///          ....
/// @internal
///     See: //https://www.sanfoundry.com/c-program-count-occurence-substring/
/// @todo Not implemented jet!
///
static int count_substrings(const char *str,const char *substr)
{
    FIRST_TIME_ERRMESSAGE( "NOT IMPLEMENTED");
    return 0; //TODO!
}

/// @details For internal use only!
///
void _errMessage(Processing::String msg,const char* func,int line,const char* file)
{
    std::cerr<<func<<":\""<<msg._std_str()<<"\"";
    if(line!=-1)
        std::cerr<<" src: "<<file<<":"<<line;
    std::cerr<<std::endl;
}

}//END of namespace Processing
/* ******************************************************************
 *               PROCESSING2C  version 2023                         *
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
