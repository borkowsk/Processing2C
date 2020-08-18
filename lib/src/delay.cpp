#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "SYMSHELL/symshell.h"
#include <iostream>

namespace Processing
{

/// Parameters:	napTime 	int: milliseconds to pause before running draw() again
void delay(int napTime)
{
    delay_ms(napTime);
}

}//END of namespace Processing

