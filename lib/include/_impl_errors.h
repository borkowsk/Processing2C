#ifndef _IMPL_ERRORS_H
#define _IMPL_ERRORS_H

#include <iostream>

//FOR NOT IMPLEMENTED OR BADLY USED FUNCTIONS also in 'not_implemented.h'
#define ERRMESSAGE( _XXX_ ) { std::cerr<<__FUNCTION__<< _XXX_ <<std::endl;  }

#define ALWAYS_ERRMESSAGE( _XXX_ )       ERRMESSAGE( _XXX_ )

#define FIRST_TIME_ERRMESSAGE( _XXX_ )   {  static int flag=0;\
                                            if(0==flag++) \
                                                ERRMESSAGE( _XXX_ ) \
                                         }


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
#endif // _IMPL_ERRORS_H
