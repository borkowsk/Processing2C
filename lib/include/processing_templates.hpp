/** ****************************************************************
* \file 'processing_templates.hpp'
* \brief Mandatory templates for objects and arrays
* \author 'borkowsk'
* \ingroup Processing_compatibility
* \see <ul>
* <li> \a "https://en.cppreference.com/w/cpp/utility/initializer_list"
* <li> \a "https://en.cppreference.com/w/cpp/language/constructor"
* <li> \a "https://en.cppreference.com/w/cpp/language/decltype"
* <li> \a "https://stackoverflow.com/questions/31874669/c11-reference-count-smart-pointer-design"
* <li> \a "https://stackoverflow.com/questions/20131877/how-do-you-make-stdshared-ptr-not-call-delete"
* </ul>
*/
// //////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////
/*
    \class is used to indicate that the comment block contains documentation for the class
    \struct to document a C-struct.
    \union to document a union.
    \enum to document an enumeration type.
    \fn to document a function.
    \var to document a variable or typedef or enum value.
    \def to document a #define.
    \typedef to document a type definition.
    \file to document a file.
    \namespace to document a namespace.
    \package to document a Java package.
    \interface to document an IDL interface.
    See: https://www.doxygen.nl/manual/docblocks.html
 */

#pragma once

#ifndef PROCESSING_TEMPLATES_H
#define PROCESSING_TEMPLATES_H
#include <cassert>
#include <memory>
#include <initializer_list>

///\namespace Processing \brief P2C compatibility libraries
namespace Processing
{

/**
 * \class "Object"
 * This is a base class for all Processing/JAVA like class but not pointers
 * \ingroup JAVA_compatibility
 * \See
 * \a https://www.javatpoint.com/object-class
 */
class Object
{
  private:
    /// Assign operator
    /// \return derefered 'this' of L-value
    Object& operator = (const Object&);
  public:
    /// Destructor
    virtual ~Object(){} //TODO =0; ???
    /// Make hashcode number for this object
    ///	\return the hashcode
    virtual long hashCode() const;
    ///	Compares the given object \p 'obj' to this object based on address.
    /// \param obj
    /// \return logical result
    ///
    /// TODO CHECK what happened with ptrs to inside base classes?
    virtual bool equals(const Object& obj) const { return this==&obj; }
};

/**
 * The template class "ptr\<T\>".
 * Proxy for standard shared_ptr which mimic Processing "object references"
 * behaviours
 * \tparam T : any class
 * \ingroup JAVA_compatibility
 * \See \a https://en.cppreference.com/w/cpp/memory/shared_ptr
 */
template<class T>
class ptr:public std::shared_ptr<T>
{
  public:
      /// Destructor
      ~ptr(){} // = default; ??? TODO?

      ///Constructors
      ptr():std::shared_ptr<T>(nullptr)//empty
      {}
      ptr(nullptr_t p):std::shared_ptr<T>(p)//visible empty
      {}
      ptr(T* ini):std::shared_ptr<T>(ini)//from raw pointer for new T
      {}

      ///konwersja z gołych shared_ptr'ów potrzebna dla dynamic_ptr_cast<>
      template<class B>
      ptr(std::shared_ptr<B> ini):std::shared_ptr<T>(ini)
      {
          assert(ini.get()==nullptr || this->get()!=nullptr);//std::cerr<<ini.get()<<std::endl;
      }

      ///Konwersja z ptr<> z typów akceptowalnych przez shared_ptr<T>
      template<class B>
      ptr(ptr<B>& ini):std::shared_ptr<T>(ini)
      {
          assert(ini.get()==nullptr || this->get()!=nullptr);
      }

      // Przypisania  //using std::shared_ptr<T>::operator = ;//robi kipisz!!! :-(
      // ^^^^^^^^^^^  //TODO - sprawdzić czy nie można w ogóle się ich pozbyć
      ptr<T>& operator = (nullptr_t p){ std::shared_ptr<T>::operator = (p); return *this; }
      ptr<T>& operator = (std::shared_ptr<T> p){ std::shared_ptr<T>::operator = (p); return *this;}
      ptr<T>& operator = (ptr<T> p){ std::shared_ptr<T>::operator = (p); return *this; }

