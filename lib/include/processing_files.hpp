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
  // An alternative to the currently used method of creating a reference to a type that mimics the JAVA class
  /// A class that adds methods that are not in std::ifstream but are in a JAVA class that we are faking
  /// See https://docs.oracle.com/javase/8/docs/api/java/io/BufferedReader.html for method details
  class _Jifstream:public std::ifstream
  {
  public:
      /// Tells whether this stream is ready to be read.
      /// A buffered character stream is ready if the buffer is not empty,
      /// or if the underlying character stream is ready.
      bool	ready() { return is_open() && peek() != EOF;}

      /// Reads a line of text.
      String readLine();

      /// Reads a single character.
      //int	read()

      ///Reads characters into a portion of an array.
      //int	read(char[] cbuf, int off, int len)

      ///Returns a Stream, the elements of which are lines read from this BufferedReader.
      //Stream<String>	lines();

      /// Tells whether this stream supports the mark() operation, which it does.
      bool	markSupported() { return false; }

      /// Marks the present position in the stream.
      //void	mark(int readAheadLimit);

      /// Resets the stream to the most recent mark.
      //void	reset()

      /// Skips characters.
      //long	skip(long n)
  };

  /// A class that adds methods that are not in std::ofstream but are in a JAVA class that we are faking
  /// See https://docs.oracle.com/javase/7/docs/api/java/io/PrintWriter.html for method details
  //class _Jofstream:public std::ofstream
  //{
  //};

  class BufferedReader: public  ptr<_Jifstream>
  {
   public:
      /// Constructors
      BufferedReader():  ptr<_Jifstream>(nullptr)
      {}
      BufferedReader(const std::nullptr_t&): BufferedReader()
      {}
      BufferedReader(_Jifstream* p):ptr<_Jifstream>(p)
      {}
      BufferedReader(BufferedReader& w):ptr<_Jifstream>(w)
      {}
      BufferedReader(const BufferedReader& w):ptr<_Jifstream>(w)
      {}
      /// Destructor
      virtual ~BufferedReader() = default;

      /// Default conversion
      operator _Jifstream& () { return *this->_get();}

      //??? is it really needed?
      void close() { if(_ok()) this->_get()->close(); }
      //BufferedReader& operator = (_Jifstream* p) { ptr=p;return *this;}
      //BufferedReader& operator = (BufferedReader& );
      //BufferedReader* operator -> () { return this; }
      //bool operator == (const std::nullptr_t&) const { return ptr==nullptr; }
      //bool operator != (const std::nullptr_t&) const { return ptr!=nullptr; }
      //bool operator == (const std::nullptr_t&) const { return ptr==nullptr; }
      //bool operator != (const std::nullptr_t&) const { return ptr!=nullptr; }

      String readLine();

      friend BufferedReader& createReader(_string_param _name);

  //Not for outside use
  protected:
      bool _ok() const
      {
          auto pom=_get();
          return  pom != nullptr
                  && pom->is_open();
      }
      _Jifstream* _get() const
      {
          return this->ptr<_Jifstream>::get();
      }
      void _set(std::ifstream* p); //for createReader ONLY
  };

  class PrintWriter:public ptr<std::ofstream>
  {
   public:
      /// Constructors
      PrintWriter(): ptr<std::ofstream>(nullptr)
      {}
      PrintWriter(const std::nullptr_t&): PrintWriter()
      {}
      PrintWriter(std::ofstream* p): ptr<std::ofstream>(p)
      {}
      PrintWriter(PrintWriter& w):ptr<std::ofstream>(w)
      {}
      PrintWriter(const PrintWriter& w):ptr<std::ofstream>(w)
      {}

      /// Destructor - // close the stream and release resources
      virtual ~PrintWriter()
      {}

      /// Default conversion
      operator std::ofstream& () {return *this->_get();}

      //??? is it really needed?
      //void flush() { if(_ok()) this->_get()->flush(); }
      //void close() { if(_ok()) this->_get()->close(); }
      //PrintWriter&   operator = (std::ofstream* p) { ptr=p; return *this; }
      //PrintWriter&   operator = (PrintWriter& );
      //PrintWriter*   operator -> () { return this; }
      //bool operator == (const std::nullptr_t&) const { return ptr==nullptr; }
      //bool operator != (const std::nullptr_t&) const { return ptr!=nullptr; }

      friend PrintWriter& createWriter(_string_param _name);

  //Not for outside use
  protected:
      bool _ok() const
      {
          auto pom=_get();
          return  pom != nullptr
                  && pom->is_open();
      }
      std::ofstream* _get() const
      {
          return this->ptr<std::ofstream>::get();
      }
      void _set(std::ofstream* p); //for createWriter ONLY
  };

  /// Create opaque std::ifstream connected to file 'name'
  BufferedReader& createReader(_string_param _name);

  /// Create opaque std::ofstream connected to file 'name'
  PrintWriter& createWriter(_string_param _name);

  /// Write something to opaqued stream
  void print(PrintWriter& o,_string_param _p1="");

  /// Write something to opaqued stream with \n at the end
  void println(PrintWriter& o,_string_param _p1="");

  /// Read whole line from opaqued stream (using .)
  inline String BufferedReader::readLine()
  {
    if(_ok())
    {
        String line;
        std::getline(*_get(), line._std_str());
        return line;
    }
    else return String(nullptr);// Totally empty string
  }

  //inline String readLine(BufferedReader& r)
  //{
  //  return r.readLine();
  //}

  /// Read whole line from the stream (using -> )
  inline String _Jifstream::readLine()
  {
      if(this->is_open())
      {
          String line;
          std::getline(*this, line._std_str());
          return line;
      }
      else return String(nullptr);// Totally empty string
  }

}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2021-12-07                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiów Społecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
#endif
