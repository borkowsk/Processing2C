/// \file
/// \brief Processing library functions connected with data & time
/// \author 'borkowsk'
/// \date 2023-04-03 (last modification)
///
/// \ingroup PROCESSING_compatibility
// //////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////

#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_window.hpp"
#include "processing_library.hpp"

#include <chrono>
#include <ctime>
#include <cstdint>
#include <iostream>

  using namespace std::chrono;

namespace Processing
{

/// @brief Replacement of JAVAs `System.currentTimeMillis()`
/// @details 
///     https://stackoverflow.com/questions/2831841/how-to-get-the-time-in-milliseconds-in-c
long long system_ctime_in_ms()
{
        auto time = system_clock::now(); // get the current time

        auto since_epoch = time.time_since_epoch(); // get the duration since epoch

        // I don't know what system_clock returns
        // I think it's uint64_t nanoseconds since epoch
        // Either way this duration_cast will do the right thing
        auto millis = duration_cast<milliseconds>(since_epoch);

        return  millis.count(); // just like java (new Date()).getTime();
}

//std::chrono::time_point?
auto tp=system_clock::now();
std::tm tm = std::tm{0}; //Last reading of time remain here

/// Date & time functions

inline void _readTime()
{
    tp=system_clock::now();
    std::time_t tt = std::chrono::system_clock::to_time_t(tp);
    gmtime_r(&tt, &tm);
}



int year()   /// The year() function returns the current year as an integer (2003, 2004, 2005, etc).
{
    _readTime();
    //std::cerr<<__FUNCTION__<<" will return "<<tm.tm_year+1900<<std::endl;
    return tm.tm_year+1900;
}

int month()  /// The month() function returns the current month as a value from 1 - 12.
{
    _readTime();
    //std::cerr<<__FUNCTION__<<" will return "<<tm.tm_mon + 1<<std::endl;
    return tm.tm_mon + 1;
}

int day()    /// The day() function returns the current day as a value from 1 - 31.
{
    _readTime();
    //std::cerr<<__FUNCTION__<<" will return "<<tm.tm_mday<<std::endl;
    return tm.tm_mday ;
}

int hour()   /// The hour() function returns the current hour as a value from 0 - 23.
{
    _readTime();
    //std::cerr<<__FUNCTION__<<" will return "<<tm.tm_hour<<std::endl;
    return tm.tm_hour ;
}

int minute() /// The minute() function returns the current minute as a value from 0 - 59.
{
    _readTime();
    //std::cerr<<__FUNCTION__<<" will return "<<tm.tm_min<<std::endl;
    return tm.tm_min ;
}

int second() /// The second() function returns the current second as a value from 0 - 59.
{
    _readTime();
    //std::cerr<<__FUNCTION__<<" will return "<<tm.tm_sec<<std::endl;
    return tm.tm_sec ;
}

int millis() /// Returns the number of milliseconds (thousandths of a second) since starting the program.
             /// This information is often used for timing events and animation sequences.
{
    tp=system_clock::now();
    auto tmp=tp.time_since_epoch();
    auto mili=duration_cast<milliseconds>(tmp).count()%1000;
    //std::cerr<<__FUNCTION__<<" will return "<<mili<<std::endl;
    return mili ;
}

}//END of namespace Processing
/* ******************************************************************
 *               PROCESSING2C  version 2022                         *
 ********************************************************************
 *           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 *
 *            W O J C I E C H   B O R K O W S K I                   *
 *          Robert Zajonc Institute for Social Studies,             *
 *                     UNIVERSITY OF WARSAW                         *
 *   (Instytut Studiów Społecznych Uniwersytetu Warszawskiego)      *
 *    WWW: http://iss.uw.edu.pl/en/ ; https://en.uw.edu.pl/         *
 *    RG : https://www.researchgate.net/profile/Wojciech-Borkowski  *
 *    GITHUB: https://github.com/borkowsk                           *
 *                                                                  *
 *                               (Don't change or remove this note) *
 ********************************************************************/

