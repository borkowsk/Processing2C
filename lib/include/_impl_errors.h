#ifndef _IMPL_ERRORS_H
#define _IMPL_ERRORS_H

//FOR NOT IMPLEMENTED OR BADLY USED FUNCTIONS also in 'not_implemented.h'
#include "_errMessage.hpp"

#define ERRMESSAGE( _XXX_ )              { _errMessage( _XXX_ , __FUNCTION__ , __LINE__ , __FILE__ ); }

#define ALWAYS_ERRMESSAGE( _XXX_ )       ERRMESSAGE( _XXX_ );

#define FIRST_TIME_ERRMESSAGE( _XXX_ )   {  static int flag=0;            \
                                            if(0==flag)                   \
                                            { flag=1;ERRMESSAGE( _XXX_ );} \
                                         }


/********************************************************************/
/*               PROCESSING2C  version 2021-11-12                   */
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
