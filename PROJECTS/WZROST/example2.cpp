#include <memory>

namespace Processing
{

template<class T>
class ptr : public std::shared_ptr<T>
{
  ///INFO: Proxy for standard shared_ptr for mimic Procesing "object references" behaviour
      ///std::shared_ptr<T> _ptr;
  public:
      //ptr();
      //ptr(ptr<T>&);
      //ptr(ptr<T>&&);
      //ptr(const ptr<T>&);//Needed for compilation but can not be impemented properly!
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
class sarray : public std::shared_ptr< array<T> >
{     // When the following line is commented out the error disapper! 
      //ptr< array<T> > _arr;//opaque smart ptr to array
      //std::shared_ptr< array<T> > _arr;//std smart pointer is OK
      // so what is missing in ptr<T> ? 
  public:
      ~sarray(){}
      sarray(){}
      sarray(array<T>* tab);
      //sarray(array<T>& tab);
      //sarray(const array<T>& tab);
      sarray<T>& operator = (array<T>* tab);
};

}

using namespace Processing;


void example()
{  
  sarray<bool>          test1 = new array<bool>(2);// Compiler error?
  sarray<bool>          test2;

  test2 = new array<bool>(2);//OK
  
  sarray<bool>   test3 { new array<bool>(2) };//OK      
}

