///\file processing_string.hpp
/// Created by borkowsk on 26.11.2021.
//
#pragma once
#ifndef PROCESSING2C_EXAMPLES_PROCESSING_STRING_HPP
#define PROCESSING2C_EXAMPLES_PROCESSING_STRING_HPP

#include <cassert>
#include <string>

///\namespace Processing2C compatibility libraries
namespace Processing
{
    class _string_param;//Zapowiadająca deklaracja tej klasy, bo użyta jako parametr

    class String:public std::string //private std::string - NIEUDANA PRóBA - CIĄGLE CZEGOŚ JESZCZE POTRZEBUJE NIEJAWNIE Z std::string
    {
        //String& operator = (const String&) = delete; //To nie zapobiega użyciu w konwersjach?!? :-(
        //https://stackoverflow.com/questions/17907453/hiding-base-class-method-with-using-declaration-doesnt-work-for-assignment-op
        //using std::string::operator + ;     // hide the below method for `Derived` objects - also does not work
        //
        // ‘std::__cxx11::basic_string<_CharT, _Traits, _Alloc> std::operator+(std::__cxx11::basic_string<_CharT, _Traits, _Alloc>&&, std::__cxx11::basic_string<_CharT, _Traits, _Alloc>&&) [with _CharT = char; _Traits = std::char_traits<char>; _Alloc = std::allocator<char>]’operator+(basic_string<_CharT, _Traits, _Alloc>&& __lhs,
    public:
        friend class Processing::_string_param;

        /// Default constructor
        String(){}
        /// NULL init constructor
        String(nullptr_t p):String(){}
        /// Copy constructor
        String(const String&);
        /// From std::string constructor
        String(const std::string& str):std::string(str){}
        /// From C like string and const string constructor
        String(const char* str):std::string(str){}
        /// From char constructor
        explicit String(const char  c);
        /// String conversion from double and other numbers
        String(double v);//:String(){ operator+=(v);}
        /// General Object  ptr conversion constructor
        String(const Object* p);//:String("@"){ operator+=( (long unsigned int)p.get() );}
        /// Template Processing::ptr<> conversion constructor
        template<class T>
        String(const ptr<T> p);//:String("@"){ operator+=( (long unsigned int)p.get() );}

        /// Destructor
        virtual ~String();//??? Na pewno potrzebne?

        /// HACK...
        /// Sam z siebie robi pointer na siebie :-D
        String* operator -> ();

        bool  equals(const char* wz) { return this->compare(wz)==0;}
        bool  notEmpty() { return this->c_str()!=nullptr; }
        //operator bool () { return this->c_str()!=nullptr; }

        /// Back, named conversion to base class
        const std::string& _std_str() const { return *this;}
        std::string& _std_str() { return *this;}

        bool operator == (nullptr_t);
        bool operator != (nullptr_t);

        String& operator = (_string_param v);
        String& operator += (_string_param v);
        template<class X>
        String& operator += (const ptr<X>& p);

        String operator  + (_string_param) const;
        String operator  & (_string_param) const;
        //template<class X>
        //String operator  + (const ptr<X>& p) const;

        /// DIRECT IMPORTS FROM basic_string, even if made private
        using std::string::length;
        using std::string::c_str;
        using std::string::operator [];
        using std::string::erase;
        using std::string::find;
        using std::string::substr;
        using std::string::find_first_of;
    };

    /// Interface for classes able to be printed
    class _self_printable
    {
    public:
        virtual String print() const=0;
    };

    /// class designed for automatic PARAMETER conversion into String
    class _string_param:public String
    {
    public:
        _string_param(const _self_printable& p):String(p.print()){}
        _string_param(const String&          p):String(p){}
        _string_param(const std::string&     p):String(p){}
        _string_param(const char*    p):String(p){}
        _string_param(const void*    p);
        _string_param(const char     p);
        _string_param(double         p);
        _string_param(float          p);
        _string_param(int            p);
        _string_param(long unsigned  p);
        _string_param(std::exception &e);
        template<class T>
        _string_param(ptr<T> p):_string_param(p.get()){}

        /// Destructor
        virtual ~_string_param();// Zwalnianie zasobów

        //operator String& () {return *(String*)this;}
        String& _str() { return *(String*)this;}
        String const& _str() const { return *(String*)this;}

        String& get() { return *(String*)this;}//Obsolete

        _string_param operator  + (_string_param) const;
    };

    template<class T>
    class  self_printable_ptr:public ptr<T>,virtual public _self_printable/*interface*/
    {
    public:
        String print() const { return  this->get()->print(); }

        self_printable_ptr():ptr<T>(nullptr){}
        self_printable_ptr(T* ini):ptr<T>(ini){}
        //using ptr<T>::operator = ; //???
        self_printable_ptr<T>& operator = (T* other){ ptr<T>::operator = ((T*)other); return *this;}
        auto begin() { return this->get()->begin(); } //need C++14 !
        auto end()   { return this->get()->end(); } //need C++14 !
    };

    inline String *String::operator -> () //Utożsamia operator -> z operatorem . dla tego typu!!!
    {
        return this;
    }

    String operator  + (_string_param,_string_param);
    //String operator  + (_string_param,float); //A lot of conflicts :-(
    //String operator  + (_string_param,int); //A lot of conflicts :-(
    template<class X>
    String& operator + (const ptr<X>&,String&);

    inline String::String(double v):String()
    {
        operator+=(v);
    }

    inline String::String(const Object* p):String("@")
    {
        operator += ( (long unsigned int)p );
    }

    template<class T>
    inline String::String(const ptr<T> p):String("@")
    {
        operator += ( (long unsigned int)p.get() );
    }

    template<class X>
    String& String::operator += (const ptr<X>& p)
    {
        this->operator += ( _string_param{ (long unsigned int)p.get() } );
        return *this;
    }

}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2021-11-26                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiów Społecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
#endif //PROCESSING2C_EXAMPLES_PROCESSING_STRING_HPP
