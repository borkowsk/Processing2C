/// \file processing_templates.hpp
/// \brief Mandatory templates for objects and arrays
/// @date 2025-04-02 (last modification)
/// \see
/// \n https://stackoverflow.com/questions/31874669/c11-reference-count-smart-pointer-design
/// \n https://en.cppreference.com/w/cpp/utility/initializer_list
/// \n https://en.cppreference.com/w/cpp/language/constructor

#pragma once
#ifndef PROCESSING_TEMPLATES_H
#define PROCESSING_TEMPLATES_H

#include <cassert>
#include <memory>
#include <initializer_list>

///\namespace Processing2C compatibility libraries
namespace Processing
{

/// \brief The base class for all "JAVAlike" objects
/// \details Base class for all Processing/JAVA like class but not pointers
/// \link  https://www.javatpoint.com/object-class
/// \see ptr
class Object
{
  private: Object& operator = (const Object&);// TODO: deleted?
  public:
    /// Destructor is virtual, which force destructor virtuality in a whole hierarchy.
    virtual ~Object(){}

    ///	Function compares the given object 'obj' to this object on the level of addresses.
    virtual bool equals(const Object& obj) const
    { return this==&obj; }

    ///	Function returns the hashcode number for this object.
    virtual long hashCode() const;
};

/// \brief The template class ptr to something.
/// \details Proxy for `std::shared_ptr` but mimic Processing/JAVA "object references" behaviour
/// \see Object
template<class T>
class ptr:public std::shared_ptr<T>
{
  public:
    /// Default (empty) constructor.
    ptr():std::shared_ptr<T>(nullptr){}     //empty

    /// Constructor explicitly assigning NULL.
    ptr(nullptr_t p):std::shared_ptr<T>(p){} //visible empty

    /// Constructor from a raw pointer to T. Mostly for `new T` operations.
    /// TODO: change into template?
    ptr(T* ini):std::shared_ptr<T>(ini){}

    /// \brief `shared_ptr` to B template constructor.
    /// \details Initial conversion from compatible `shared_ptr`s, needed for `dynamic_pointer_cast<>`
    template<class B>
    ptr(std::shared_ptr<B>& ini):std::shared_ptr<T>(ini)
    {
        assert(ini.get()==nullptr || this->get()!=nullptr);
    }

    /// \brief ptr to B template constructor
    /// \details Initial conversion from compatible ptr to B. For types accepted by shared_ptr<T>
    template<class B>
    ptr(ptr<B>& ini):std::shared_ptr<T>(ini) //Konwersja z ptr<> z typów akceptowalnych przez `std::shared_ptr<T>`
    {
        assert(ini.get()==nullptr || this->get()!=nullptr);
    }

    /// Destructor.
    ~ptr(){}

    // Assigments:
    // ////////////

    /// NULL pointer assigment.
    ptr<T>& operator = (nullptr_t p)
    {
        std::shared_ptr<T>::operator = (p);
        return *this;
    }

    /// RAW ptr assigment.
    ptr<T>& operator = (T*& p)
    {
        std::shared_ptr<T>::operator = (p);
        return *this;
    }

    /// Coping assigment.
    ptr<T>& operator = (ptr<T>& p)
    {
        std::shared_ptr<T>::operator = (p);
        return *this;
    }

    /// From base class coping assigment.
    ptr<T>& operator = (std::shared_ptr<T>& p)
    {
        std::shared_ptr<T>::operator = (p);
        return *this;
    }

    // using std::shared_ptr<T>::operator = ;//It's boiling over !!! :-( NEED TO BE DEFINED ONE BY ONE

    /// The most important operator that gives access to the pointed object.
    /// Probably the analogous one inherits from `shared_ptr`, but this one comes in handy for debugging.
    T* operator -> () { return this->get();}

    /// Operator that gives access to the pointed object. Less important, but also usable.
    operator T* () { return this->get();}

  //comparison operators:
  //^////////////////////
  template<class B>
  bool equals(const ptr<B>& p) const //Same object pointed
  {
      Object* tmp1=this->get();
      Object* tmp2=p.get();
      return tmp1==tmp2;
  }

  template<class B>
  bool operator == (const ptr<B>& p) const { return this->equals(p);}

  template<class B>
  bool operator != (const ptr<B>& p) const { return !(this->equals(p));}

  bool operator == (T* p) const { return this->get()==p;}
  bool operator != (T* p) const { return this->get()!=p;}

  bool operator == (std::nullptr_t p) const { return this->get()==p;}
  bool operator != (std::nullptr_t p) const { return this->get()!=p;}
};

/** Representation of JAVA "Comparable" interface. */
template<class T>
/*interface*/ class Comparable //,public virtual Object /*???*/
{
  public:
      virtual int compareTo(ptr<T> o) = 0;
};

/** @brief pObject is aliasing for ptr of Object.
 * Represents "object references" for object of basic class Object */
typedef ptr<Object> pObject;

/** @brief The template class array.
 * @details Array of T, sized when constructed. */
template<class T>
class array
{
      T* _ptr;
  public:
      size_t length; //!< Processing ma to jako goły atrybut a nie akcesor.

