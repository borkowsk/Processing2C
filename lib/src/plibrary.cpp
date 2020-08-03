// most commonly used library functions
#include "processing_window.hpp"
#include "processing_library.hpp"
namespace Processing
{

String::~String()
{}//??? Na pewno potrzebne?

String::String()
{}

String::String(const char*)
{}

String::String(const String&)
{}

bool String::operator == (nullptr_t)
{}

bool String::operator != (nullptr_t)
{}

String& String::operator += (const String&)
{}

String& String::operator += (int)
{}

String& String::operator += (float)
{}

String& String::operator += (double)
{}

String& String::operator += (bool)
{}

String& String::operator  + (const String&) const
{}

String& String::operator  + (int) const
{}

String& String::operator  + (float) const
{}

String& String::operator  + (double) const
{}

String& String::operator  + (bool) const
{}


String& operator  + (int,const String&)
{}

String& operator  + (float,const String&)
{}

String& operator  + (double,const String&)
{}

String& operator  + (bool,const String&)
{}

_string_param::

_string_param::~_string_param()
        // Zwalnianie zasobów
{}

//_string_param::_string_param(const String& p):String(p){}
//_string_param::_string_param(const char *p):String(p){}

_string_param::_string_param(double p)
{}

_string_param::_string_param(float  p)
{}

_string_param::_string_param(int    p)
{}

_string_param::_string_param(void*  p)
{}

/// Simple functions
float random(double low,double hig)
{}

//inline float random(double hig){return random(0,hig); }

/// Parameters:
/// value 	float: the incoming value to be converted
/// start1 	float: lower bound of the value's current range
/// stop1 	float: upper bound of the value's current range
/// start2 	float: lower bound of the value's target range
/// stop2 	float: upper bound of the value's target range
float map(float value,float start1,float stop1,float start2,float stop2)
{}


/// Parameters:
/// value 	float: the incoming value to be converted
/// start 	float: lower bound of the value's current range
/// stop 	float: upper bound of the value's current range
float norm(float value,float start,float stop)
{}


/// Parameters:
/// start 	float: first value
/// stop 	float: second value
/// amt 	float: float between 0.0 and 1.0
float lerp(float start,float stop,float amt)
{}


/// Parameters:	napTime 	int: milliseconds to pause before running draw() again
void delay(int napTime)
{}

void saveFrame(const String& filename)
{}

void saveFrame(const std::string& filename)
{}

/// Extended graphix text()
void text(_string_param str,float x,float y)
{}

void text(_string_param str,float x1,float y1,float x2,float y2)
{}

//void text(const String& str,float x,float y);
//void text(const String& str,float x1,float y1,float x2,float y2);

/// File streams
PrintWriter::~PrintWriter()
{}
// Zwalnianie zasobów
PrintWriter::PrintWriter()
{}

PrintWriter::PrintWriter(PrintWriter&)
{}

std::fstream* PrintWriter::operator -> ()
{}

void PrintWriter::flush()
{}


PrintWriter& createWriter(const String&)
{}

PrintWriter& createWriter(const char* )
{}


//void print();//To bez sensu
void print(PrintWriter& o,_string_param _p1)
{}

//void print(PrintWriter& o,const String& );
//void print(PrintWriter& o,const std::string& );

void println(PrintWriter& o,_string_param _p1)
{}

//void println(PrintWriter& o,const String& );
//void println(PrintWriter& o,const std::string& );


}//END of namespace Processing
