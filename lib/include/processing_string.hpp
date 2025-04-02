/** \brief JAVA like String
 * \file processing_string.hpp
 * \classes String
 * \ingroup strings
 * \author borkowsk
 * @date 2025-04-02 (last modification)
 */
// //////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////
#pragma once
#ifndef PROCESSING2C_PROCESSING_STRING_HPP
#define PROCESSING2C_PROCESSING_STRING_HPP

#include "processing_templates.hpp"
#include <cassert>
#include <string>

///\namespace Processing \brief P2C compatibility libraries
namespace Processing
{
    /// A foreshadowing declaration of this class to be used hereafter as a method parameter
    class Object;

    /// A foreshadowing declaration of this class to be used hereafter as a method parameter
    class _string_param;

    /// A foreshadowing declaration of this class to be used hereafter as a method parameter
    class _self_printable;

    /// \brief A class that mimics the String capabilities in Processing programs
    //... private std::string - ŚLAD PO NIEUDANEJ PRóBIE - CIĄGLE CZEGOŚ JESZCZE POTRZEBUJE NIEJAWNIE Z std::string
    class String:public std::string
    {
    public:
        friend class Processing::_string_param;
        /// \brief Destructor
        ~String() = default ; //raczej potrzebne?

        // CONSTRUCTORS
        // ////////////

        /// \brief Default constructor
        String() = default ;
        /// \brief Copy constructor
        String(String const&) = default ;
        /// \brief From std::string constructor
        String(const std::string& str):std::string(str){}
        /// \brief NULL init constructor
        String(std::nullptr_t p):String(){} //POTRZEBNE?
        /// \brief From C like string and const string constructor
        String(const char* str):std::string(str){}
        /// \brief from String* transfer!
        explicit String(String* from_new);
        /// \brief from const String* copy!
        explicit String(const String* from_new);
        /// From procesing array of characters.
        explicit String(const sarray<char16_t> from); //TODO Dlaczego bez &
        /// \brief From char constructor
        explicit String(const char  c);
        /// \brief From char16_t constructor
        explicit String(const char16_t c);
        /// \brief String conversion from double and other numbers
        String(double v); //:String(){ operator+=(v);}
        /// \brief General Object  ptr conversion constructor
        String(const Object* p); //:String("@"){ operator+=( (long unsigned int)p.get() );}
        /// \brief Template Processing::ptr<> conversion constructor
        template<class T>
        String(const ptr<T> p); //:String("@"){ operator+=( (long unsigned int)p.get() );}


        /// \note It makes a pointer on itself :-D, such a ugly HACK... But it works :-)
        const String* operator -> () const { return this; }
	    String* operator -> () { return this; }

        /// \brief Back, named "conversion", to base class
        const std::string& _std_str() const { return *this;}
        std::string& _std_str() { return *this;}

        /// \brief Comparison with the string constant
        bool  equals(const char* wz) const { return this->compare(wz)==0;}

        /// \brief Comparison with another String \todo - MORE TESTS!
        bool equals(const String& wz) const { return this->compare(wz._std_str())==0;}

        /// \brief Explicit test for empties
        bool  notEmpty() const { return this->c_str()!=nullptr; }

        /// \brief Implicit tests for empties
        bool operator == (std::nullptr_t);
        /// \brief Negated implicit tests for empties
        bool operator != (std::nullptr_t);

        /// \brief Przypisywanie niemal czegokolwiek, dzięki możliwościom klasy _string_param
        String& operator = (_string_param v);

        /// \brief powinien to robić `_string_param`, ale nie robi :-/
        String& operator = (const char* v) { std::string::operator = (v); return *this; }

        /// \brief powinien to robić `_string_param`, ale nie robi :-/
        String& operator = (const Processing::String&)= default;

        /// \brief Przedłużanie string-u o niemal cokolwiek, dzięki możliwościom klasy _string_param
        String& operator += (_string_param v);

        /// \brief ...
        template<class X>
        String& operator += (const ptr<X>& p);

        /// \brief Konkatenacja na wzór Processing-u. Niestety w C++ wciąż generuje liczne ostrzeżenia
        String operator  + (_string_param v) const;

