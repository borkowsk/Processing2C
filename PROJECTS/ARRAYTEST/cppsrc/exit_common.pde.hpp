/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
/// @date 2026-01-29 (last change)
//*////////////////////////////////////////////////////

/// `exit()` function which save the const view of the window user area.
void processing_window::exit()
{
  save("exit.png"); //Without extension in Processing it produce TIFF, in C++ file format depend on implementation
  println("Bye...");
  processing_window_base::exit();     //What shoud be done by default!
}
//MADE NOTE: ../../scripts did it 2026-01-29 16:31:14 !