      // Porównania
      // ^^^^^^^^^^

      /// \brief Template method for compared ptr\<T\> for any others ptr\<\>
      template<class B>
      bool equals(const ptr<B>& p) const //Same object pointed
      {
          Object* tmp1=this->get();
          Object* tmp2=p.get();
          return tmp1==tmp2;
      }

      /// \brief Template operator == for compared ptr<T> for any others ptr<>
      template<class B>
      bool operator == (const ptr<B>& p) const { return this->equals(p);}

      /// \brief Template operator != for compared ptr<T> for any others ptr<>
      template<class B>
      bool operator != (const ptr<B>& p) const { return !(this->equals(p));}

      bool operator == (T* p) const { return this->get()==p;}
      bool operator != (T* p) const { return this->get()!=p;}

      bool operator == (std::nullptr_t p) const { return this->get()==p;}
      bool operator != (std::nullptr_t p) const { return this->get()!=p;}

      /// Dostęp do atrybutów przechowywanego obiektu
      T* operator -> () { return this->get();} //TODO Takie są dziedziczone, więc po co?
      /// Dostęp do całości przechowywanego obiektu
      operator T* () { return this->get();} //TODO Takie są dziedziczone, więc po co?
};

    /**
     * \typedef pObject is an alias for "ptr\<Object\>" .
     * Represents "object references" for object of basic class Object
     * using the same convention like any other Processing like objects.
     */
    typedef ptr<Object> pObject;

    /**
     * \fn Template function _free_ptr_to releases the raw pointer to A
     * from shared ptr to (potentially) derived class B
     */
    template<class A,class B>
    inline
    A* _free_ptr_to(ptr<B>& b)//TODO rename it into _raw_ptr_to
    {
        return (A*)(B*)b;
    }

    /**
     * \fn Template function which imitates JAVA like 'instanceof' function
     * inspired by https://www.tutorialspoint.com/cplusplus-equivalent-of-instanceof
     */
    template<typename Base, typename T>
    inline
    bool instanceof(ptr<T>& p)
    {
        return dynamic_cast<Base*>(p.get()) != nullptr;
    }

    /** \fn Raw pointer de-referencing template.
     * Needed mostly for extract class type from 'this'.
     * \example                                             \code
     *          decltype( _dereference_ptr(this) )
     *                                                      \endcode
     * \tparam T : any class
     * \param ptr : raw ptr to class, typically this
     * \return de-referenced object
     * \See \a https://en.cppreference.com/w/cpp/language/decltype
     */
    template<class T>
        T _dereference_ptr(T* ptr){ return *ptr;}

/** Macro for creating dummy _shared_ptr from prevent non needed de-allocation
 * \example                                                 \code
 *          auto safe_this=SAFE_RAW_PTR( this );
 *                                                          \endcode
 * \See \a https://stackoverflow.com/questions/20131877/how-do-you-make-stdshared-ptr-not-call-delete
 */
#define    SAFE_RAW_PTR( ptr )     (std::shared_ptr< decltype( _dereference_ptr( ptr ) ) >( \
                                    std::shared_ptr< decltype( _dereference_ptr( ptr ) ) >{}, ptr ))

/** Macro for creating dummy _shared_ptr of 'this'
 * \example                                     \code
 *              call_outside(SAFE_THIS,msg);
 *                                              \endcode
 * \ingroup JAVA_compatibility
 */
#define    SAFE_THIS                SAFE_RAW_PTR( this )

/**
 * \interface
 * C++ class representation of JAVA "Comparable" interface
 * \tparam T : any class
 * \ingroup JAVA_compatibility
 */
template<class T>
/*interface*/ class Comparable
{
  public:
      virtual int compareTo(ptr<T> o) = 0;
};

