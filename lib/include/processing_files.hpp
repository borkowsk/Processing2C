// processing_files.hpp
#pragma once
#ifndef PROCESSING_FILES_HPP
#define PROCESSING_FILES_HPP

//#include <type_traits> //W fstream jest problem dla QtCreatora z type_false z <type_traits>
//Ale ten include nie pomaga
#include "processing_library.hpp"
#include <fstream>

/// File streams
////////////////////////////////////////////////////////////////////////

namespace Processing
{
  class BufferedReader
  {
   ///INFO:
      std::ifstream* ptr;
   public:
      virtual ~BufferedReader();// zamknięcie i zwalnianie zasobów

      //Konstruktory
      BufferedReader(){ptr=nullptr;}
      BufferedReader(const std::nullptr_t&): BufferedReader(){}
      BufferedReader(std::ifstream* p) { ptr=p;}
      BufferedReader(BufferedReader& );
      BufferedReader(const BufferedReader& );//need for nullptr initialisation  BUT NOT USED?

      operator std::ifstream& () { return *_get();}

      BufferedReader& operator = (std::ifstream* p) { ptr=p;return *this;}
      BufferedReader& operator = (BufferedReader& );
      BufferedReader* operator -> () { return this; }

      bool operator == (const std::nullptr_t&) const { return ptr==nullptr; }
      bool operator != (const std::nullptr_t&) const { return ptr!=nullptr; }

      String readLine();

      void close() { if(ptr!=nullptr) ptr->close(); }

      //Not for everyday use
      void _set(std::ifstream* p)  { ptr=p;} //for createReader ONLY
      bool _ok() const { return ptr!=nullptr && ptr->is_open();}
      std::ifstream* _get() const;
  };

  BufferedReader& createReader(_string_param _name);

  inline
  String BufferedReader::readLine()
  {
      if(ptr!=nullptr)
      {
          String line;
          std::getline(*ptr, line._std_str());
          return line;
      }
      else return String(nullptr);
  }

  class PrintWriter
  {
   ///INFO:
      std::ofstream* ptr;
   public:
      virtual ~PrintWriter();// zamknięcie i zwalnianie zasobów

      //Konstruktory
      PrintWriter() {ptr=nullptr;}
      PrintWriter(const std::nullptr_t&): PrintWriter(){}
      PrintWriter(std::ofstream* p) { ptr=p;}
      PrintWriter(PrintWriter& );
      PrintWriter(const PrintWriter& );//need for nullptr initialisation BUT NOT USED?

      operator std::ofstream& () {return *_get();}

      PrintWriter&   operator = (std::ofstream* p) { ptr=p; return *this; }
      PrintWriter&   operator = (PrintWriter& );
      PrintWriter*   operator -> () { return this; }

      bool operator == (const std::nullptr_t&) const { return ptr==nullptr; }
      bool operator != (const std::nullptr_t&) const { return ptr!=nullptr; }

      void flush() { if(ptr!=nullptr) ptr->flush(); }
      void close() { if(ptr!=nullptr) ptr->close(); }

      //Not for everyday use
      bool _ok() const { return ptr!=nullptr && ptr->is_open();}
      void _set(std::ofstream* p)  { ptr=p;} //for createWriter ONLY
      std::ofstream* _get() const;
  };

  PrintWriter& createWriter(_string_param _name);

  //void print();//To bez sensu
  void print(PrintWriter& o,_string_param _p1="");
  //void print(PrintWriter& o,const String& );
  //void print(PrintWriter& o,const std::string& );

  void println(PrintWriter& o,_string_param _p1="");
  //void println(PrintWriter& o,const String& );
  //void println(PrintWriter& o,const std::string& );

}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2021-10-26                   */
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
