/// \file _impl_errors.h
/// \brief Macros for errors and function(s) for string concatenation which may helps
/// \author 'borkowsk'
/// \date 2022-11-21 (last modification)
/// \ingroup rtm
// //////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////
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

///\namespace Processing \brief P2C compatibility libraries
namespace Processing
{
    /// Function(s) that replaces ineffective "+" sequences,
    /// which also generate unnecessary warnings

    /// String concatenation in efficient function form
    ///  Both parameters may be String or what is convertable to String
    /// \param a1
    /// \param a2
    /// \return concatenated string
    String concat(const _string_param& a1,const _string_param& a2);

    /// Strong concatenation with 3 parameters
    String concat(const _string_param& a1,const _string_param& a2,const _string_param& a3);

    /// Strong concatenation with 4 parameters
    String concat(const _string_param& a1,const _string_param& a2,const _string_param& a3,const _string_param& a4);

    /// Strong concatenation with 5 parameters
    String concat(const _string_param& a1,const _string_param& a2,const _string_param& a3,const _string_param& a4,const _string_param& a5);

    /// String concatenation in efficient function form
    /// All parameters may be String or what is convertable to String
    /// \param a1
    /// \param a2
    /// \param a3
    /// \param a4
    /// \param a5
    /// \param a6
    /// \return concatenated string
    String concat(const _string_param& a1,const _string_param& a2,const _string_param& a3,const _string_param& a4,const _string_param& a5,const _string_param& a6);
}//END of namespace Processing
/* ****************************************************************** */
/*               PROCESSING2C  version 2022                           */
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
