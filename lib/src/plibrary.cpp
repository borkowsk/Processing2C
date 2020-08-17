// most commonly used library functions
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include <iostream>

namespace Processing
{

String::~String()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}//??? Na pewno potrzebne?

String::String()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String::String(const char*)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String::String(const String&)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

bool String::operator == (nullptr_t)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

bool String::operator != (nullptr_t)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String& String::operator += (const String&)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String& String::operator += (int)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String& String::operator += (float)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String& String::operator += (double)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String& String::operator += (bool)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String& String::operator  + (const String&) const
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String& String::operator  + (int) const
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String& String::operator  + (float) const
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String& String::operator  + (double) const
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String& String::operator  + (bool) const
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}


String& operator  + (int,const String&)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String& operator  + (float,const String&)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String& operator  + (double,const String&)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

String& operator  + (bool,const String&)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

_string_param::

_string_param::~_string_param()
        // Zwalnianie zasobów
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

//_string_param::_string_param(const String& p):String(p){
//    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
//}
//_string_param::_string_param(const char *p):String(p){
//    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
//}

_string_param::_string_param(double p)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

_string_param::_string_param(float  p)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

_string_param::_string_param(int    p)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

_string_param::_string_param(void*  p)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

/// Simple functions
float random(double low,double hig)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

//inline float random(double hig){return random(0,hig); }

/// Parameters:
/// value 	float: the incoming value to be converted
/// start1 	float: lower bound of the value's current range
/// stop1 	float: upper bound of the value's current range
/// start2 	float: lower bound of the value's target range
/// stop2 	float: upper bound of the value's target range
float map(float value,float start1,float stop1,float start2,float stop2)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}


/// Parameters:
/// value 	float: the incoming value to be converted
/// start 	float: lower bound of the value's current range
/// stop 	float: upper bound of the value's current range
float norm(float value,float start,float stop)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}


/// Parameters:
/// start 	float: first value
/// stop 	float: second value
/// amt 	float: float between 0.0 and 1.0
float lerp(float start,float stop,float amt)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}


/// Parameters:	napTime 	int: milliseconds to pause before running draw() again
void delay(int napTime)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void saveFrame(const String& filename)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void saveFrame(const std::string& filename)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

/// Extended graphix text()
void text(_string_param str,float x,float y)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void text(_string_param str,float x1,float y1,float x2,float y2)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

//void text(const String& str,float x,float y);
//void text(const String& str,float x1,float y1,float x2,float y2);

/// File streams
PrintWriter::~PrintWriter()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}
// Zwalnianie zasobów
PrintWriter::PrintWriter()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

PrintWriter::PrintWriter(PrintWriter&)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

std::fstream* PrintWriter::operator -> ()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void PrintWriter::flush()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}


PrintWriter& createWriter(const String&)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

PrintWriter& createWriter(const char* )
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}


//void print();//To bez sensu
void print(PrintWriter& o,_string_param _p1)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

//void print(PrintWriter& o,const String& );
//void print(PrintWriter& o,const std::string& );

void println(PrintWriter& o,_string_param _p1)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

//void println(PrintWriter& o,const String& );
//void println(PrintWriter& o,const std::string& );

void saveFrame()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void saveFrame(const char* filename)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

}//END of namespace Processing