        /// \brief Operator konkatenacji — nie ma go w Processing-u, ale może pomagać rozwiązywać kłopoty z operatorem '+'
        String operator  & (_string_param v) const;

        //template<class X>
        //String operator  + (const ptr<X>& p) const; //Generuje multum kłopotów
        //Nie chcę domyślnego operatora = z klasy bazowej, ale to nie dzoiała
        //String& operator = (const String&) = delete; //To nie zapobiega użyciu w konwersjach?!? :-(
        //https://stackoverflow.com/questions/17907453/hiding-base-class-method-with-using-declaration-doesnt-work-for-assignment-op
        //using std::string::operator + ;     // hide the below method for `Derived` objects - also does not work
        //
        // ‘std::__cxx11::basic_string<_CharT, _Traits, _Alloc> std::operator+(std::__cxx11::basic_string<_CharT, _Traits, _Alloc>&&, std::__cxx11::basic_string<_CharT, _Traits, _Alloc>&&) [with _CharT = char; _Traits = std::char_traits<char>; _Alloc = std::allocator<char>]’operator+(basic_string<_CharT, _Traits, _Alloc>&& __lhs,

        /// \brief Alternatywna funkcja zaprzyjaźniona do konkatenacji _Stringów poprzez _string_param
        friend String operator  + (_string_param,_string_param);

        // DIRECT IMPORTS FROM `basic_string`, even, if it will be made private
        using std::string::length;
        using std::string::c_str;
        using std::string::operator [];
        using std::string::erase;
        using std::string::find;
        using std::string::substr;
        using std::string::find_first_of;
        
        /// \brief Access to one character in a Processing manner
        char charAt(int index) const { return (*this)[index]; }

        /// Java like searching of `substring`.
        /// @returns the index within this string of the first occurrence of the specified substring, starting at the
        ///          specified index. If no such value of k exists, then -1 is returned.
        int indexOf(String substring, int fromIndex=0) const;

        /// Java like searching of last occurence of `substring`.
        /// @param str : substring to locate.
        /// @param fromIndex : index in string from witch searching will start BACKWARD!
        /// @returns the index within this string of the last occurrence of the specified substring, searching
        ///          backward starting at the specified index. If no such value of k exists, then -1 is returned.
        int lastIndexOf(String str, int fromIndex=-1) const;

        /// Java like searching of `character`.
        int indexOf(const char character, int fromIndex=0) const;

        /// Java like substring extraction.
        String substring(int startIndex,int endIndex=INT32_MAX) const;

        /// Java like to upper case conversion.
        String toUpperCase() const;

        /// Upper case partial conversion. Similar to Java but more flexible.
        /// \param startIndex - inclusively
        /// \param endIndex - exclusively
        /// \return Copy of this string with requested characters upper-cased.
        String toUpperCase(int startIndex,int endIndex) const;

        /// Java like to lower case conversion.
        String toLowerCase() const; /// < @todo

        /// Lower case partial conversion. Similar to Java but more flexible.
        /// \param startIndex - inclusively
        /// \param endIndex - exclusively
        /// \return Copy of this string with requested characters lower-cased.
        String toLowerCase(int startIndex,int endIndex) const;

        /// @brief Java `getchars()` for transfer char from string to array of chars.
        /// @note The Java String class getChars() method copies the content of this string into a specified char array.
        ///       There are four arguments passed in the getChars() method.
        /// \param srcBeginIndex `int`: The index from where copying of characters is started.
        /// \param srcEndIndex `int` : The index which is next to the last character that is getting copied.
        /// \param destination 'char[]': The char array where characters from the string that invokes the getChars()
        ///                     method is getting copied.
        /// \param dstEndIndex `int`: It shows the position in the destination array from where the characters from
        ///                     the string will be pushed.
        void getChars(int srcBeginIndex, int srcEndIndex, sarray<char16_t> dest, int dstBeginIndex) const; /// < @todo ?
    };

    /// \brief Duplikat deklaracji frienda z wnętrza klasy String
    /// TODO: Dlaczego ta deklaracja jest potrzebna? CZORT WIE :-( Bez tego nie działa
    String operator  + (_string_param,_string_param);

