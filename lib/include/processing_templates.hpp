// Obligatoryjne szablony dla obiektów i tablic
#pragma once
#ifndef PROCESSING_TEMPLATES_H
#define PROCESSING_TEMPLATES_H
namespace Processing
{

template<class T>
class ptr
{
  ///INFO:
     T* _ptr;
  public:
      virtual ~ptr();// Zwalnianie zasobów
      ptr(T* ini);
      ptr():_ptr(nullptr){}
      T* operator -> () { return _ptr;}
      operator T& ();
      bool operator == (const ptr&) const;
      bool operator != (const ptr&)const;
      bool operator == (T*) const;
      bool operator != (T*) const;
};

template<class T>
inline  ptr<T>::~ptr()
{

}

template<class T>
inline  ptr<T>::ptr(T* ini)
{

}

//https://en.cppreference.com/w/cpp/utility/initializer_list
//https://en.cppreference.com/w/cpp/language/constructor

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




}//END of namespace Processing
#endif
