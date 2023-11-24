void processing_window::exit()
{
  save("exit.png"); //Without extension in Processing it produce TIFF, in C++ file format depend on implementation
  println("Bye...");
  processing_window_base::exit();     //What shoud be done by default!
}
//NOTE! ../../scripts did it 2023-10-11 14:12:39