    /// \brief class designed for automatic PARAMETER conversion into String
    class _string_param:public String
    {
    public:
        /// \brief Destructor
        ~_string_param() = default; // Zwalnianie zasobów - czy ta deklaracja potrzebna?
        /// \brief Default constructor
        _string_param() = default;

        _string_param(const _string_param& ) = default;
        //_string_param(_string_param const& ) = default;

        /// \brief One of non-trivial constructors
        /// \param p : String
        _string_param(const String&          p):String(p){}
        /// \param p : std::string
        _string_param(const std::string&     p):String(p){}
        /// \param p : const char*
        _string_param(const char*    p):String(p){}
        /// \param p : const void*
        _string_param(const void*    p);
        /// \param p : any char
        _string_param(const char     p);

        /// \param p : any char16_t
        _string_param(const char16_t  p);

        /// \param p : double precision value
        _string_param(double         p);
        /// \param p : single  precision value
        _string_param(float          p);
        /// \param p : int value
        _string_param(int            p);
        /// \param p : long int value
        _string_param(long  int      p);
        /// \param p : unsigned long value
        _string_param(unsigned long   p);
        /// \param p : any self-printable object
        _string_param(_self_printable const& p);
        /// \param p : any exception
        _string_param(std::exception &e);

        /// \param p : any ptr to Processing compatible object
        template<class T>
        _string_param(ptr<T> p):_string_param(p.get()){}

        /// \brief Operator konkatenacji dla _string_param.
        /// Wydaje się niepotrzebny, ale bez niego dłuższe konkatenacje czasem się nie udają
        _string_param operator  + (_string_param what) const;

        /// \brief Jawne odzyskiwanie klasy String z klasy _string_param
        String& _str() { return *(String*)this;}
        String const& _str() const { return *(String*)this;}

        /// \brief Jawne odzyskiwanie klasy `String` z klasy `_string_param`
        /// \absolete !!!
        String& get() { return *(String*)this;} //Obsolete?
        //operator String& () {return *(String*)this;}
    };

    // Jawna konwersja czegokolwiek na String.
    inline String str(_string_param par) { return par._str(); }

    /// \brief Alternatywna wersja _errMessage
    void _errMessage(String msg,const char* func,int line=-1,const char* file="");

    /// \brief Interface for classes able to make printable representation
    class _self_printable
    {
    public:
        virtual String print() const=0;
    };

    /// \brief Wskaźnik na klasy zdolne do samodzielnego stworzenia sobie drukowalnej reprezentacji
    /// czyli spełniającej interface _self_printable
    template<class T>
    class  self_printable_ptr:public ptr<T>,virtual public _self_printable/*interface*/
    {
    public:
        /// \brief Najważniejsza metoda wymagana przez interface
        String print() const { return  this->get()->print(); }

        /// \brief Destructor
        ~self_printable_ptr() = default ;
        /// \brief Default, empty constructor
        self_printable_ptr() = default ;
        /// \brief Copy constructor
        self_printable_ptr(self_printable_ptr const& ) = default ;
        /// \brief THE MOST IMPORTANT CONSTRUCTOR (for accept `new T()` ).
        self_printable_ptr(T* ini):ptr<T>(ini){}

        // Todo PRZETESTOWAĆ CZY TO W OGÓLE POTRZEBNE
        // Bez tej metody projekt się kompiluje ale JAK działa?
        //self_printable_ptr<T>& operator = (T*& other)
        //{
        //    ptr<T>::operator = (other);
        //    return *this;
        //}

        auto begin() //auto return need C++14 !
        {
            T* raw=this->get(); //Code is split for DEBUG-ing.
            auto iter=raw->begin();
            return iter;
        }

        auto end() //auto return need C++14 !
        {
            T* raw=this->get(); //Code is split for DEBUG-ing.
            auto iter=raw->end();
            return iter;
        }
    };

    // Implementacje
    //*////////////////////////////////////

    /// Constructor: Inicjalizacja obiektu String jakąś liczbą.
    inline String::String(double v):String()
    {
        operator+=(v);
    }

    /// Constructor: Inicjalizacja obiektu String reprezentacją tekstową adresu jakiegoś obiektu.
    inline String::String(const Object* p):String("@")
    {
        operator += ( (long unsigned int)p );
    }

