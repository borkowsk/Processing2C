///\file processing_string.hpp
/// Created by borkowsk on 26.11.2021.
//
#pragma once
#ifndef PROCESSING2C_PROCESSING_STRING_HPP
#define PROCESSING2C_PROCESSING_STRING_HPP

#include <cassert>
#include <string>

///\namespace Processing2C compatibility libraries
namespace Processing
{
    class _string_param;//Zapowiadająca deklaracja tej klasy, bo użyta jako parametr
    class _self_printable;//Zapowiadająca deklaracja tej klasy, bo użyta jako parametr

    class String:public std::string //private std::string - ŚLAD PO NIEUDANEJ PRóBIE - CIĄGLE CZEGOŚ JESZCZE POTRZEBUJE NIEJAWNIE Z std::string
    {
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

        /// Sam z siebie robi pointer na siebie :-D, taki HACK...
        String* operator -> () { return this; }

        /// Back, named conversion to base class
        const std::string& _std_str() const { return *this;}
        std::string& _std_str() { return *this;}

        /// Porównanie ze stałą łańcuchową
        bool  equals(const char* wz) const { return this->compare(wz)==0;}

        /// Porównanie z innym Stringiem   - TODO TEST!
        bool equals(const String& wz) const { return this->compare(wz._std_str())==0;}

        /// Tests for empties
        bool  notEmpty() { return this->c_str()!=nullptr; }
        //operator bool () { return this->c_str()!=nullptr; }
        bool operator == (nullptr_t);
        bool operator != (nullptr_t);

        ///Przypisywanie niemal czegokolwiek, dzięki sztuczce z parametrem
        String& operator = (_string_param v);
        ///Przedłużanie stringu o niemal cokolwiek, dzięki sztuczce z parametrem
        String& operator += (_string_param v);
        template<class X>
        String& operator += (const ptr<X>& p);
        ///Konkatenacja na wzór Processingu. Niestety w C++ wciąż generuje liczne ostrzeżenia
        String operator  + (_string_param v) const;
        ///Operator konkatenacji - nie ma go w Processingu, ale może pomagać rozwiązywać kłopoty z operatorem '+'
        String operator  & (_string_param v) const;
        //template<class X>
        //String operator  + (const ptr<X>& p) const; //Generuje multum kłopotów
        //Nie chcę domyślnego operatora = z klasy bazowej, ale to nie dzoiała
        //String& operator = (const String&) = delete; //To nie zapobiega użyciu w konwersjach?!? :-(
        //https://stackoverflow.com/questions/17907453/hiding-base-class-method-with-using-declaration-doesnt-work-for-assignment-op
        //using std::string::operator + ;     // hide the below method for `Derived` objects - also does not work
        //
        // ‘std::__cxx11::basic_string<_CharT, _Traits, _Alloc> std::operator+(std::__cxx11::basic_string<_CharT, _Traits, _Alloc>&&, std::__cxx11::basic_string<_CharT, _Traits, _Alloc>&&) [with _CharT = char; _Traits = std::char_traits<char>; _Alloc = std::allocator<char>]’operator+(basic_string<_CharT, _Traits, _Alloc>&& __lhs,
        /// Alternatywna funkcja zaprzyjaźniona do konkatenacji _Stringów poprzez _string_param
        friend String operator  + (_string_param,_string_param);

        /// DIRECT IMPORTS FROM basic_string, even if made private
        using std::string::length;
        using std::string::c_str;
        using std::string::operator [];
        using std::string::erase;
        using std::string::find;
        using std::string::substr;
        using std::string::find_first_of;
    };

    /// Duplikat deklaracji frienda z wnętrza klasy String
    /// TODO: Dlaczego ta deklaracja jest potrzebna? CZORT WIE :-( Bez tego nie działa
    String operator  + (_string_param,_string_param);

    /// class designed for automatic PARAMETER conversion into String
    class _string_param:public String
    {
    public:
        _string_param(const _self_printable& p);
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

        ///Operator konkatenacji dla _string_param.
        ///Wydaje się niepotrzebny, ale bez niego dłuższe konkatenacje czasem się nie udają
        _string_param operator  + (_string_param) const;

        ///Jawne odzyskiwanie klasy String z klasy _string_param
        String& _str() { return *(String*)this;}
        String const& _str() const { return *(String*)this;}
        String& get() { return *(String*)this;}//Obsolete
        //operator String& () {return *(String*)this;}
    };

    /// Interface for classes able to make printable representation
    class _self_printable
    {
    public:
        virtual String print() const=0;
    };

    /// Wskaźnik na klasy zdolne do samodzielnego stworzenia sobie drukowalnej reprezentacji
    template<class T>
    class  self_printable_ptr:public ptr<T>,virtual public _self_printable/*interface*/
    {
    public:
        String print() const { return  this->get()->print(); }

        self_printable_ptr():ptr<T>(nullptr){}
        self_printable_ptr(T* ini):ptr<T>(ini){}
        //using ptr<T>::operator = ; //Tak to nie działa. TODO: A w ogóle po co???
        self_printable_ptr<T>& operator = (T* other){ ptr<T>::operator = ((T*)other); return *this;}
        auto begin() { return this->get()->begin(); } //need C++14 !
        auto end()   { return this->get()->end(); } //need C++14 !
    };

    // Implementacje
    // ////////////////////////////////////

    /// Inicjalizacja obiektu String liczbą
    inline String::String(double v):String()
    {
        operator+=(v);
    }

    /// Inicjalizacja obiektu String reprezentacją tekstową adresu jakiegoś obiektu
    inline String::String(const Object* p):String("@")
    {
        operator += ( (long unsigned int)p );
    }

    /// Inicjalizacja klasy String reprezentacją tekstową adresu trzymanego w obiekcie
    /// z szablonu Processing::ptr<T>
    template<class T>
    inline String::String(const ptr<T> p):String("@")
    {
        operator += ( (long unsigned int)p.get() );
    }

    /// Dopisanie do zawartości Stringu reprezentacji tekstowej adresu trzymanego w obiekcie
    /// z szablonu Processing::ptr<T>
    template<class X>
    String& String::operator += (const ptr<X>& p)
    {
        this->operator += ( _string_param{ (long unsigned int)p.get() } );
        return *this;
    }

    /// Inicjalizacja _string_param z typów _self_printable
    inline _string_param::_string_param(const _self_printable& p):String(p.print())
    {}

    //String operator  + (_string_param,float); //A lot of conflicts :-(
    //String operator  + (_string_param,int); //A lot of conflicts :-(
    //template<class X> /// TODO: Czy to jest potrzebne
    //String& operator + (const ptr<X>&,String&);

}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2021-11-29                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiów Społecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
#endif //PROCESSING2C_PROCESSING_STRING_HPP