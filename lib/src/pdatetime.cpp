// Processing library functions connected with data & time
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include <chrono>
#include <ctime>
#include <cstdint>
#include <iostream>

  using namespace std::chrono;

namespace Processing
{
    //std::chrono::time_point?
    auto tp=system_clock::now();
    std::tm tm = std::tm{0};//Last reading of time remain here

/// Date & time functions

inline void _readTime()
{
    tp=system_clock::now();
    std::time_t tt = std::chrono::system_clock::to_time_t(tp);
    std::tm tm = std::tm{0};
    gmtime_r(&tt, &tm);
}

int year()   /// The year() function returns the current year as an integer (2003, 2004, 2005, etc).
{
    _readTime();
    std::cerr<<__FUNCTION__<<" will return "<<tm.tm_year+1900<<std::endl;
    return tm.tm_year+1900;
}

int month()  /// The month() function returns the current month as a value from 1 - 12.
{
    _readTime();
    std::cerr<<__FUNCTION__<<" will return "<<tm.tm_mon + 1<<std::endl;
    return tm.tm_mon + 1;
}

int day()    /// The day() function returns the current day as a value from 1 - 31.
{
    _readTime();
    std::cerr<<__FUNCTION__<<" will return "<<tm.tm_mday<<std::endl;
    return tm.tm_mday ;
}

int hour()   /// The hour() function returns the current hour as a value from 0 - 23.
{
    _readTime();
    std::cerr<<__FUNCTION__<<" will return "<<tm.tm_hour<<std::endl;
    return tm.tm_hour ;
}

int minute() /// The minute() function returns the current minute as a value from 0 - 59.
{
    _readTime();
    std::cerr<<__FUNCTION__<<" will return "<<tm.tm_min<<std::endl;
    return tm.tm_min ;
}

int second() /// The second() function returns the current second as a value from 0 - 59.
{
    _readTime();
    std::cerr<<__FUNCTION__<<" will return "<<tm.tm_sec<<std::endl;
    return tm.tm_sec ;
}

int millis() /// Returns the number of milliseconds (thousandths of a second) since starting the program.
             /// This information is often used for timing events and animation sequences.
{
    tp=system_clock::now();
    auto tmp=tp.time_since_epoch();
    auto mili=duration_cast<milliseconds>(tmp).count();
    std::cerr<<__FUNCTION__<<" will return "<<mili<<std::endl;
    return mili ;
}

}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2020-10-01                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