    /// Constructor: Inicjalizacja klasy String reprezentacją tekstową adresu trzymanego w obiekcie.
    /// z szablonu `Processing::ptr<T>`
    template<class T>
    inline String::String(const ptr<T> p):String("@")
    {
        operator += ( (long unsigned int)p.get() );
    }

    /// Dopisanie do zawartości String-u reprezentacji tekstowej adresu trzymanego w obiekcie
    /// z szablonu `Processing::ptr<T>`
    template<class X>
    String& String::operator += (const ptr<X>& p)
    {
        this->operator += ( _string_param{ (long unsigned int)p.get() } );
        return *this;
    }

    inline _string_param::_string_param(char p):String( p )// inline?
    {}

    inline _string_param::_string_param(char16_t p):String( p )// inline?
    {}

    /// @details Constructor: Inicjalizacja `_string_param` z typów `_self_printable`.
    inline _string_param::_string_param(const _self_printable& p):String(p.print())
    {}

    //String operator  + (_string_param,float); //A lot of conflicts :-(
    //String operator  + (_string_param,int); //A lot of conflicts :-(
    //template<class X> /// TODO: Czy to jest potrzebne - RACZEJ NIE
    //String& operator + (const ptr<X>&,String&);

    String hex(int num); //Converts an int, byte, char, or color (?) to a String containing the equivalent hexadecimal notation.
    String hex(int num,int digits); //jest
    String binary(int num); //Converts an int, byte, char, or color (?) to a String containing the equivalent binary notation.
    String binary(int value,int digits); //TODO

    String nf(double num);
    String nf(double num,int digits);
    String nf(double num,int left,int right);

    String nf(sarray<int> nums);
    String nf(sarray<int> nums,int digits);
    String nf(sarray<int> nums,int left,int right);

    String nf(sarray<float> nums);
    String nf(sarray<float> nums,int digits);
    String nf(sarray<float> nums,int left,int right);

    String nf(sarray<double> nums);
    String nf(sarray<double> nums,int digits);
    String nf(sarray<double> nums,int left,int right);

    String nfp(double num);
    String nfp(double num,int digits);
    String nfp(double num,int left,int right);

    String nfp(sarray<int> nums);
    String nfp(sarray<int> nums,int digits);
    String nfp(sarray<int> nums,int left,int right);

    String nfp(sarray<float> nums);
    String nfp(sarray<float> nums,int digits);
    String nfp(sarray<float> nums,int left,int right);

    String nfp(sarray<double> nums);
    String nfp(sarray<double> nums,int digits);
    String nfp(sarray<double> nums,int left,int right);

    String nfs(double num);
    String nfs(double num,int digits);
    String nfs(double num,int left,int right);

    String nfs(sarray<int> nums);
    String nfs(sarray<int> nums,int digits);
    String nfs(sarray<int> nums,int left,int right);

    String nfs(sarray<float> nums);
    String nfs(sarray<float> nums,int digits);
    String nfs(sarray<float> nums,int left,int right);

    String nfs(sarray<double> nums);
    String nfs(sarray<double> nums,int digits);
    String nfs(sarray<double> nums,int left,int right);

    String nfc(double num);
    String nfc(double num,int digits);
    String nfc(double num,int left,int right);

    String nfc(sarray<int> nums);
    String nfc(sarray<int> nums,int digits);
    String nfc(sarray<int> nums,int left,int right);

    String nfc(sarray<float> nums);
    String nfc(sarray<float> nums,int digits);
    String nfc(sarray<float> nums,int left,int right);

    String nfc(sarray<double> nums);
    String nfc(sarray<double> nums,int digits);
    String nfc(sarray<double> nums,int left,int right);

    static inline String _chars(const char c,unsigned n) {
        String tmp; tmp.reserve(n);
        for(unsigned i=0;i<n;i++)
            tmp+=c;
        return tmp;
    }

}//END of namespace Processing
/* ******************************************************************
 *                PROCESSING2C  version 2025                        *
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
 ****************************************************************** */
#endif //PROCESSING2C_PROCESSING_STRING_HPP
