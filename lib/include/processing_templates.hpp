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

template<class T>
class ptr
{
  ///INFO: Proxy for standard shared_ptr for mimic Procesing "object references" behaviour
      std::shared_ptr<T> _ptr;
  public:
      ~ptr(){}// Zwalnianie zasobów
      ptr():_ptr(nullptr){}
      ptr(T* ini):_ptr(ini){}
      ptr(ptr<T>& other):_ptr(other._ptr){}
      ptr<T>& operator = (ptr<T>& other);
      ptr<T>& operator = (T* other);
      ptr<T>& operator = (nullptr_t);

      bool operator == (const ptr<T>&) const;
      bool operator != (const ptr<T>&) const;
      bool operator == (T*) const;
      bool operator != (T*) const;
      T* operator -> () { return _ptr.get();}
      operator T& () { return *_ptr;}
};

// Pojawił się problem z kompilatorem
//https://stackoverflow.com/questions/63314333/strange-behavior-of-gcc-are-c-object-definitions-with-and-equal-or-not
//array(size_t N,nullptr_t); To też nie pomaga :-/

template<class T>
class array
{
  ///INFO:
  //    T* _ptr;
  public:
      size_t length;

      ~array();//{ delete [] _ptr; }// Zwalnianie zasobów
      array(size_t N);

      T& operator [] (size_t i);
};

/*
template<class T>
class sarray
{
  public:
      ~sarray(){}
      sarray(){}
      sarray(array<T>* tab);
      sarray(std::initializer_list<T> lst);
      sarray<T>& operator = (array<T>* tab);
      T& operator [] (size_t i);
};
*/

template<class T>
class sarray
{
      ///INFO:
      //ptr< array<T> > _arr;//smart ptr to array?
  public:
      ~sarray(){}// Zwalnianie zasobów
      sarray(){}
      sarray(std::initializer_list<T> lst);
      sarray(array<T>* tab);
      sarray(nullptr_t);//Empty sarray
      sarray<T>& operator = (array<T>* tab);

      array<T>* operator -> ();
      T& operator [] (size_t i);// { return (*_arr)[i]; }
      //size_t length();//Potrzebne?
};

template<class T>
class matrix
{
  ///INFO:
  //    sarray<T>* _arr;//TABLICA TABLIC
  public:
      size_t length;

      ~matrix(){}// Zwalnianie zasobów
      matrix(size_t N,size_t M);

      sarray<T>& operator [] (size_t j);
};

/*
template<class T>
class smatrix
{
  public:
     ~smatrix(){}
     smatrix(){}
     smatrix(matrix<T>* tab);
     smatrix(std::initializer_list<T> lst);
     smatrix<T>& operator = (smatrix<T>* tab);

     size_t length();
     matrix<T>* operator -> ();
     sarray<T>& operator [] (size_t j);
};
*/

template<class T>
class smatrix
{
  ///INFO:
  ///    matrix<T>* _arr;//goły wskaźnik na matrix
  public:
      ~smatrix(){}// Zwalnianie zasobów
      smatrix(){}
      smatrix(matrix<T>* tab);
      smatrix(std::initializer_list<T> lst);//??? TODO TEST IT!

      size_t length();
      matrix<T>* operator -> ();
      sarray<T>& operator [] (size_t j);// { return (*_arr)[j]; }
};

/*

*/

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
//inline  sarray<T>::sarray(std::initializer_list<T> l)
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
#endif
