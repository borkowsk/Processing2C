/// @file
/// @note Automatically made from _exit_common.pde_ by __Processing to C++__ converter (../../scripts/procesing2cpp.sh).
/// @date 2024-10-15 16:11:05 (translation)
//
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_window.hpp"
#ifndef _NO_INLINE
#include "processing_inlines.hpp" //...is optional.
#endif // _NO_INLINE
#include "processing_string.hpp"  //Processing::String class
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
using namespace Processing;
#include "local.h" //???.
#include <iostream>
//================================================================

/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
/// @date 2024-10-04 (last change)
//*////////////////////////////////////////////////////

/// `exit()` function which save the const view of the window user area.
void processing_window::exit()
{
  save("exit.png"); //Without extension in Processing it produce TIFF, in C++ file format depend on implementation
  println("Bye...");
  processing_window_base::exit();     //What shoud be done by default!
}
//MADE NOTE: ../../scripts did it 2024-10-15 16:11:05 !

