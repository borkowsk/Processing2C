// Obligatoryjne szablony dla obiektów i tablic
#pragma once
#ifndef PROCESSING_TEMPLATES_H
#define PROCESSING_TEMPLATES_H
#include <memory>
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
      //virtual ???
      ~ptr(){}// Zwalnianie zasobów
      ptr(ptr<T>& other):_ptr(other._ptr){}
      ptr(T* ini):_ptr(ini){}
      ptr():_ptr(nullptr){}
      ptr<T>& operator = (ptr<T>& other);

      T* operator -> () { return _ptr.get();}
      operator T& () { return *_ptr;}

      bool operator == (const ptr<T>&) const;
      bool operator != (const ptr<T>&) const;
      bool operator == (T*) const;
      bool operator != (T*) const;
};

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


template<class T>
class array
{
  ///INFO:
      T* _ptr;
  public:
      virtual ~array();// Zwalnianie zasobów
      size_t length;
      array(size_t N);
      array(array<T>* tab);//TEST IT! TODO
      T& operator [] (size_t i);
};


template<class T>
inline  array<T>::~array()
{

}
// Zwalnianie zasobów
template<class T>
inline  array<T>::array(size_t N)
{

}

template<class T>
inline  array<T>::array(array<T>* tab)
{

}
//TEST IT! TODO

template<class T>
inline  T& array<T>::operator [] (size_t i)
{

}


template<class T>
class sarray
{
      array<T>* _arr;//goły wskaźnik na array
  public:
      virtual ~sarray();// Zwalnianie zasobów
      sarray();
      sarray(array<T>* tab);
      sarray(nullptr_t);//Empty sarray
      sarray(std::initializer_list<T> l);
      size_t length();
      array<T>* operator -> ();
      T& operator [] (size_t i) { return (*_arr)[i]; }
};

template<class T>
inline  sarray<T>::~sarray()
{

}
// Zwalnianie zasobów

template<class T>
inline  sarray<T>::sarray()
{

}

template<class T>
inline  sarray<T>::sarray(array<T>* tab)
{

}

template<class T>
inline  sarray<T>::sarray(nullptr_t)
{

}
//Empty sarray

template<class T>
inline  sarray<T>::sarray(std::initializer_list<T> l)
{

}

template<class T>
inline  size_t sarray<T>::length()
{

}

template<class T>
inline  array<T>* sarray<T>::operator -> ()
{

}


template<class T>
class matrix
{
  ///INFO:
      sarray<T>* _arr;//TABLICA TABLIC
  public:
      size_t length;
      virtual ~matrix();// Zwalnianie zasobów
      matrix(size_t N,size_t M);
      matrix(array<T>* tab);//??? TEST IT! TODO!!!
      sarray<T>& operator [] (size_t j);
};

template<class T>
inline  matrix<T>::~matrix()
{

}

template<class T>
inline  matrix<T>::matrix(size_t N,size_t M)
{

}

template<class T>
inline  matrix<T>::matrix(array<T>* tab)
{

}
//??? TEST IT! TODO!!!

template<class T>
inline  sarray<T>& matrix<T>::operator [] (size_t j)
{

}


template<class T>
class smatrix
{
  ///INFO:
      matrix<T>* _arr;//goły wskaźnik na matrix
  public:
      virtual ~smatrix();// Zwalnianie zasobów
      smatrix();
      smatrix(matrix<T>* tab);
      smatrix(std::initializer_list<T> l);//??? TODO TEST IT!
      size_t length();
      matrix<T>* operator -> ();
      sarray<T>& operator [] (size_t j) { return (*_arr)[j]; }
};


template<class T>
inline  smatrix<T>::~smatrix()
{

}
// Zwalnianie zasobów

template<class T>
inline  smatrix<T>::smatrix()
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


}//END of namespace Processing
#endif
