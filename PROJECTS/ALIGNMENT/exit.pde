/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
/// @date 2024-09-30 (last change)
//*////////////////////////////////////////////////////

void exit()
{
  save("exit.png"); //Without extension in Processing it produce TIFF, in C++ file format depend on implementation
  println("Bye...");
  super.exit();     //What shoud be done by default!
}
