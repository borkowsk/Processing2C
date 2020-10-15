// Obligatoryjne szablony dla obiektów i tablic
#pragma once
#ifndef PROCESSING_TEMPLATES_H
#define PROCESSING_TEMPLATES_H
#include <memory>
#include <initializer_list>
/// https://en.cppreference.com/w/cpp/utility/initializer_list
/// https://en.cppreference.com/w/cpp/language/constructor
/// https://stackoverflow.com/questions/31874669/c11-reference-count-smart-pointer-design
namespace Processing
{

class Object
{
  ///INFO: see https://www.javatpoint.com/object-class
  public:
    virtual ~Object(){}
    virtual long hashCode() const;///	returns the hashcode number for this object
    virtual bool equals(const Object& obj) const///	compares the given object to this object.
    { return this==&obj; }
};

template<class T>
class ptr:public std::shared_ptr<T>
{
  ///INFO: Proxy for standard shared_ptr for mimic Procesing "object references" behaviour
  public:
      ~ptr(){}// Zwalnianie zasobów

      //Konstruktory
      ptr():std::shared_ptr<T>(nullptr){}     //empty

      ptr(nullptr_t p):std::shared_ptr<T>(p){}//visible empty

      ptr(T* ini):std::shared_ptr<T>(ini){}   //from raw pointer for new T

      template<class B>
      ptr(std::shared_ptr<B> ini):std::shared_ptr<T>(ini){}//from dynamic_pointer_cast

      template<class B>
      ptr(ptr<B>& ini):std::shared_ptr<T>(ini){}//Konwersja z ptr<> z typów akceptowalnych przez shared_ptr<T>

      //using std::shared_ptr<T>::operator = ;//kipisz!!!

      ptr<T>& operator = (nullptr_t p){ std::shared_ptr<T>::operator = (p); return *this; }
      ptr<T>& operator = (std::shared_ptr<T> p){ std::shared_ptr<T>::operator = (p); return *this;}
      ptr<T>& operator = (ptr<T> p){ std::shared_ptr<T>::operator = (p); return *this; }

      bool equals(const ptr<T>& p) const { return this->get()==p.get();}//Same object pointed
      //bool operator == (const ptr<T>& p) const { return this->equals(p);}
      //bool operator != (const ptr<T>& p) const { return this->equals(p);}
      bool operator == (T* p) const { return this->get()==p;}
      bool operator != (T* p) const { return this->get()!=p;}
      bool operator == (std::nullptr_t p) const { return this->get()==p;}
      bool operator != (std::nullptr_t p) const { return this->get()!=p;}

      T* operator -> () { return this->get();}
      operator T& () { return *(this->get());}
      //operator T* () { return *(this->get());}
};

typedef ptr<Object> pObject;

template<typename Base, typename T> //inspired by https://www.tutorialspoint.com/cplusplus-equivalent-of-instanceof
inline bool instanceof(ptr<T>& p)
{
   return dynamic_cast<Base*>(p.get())!=nullptr;
}

template<class T>
/*interface*/ class Comparable
{
  ///INFO:
  public:
      virtual int compareTo(ptr<T> o)=0;
};

template<class T>
class array
{
  ///INFO: Array of T, sized when constructed
  T* _ptr;
  public:
      size_t length;

      ~array() { delete [] _ptr; } // Zwalnianie zasobów
      array(size_t N): length{N} { _ptr = new T[N]; }
      T& operator [] (size_t i) { return _ptr[i]; }
};

template<class T>
class sarray:public ptr< array<T> >
{
      ///INFO: Processing semantics for one dimensional array
  public:
      ~sarray(){}// Zwalnianie zasobów
      sarray(){}
      sarray(std::initializer_list<T> lst);
      sarray(array<T>* tab): ptr< array<T> >(tab){}

      array<T>* operator -> () { return this->get();}
      T&        operator [] (size_t i) { return (*this->get())[i]; }
      T*        begin() { return &(*this)[0]; }
      T*        end() { return &(*this)[ length() ]; }
      size_t    length() { return this->get()->length; }
};

template<class T>
inline  sarray<T>::sarray(std::initializer_list<T> l):
            ptr< array<T> >(new array<T>(l.size()))
{ //NOT TESTED YET! TODO!
    size_t i=0;
    for(auto e:l)
        (*this)[i++]=e;
}

template<class T>
class matrix:public array< sarray<T> >
{
  ///INFO: tablica dwuwymiarowa opiera się na jednowymiarowych
  public:
      ~matrix(){}// Zwalnianie zasobów
       matrix(size_t N,size_t M);
      //sarray<T>& operator [] (size_t j);//Potrzebne?
};

template<class T>
inline matrix<T>::matrix(size_t N,size_t M):
            array< sarray<T> >( N )
{ //NOT TESTED YET! TODO!
    for(size_t i=0;i<this->length;i++)
        (*this)[i]=new array<T>( M );
}

template<class T>
class smatrix:public ptr< matrix<T> >
{
  ///INFO:Processing semantics for two dimensional array
  public:
      ~smatrix(){}// Zwalnianie zasobów
      smatrix(){}
      smatrix(matrix<T>* tab): ptr< matrix<T> > (tab) {}
      //smatrix(std::initializer_list<T> lst);//Potrzebne?

      matrix<T>* operator -> () { return this->get();}
      sarray<T>& operator [] (size_t j) { return (*this->get())[j]; }
      sarray<T>* begin() { return &(*this)[0]; }
      sarray<T>* end() { return &(*this)[ length() ]; }
      size_t     length() { return this->get()->length; }
};


/*
template<class T>
inline  ptr<T>& ptr<T>::operator = (ptr<T>& other)
{
    _ptr=other._ptr; return *this;
}

template<class T>
inline  bool ptr<T>::operator == (const ptr<T>& other) const
{
    return _ptr.get()==other._ptr.get();
}

template<class T>
inline  bool ptr<T>:: operator != (const ptr& other)const
{
    return _ptr.get()!=other._ptr.get();
}

template<class T>
inline  bool ptr<T>::operator == (T* other) const
{
    return _ptr.get()==other;
}

template<class T>
inline  bool ptr<T>::operator != (T* other) const
{
    return _ptr.get()!=other;
}

//template<class T>
//inline  array<T>::array(size_t N):_ptr(new T[N]),length(N)
//{}

template<class T>
inline  T& array<T>::operator [] (size_t i)
{
//    return _ptr[i];
}

//template<class T>
//inline  sarray<T>::sarray(array<T> &tab)
//{
//
//}


//template<class T>
//inline  size_t sarray<T>::length()
//{
//
//}

template<class T>
inline  array<T>* sarray<T>::operator -> ()
{

}

template<class T>
inline  matrix<T>::matrix(size_t N,size_t M)
{

}

template<class T>
inline  sarray<T>& matrix<T>::operator [] (size_t j)
{

}

template<class T>
inline  smatrix<T>::smatrix(matrix<T>* tab)
{

}

template<class T>
inline  smatrix<T>::smatrix(std::initializer_list<T> l)
{

}
//??? TODO TEST IT!

template<class T>
inline  size_t smatrix<T>::length()
{

}

template<class T>
inline  matrix<T>* smatrix<T>::operator -> ()
{

}
*/

}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2020-09-29                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
#endif
