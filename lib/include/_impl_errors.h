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

namespace Processing
{
    /// A function(s) that replaces ineffective "+" sequences,
    /// which also generate unnecessary warnings
    String concat(const _string_param& a1,const _string_param& a2);
    String concat(const _string_param& a1,const _string_param& a2,const _string_param& a3);
    String concat(const _string_param& a1,const _string_param& a2,const _string_param& a3,const _string_param& a4);
    String concat(const _string_param& a1,const _string_param& a2,const _string_param& a3,const _string_param& a4,const _string_param& a5);
    String concat(const _string_param& a1,const _string_param& a2,const _string_param& a3,const _string_param& a4,const _string_param& a5,const _string_param& a6);
}//END of namespace Processing
/* ****************************************************************** */
/*               PROCESSING2C  version 2021-12-21                     */
/* ****************************************************************** */
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                   */
/*            W O J C I E C H   B O R K O W S K I                     */
/*    Instytut Studiów Społecznych Uniwersytetu Warszawskiego         */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI    */
/*    RG : https://www.researchgate.net/profile/Wojciech-Borkowski    */
/*    GITHUB: https://github.com/borkowsk                             */
/*                                                                    */
/*                                 (Don't change or remove this note) */
/* ****************************************************************** */
#endif // _IMPL_ERRORS_H