      ~array() { delete [] _ptr; } //!< Zwalnianie zasobów
      array(size_t N); //!< Jedyny konstruktor
      T& operator [] (size_t i) { return _ptr[i]; }
};

/** @brief The template class ptr of array.
 * @details Represents "object references" for array of `T`.
 *          Implements Processing semantics for one dimensional array */
template<class T>
class sarray:public ptr< array<T> >
{
public:
      sarray(){}
      sarray(nullptr_t p){}
      sarray(array<T>* tab): ptr< array<T> >(tab){}
      sarray(sarray<T>& tab): ptr< array<T> >(tab){}
      sarray(std::initializer_list<T> lst); // TODO? Czy to na pewno jest potrzebne?
      ~sarray(){} // Odziedziczone zwalnianie zasobów
      array<T>*   operator -> () { return this->get();}
      T&          operator [] (std::size_t i) { return (*this->get())[i]; }
      T*          begin() { return &(*this)[0]; }
      T*          end() { return &(*this)[ length() ]; }
      std::size_t length() { return this->get()->length; }
};

/** @brief The template class matrix (2D array)
 * @details Matrix of T, sized when constructed
 * (Tablica dwuwymiarowa opiera się na jednowymiarowych (PL)) */
template<class T>
class matrix:public array< sarray<T> >
{
  public:
      ~matrix(){}// Odziedziczone zwalnianie zasobów
       matrix(std::size_t N,std::size_t M);//Jedyny na razie konstruktor
};

/** @brief The template class ptr< matrix >
 * @details Represents "object references" for a matrix of `T`
 * Implements Processing semantics for a two-dimensional array. */
template<class T>
class smatrix:public ptr< matrix<T> >
{
  public:
      ~smatrix(){} // Odziedziczone zwalnianie zasobów
      smatrix(){}
      smatrix(matrix<T>* tab): ptr< matrix<T> > (tab) {}
      //smatrix(std::initializer_list<T> lst); //Na razie nigdzie nie używane. Potrzebne?

      matrix<T>* operator -> () { return this->get();}
      sarray<T>& operator [] (size_t j) { return (*this->get())[j]; }
      sarray<T>* begin() { return &(*this)[0]; }
      sarray<T>* end() { return &(*this)[ length() ]; }
      size_t     length() { return this->get()->length; }
};

/**
 * @brief Function _free_ptr_to releases the raw pointer to A
 */
template<class A,class B>
inline
A* _free_ptr_to(ptr<B>& b)//TODO rename it into _raw_ptr_to
{
    return (A*)(B*)b;
}


/// \brief C++ equivalent of JAVA `instanceof` for raw pointers.
/// \details
/// C++ has no direct method to check one object is an instance of some class type or not.
/// The nearest possible functionality similar to "instanceof" can be achieved using `dynamic_cast` of expression.
///
/// ``` C++
///     if(instanceof<Parent>(ptr1)) {
///           cout << "p is an instance of the class Parent" << endl;
///        } else {
///           cout << "p is not an instance of the class Parent" << endl;
///    }
/// ```
///
/// See: https://www.tutorialspoint.com/cplusplus-equivalent-of-instanceof
template<typename Base, typename T>
inline
bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}


/** @brief JAVA like instanceof function for processing pointers.
 * inspired by https://www.tutorialspoint.com/cplusplus-equivalent-of-instanceof */
template<typename Base, typename T>
inline
bool instanceof(ptr<T>& p)
{
    return dynamic_cast<Base*>(p.get()) != nullptr;
}

// PODRĘCZNE IMPLEMENTACJE INLINE:
//********************************

/**
 * @brief Template of sarray<> constructor with initialiser list
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
 * @brief The sole constructor of inside template array<T> class
 */
template<class T>
inline
array<T>::array(size_t N): length{N}
{
    _ptr = new T[N];
}

/**
 * @brief The sole constructor of inside template matrix<T> class
 */
template<class T>
inline
matrix<T>::matrix(size_t N,size_t M):array< sarray<T> >( N )
{
    for(size_t i=0;i<this->length;i++)
        (*this)[i]=new array<T>( M );
}

}//END of namespace Processing
/* *******************************************************************/
/*               PROCESSING2C  version 2025                          */
/* *******************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                  */
/*            W O J C I E C H   B O R K O W S K I                    */
/*    Instytut Studiów Społecznych Uniwersytetu Warszawskiego        */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI   */
/*    GITHUB: https://github.com/borkowsk                            */
/*                                                                   */
/*                               (Don't change or remove this note)  */
/* *******************************************************************/
#endif