/**
 * The template class for any simple array.
 * Array of T, sized when constructed
 * \ingroup JAVA_compatibility
 */
template<class T>
class array
{
      T* _ptr;
  public:
      size_t length;//Processing ma to jako goły atrybut, a nie metodę akcesorową

      ~array() { delete [] _ptr; } // Zwalnianie zasobów
      array(size_t N); //Jedyny konstruktor
      T& operator [] (size_t i) { return _ptr[i]; }
};

/**
 * The template class "ptr\< array \>" .
 * Represents "object references" for array of T
 * Implements additional Processing semantics for one dimensional array
 * \ingroup JAVA_compatibility
 */
template<class T>
class sarray:public ptr< array<T> >
{
  public:
      //using ptr< array<T> >::operator ->;??? //NIE?

     ~sarray() = default;// Odziedziczone zwalnianie zasobów
      sarray() = default;
      sarray(sarray const&) = default; //??? TODO TODO ? chyba OK
      sarray(array<T>* tab): ptr< array<T> >(tab){}
      sarray(std::initializer_list<T> lst);

      array<T>*   operator -> () { return this->get();} // dublet? TODO usunąć?
      T&          operator [] (std::size_t i) const { return (*this->get())[i]; }
      T*          begin() const { return &(*this)[0]; }
      T*          end() const { return &(*this)[ length() ]; }

      std::size_t length() const { return this->get()->length; }
};

/**
 * The template class matrix (2D array)
 * Represent Matrix of T, sized when constructed
 * (Tablica dwuwymiarowa opiera się na jednowymiarowych (PL))
 * \ingroup JAVA_compatibility
 */
template<class T>
class matrix:public array< sarray<T> >
{
public:
    ~matrix() = default;// Odziedziczone zwalnianie zasobów
    matrix(std::size_t N,std::size_t M);//Jedyny konstruktor
};

/**
 * The template class "ptr\< matrix \>" .
 * Represents "object references" for matrix of T
 * Implements additional Processing semantics for two dimensional array
 * \ingroup JAVA_compatibility
 */
template<class T>
class smatrix:public ptr< matrix<T> >
{
  public:
      //using ptr< matrix<T> >::operator ->; //NIE?

     ~smatrix() = default; // Odziedziczone zwalnianie zasobów
      smatrix() = default;
      smatrix(smatrix const&) = default; //???  TODO ? chyba OK
      smatrix(matrix<T>* tab): ptr< matrix<T> > (tab) {}
      smatrix(std::initializer_list<T> lst);//Jak na razie nigdzie nie używane. TODO TEST!

      //matrix<T>* operator -> () { return this->get();} // dublet? TODO usunąć?
      sarray<T>& operator [] (size_t j) const { return (*this->get())[j]; } // dublet? NIE!
      sarray<T>* begin() const { return &(*this)[0]; } // dublet? NIE!
      sarray<T>* end() const { return &(*this)[ this->get()->length ]; } // dublet? NIE!
      //size_t     length() { return this->get()->length; } // dublet? TODO usunąć?
};

// PODRĘCZNE IMPLEMENTACJE INLINE
// ==============================

/**
 * \brief Template of sarray<> constructor with initialiser list
 */
template<class T>
inline
sarray<T>::sarray(std::initializer_list<T> l):ptr< array<T> >(new array<T>(l.size()))
{
    size_t i=0;
    for(auto e:l)
        (*this)[i++]=e;
}

/**
 * \brief The sole constructor of inside template array<T> class
 */
template<class T>
inline
array<T>::array(size_t N): length{N}
{
    _ptr = new T[N];
}

/**
 * \brief The sole constructor of inside template matrix<T> class
 */
template<class T>
inline
matrix<T>::matrix(size_t N,size_t M):array< sarray<T> >( N )
{
    for(size_t i=0;i<this->length;i++)
        (*this)[i]=new array<T>( M );
}

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
