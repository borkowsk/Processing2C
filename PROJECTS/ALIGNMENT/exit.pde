void exit()
{
  save("exit.png"); //Without extension in Processing it produce TIFF, in C++ file format depend on implementation
  super.exit(); //What shoud be done by default!
}
