#include <memory>
#include <initializer_list>

namespace Processing
{

template<class T>
class ptr
{
  ///INFO: Proxy for standard shared_ptr for mimic Procesing "object references" behaviour
      std::shared_ptr<T> _ptr;
  public:
      ~ptr(){}
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

template<class T>
class array
{     
      //T* content;
  public:
      ~array();
      array(size_t N);
};

template<class T>
class sarray
{     // When the following line is commented out the error disapper!
      // so what is missing in ptr<T> ?  
      //ptr< array<T> > _arr;//opaque smart ptr to array
      std::shared_ptr< array<T> > _arr;//std smart pointer is OK
  public:
      ~sarray(){}
      sarray(){}
      sarray(array<T>* tab);
      sarray(std::initializer_list<T> lst);
      sarray<T>& operator = (array<T>* tab);
};

template<class T>
class matrix
{
      //sarray<T>* content;
  public:
      ~matrix(){}
      matrix(size_t N,size_t M);
};

template<class T>
class smatrix
{
     //std::shared_ptr< matrix<T> > _arr;//std smart pointer is OK
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

}

using namespace Processing;


void example()
{
  smatrix<bool>         bools = new matrix<bool>(50,2);// OK
  
  sarray<bool>          test1 = new array<bool>(2);// Compiler error?
  sarray<bool>          test2;

  test2 = new array<bool>(2);//OK
  
  sarray<bool>   test3 { new array<bool>(2) };//OK      
}

