//Procesing/Java Object class
#include "processing_consts.hpp"
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include <iostream>

namespace Processing
{

    long Object::hashCode() const
    ///	returns the hashcode number for this object
    {
        std::cout<<__FUNCTION__<<" - not implemented! "<<std::endl;
        return (size_t)this;
    }

}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2020-11-15                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
