lib/src/parrayformat.cpp-1-/// Processing functions for formated arrays into Strings
lib/src/parrayformat.cpp-14-String nf(sarray<int> nums)
lib/src/parrayformat.cpp-19-String nf(sarray<int> nums,int digits)
lib/src/parrayformat.cpp-24-String nf(sarray<int> nums,int left,int right)
lib/src/parrayformat.cpp-29-String nf(sarray<float> nums)
lib/src/parrayformat.cpp-34-String nf(sarray<float> nums,int digits)
lib/src/parrayformat.cpp-39-String nf(sarray<float> nums,int left,int right)
lib/src/parrayformat.cpp-44-String nf(sarray<double> nums)
lib/src/parrayformat.cpp-49-String nf(sarray<double> nums,int digits)
lib/src/parrayformat.cpp-54-String nf(sarray<double> nums,int left,int right)
lib/src/parrayformat.cpp-62-String nfp(sarray<int> nums)
lib/src/parrayformat.cpp-67-String nfp(sarray<int> nums,int digits)
lib/src/parrayformat.cpp-72-String nfp(sarray<int> nums,int left,int right)
lib/src/parrayformat.cpp-77-String nfp(sarray<float> nums)
lib/src/parrayformat.cpp-82-String nfp(sarray<float> nums,int digits)
lib/src/parrayformat.cpp-87-String nfp(sarray<float> nums,int left,int right)
lib/src/parrayformat.cpp-92-String nfp(sarray<double> nums)
lib/src/parrayformat.cpp-97-String nfp(sarray<double> nums,int digits)
lib/src/parrayformat.cpp-105-String nfs(sarray<double> nums,int left,int right)
lib/src/parrayformat.cpp-110-String nfs(sarray<int> nums)
lib/src/parrayformat.cpp-115-String nfs(sarray<int> nums,int digits)
lib/src/parrayformat.cpp-120-String nfs(sarray<int> nums,int left,int right)
lib/src/parrayformat.cpp-125-String nfs(sarray<float> nums)
lib/src/parrayformat.cpp-130-String nfs(sarray<float> nums,int digits)
lib/src/parrayformat.cpp-135-String nfs(sarray<float> nums,int left,int right)
lib/src/parrayformat.cpp-140-String nfs(sarray<double> nums)
lib/src/parrayformat.cpp-145-String nfs(sarray<double> nums,int digits)
lib/src/parrayformat.cpp-151-String nfc(sarray<double> nums,int left,int right)
lib/src/parrayformat.cpp-156-String nfc(sarray<int> nums)
lib/src/parrayformat.cpp-161-String nfc(sarray<int> nums,int digits)
lib/src/parrayformat.cpp-166-String nfc(sarray<int> nums,int left,int right)
lib/src/parrayformat.cpp-171-String nfc(sarray<float> nums)
lib/src/parrayformat.cpp-176-String nfc(sarray<float> nums,int digits)
lib/src/parrayformat.cpp-181-String nfc(sarray<float> nums,int left,int right)
lib/src/parrayformat.cpp-186-String nfc(sarray<double> nums)
lib/src/parrayformat.cpp-191-String nfc(sarray<double> nums,int digits)
lib/src/pbasegrapx.cpp-22-void strokeCap(int cap)/// Parameters	cap 	int: either SQUARE, PROJECT, or ROUND
lib/src/pbasegrapx.cpp-27-void strokeJoin(int join)/// Parameters	join 	int: either MITER, BEVEL, ROUND
lib/src/pbasegrapx.cpp-32-int _LINE_WIDTH=1;
lib/src/pbasegrapx.cpp-288-void saveFrame()//PROCESSING: If saveFrame() is used without parameters, it will save files as screen-0000.tif, screen-0001.tif,
lib/src/pfont.cpp-14-PFont createFont(String fn,int s)
lib/src/pfont.cpp-21-void textFont(PFont f)
lib/src/pfont.cpp-27-void textLeading(int)
lib/src/pfont.cpp-33-void textMode(int)
lib/src/pfont.cpp-39-void textSize(int)
lib/src/pimage.cpp-14-    //void cursor(PImage img,int x,int y);
lib/src/pimage.cpp-15-    void cursor()
lib/src/pimage.cpp-20-    void noCursor()
lib/src/pimage.cpp-25-    //kind 	int: either ARROW, CROSS, HAND, MOVE, TEXT, or WAIT
lib/src/plists.cpp-10-float     FloatList::remove(int index)// 	Remove an element from the specified index
lib/src/plists.cpp-15-bool      FloatList::hasValue(float what)// 	Check if a number is a part of the list
lib/src/plists.cpp-20-void      FloatList::add(int index,float amount)// 	Add to a value
lib/src/plists.cpp-25-void      FloatList::sub(int index,float amount)// 	Subtract from a value
lib/src/plists.cpp-30-void      FloatList::mult(int index,float amount)// 	Multiply a value
lib/src/plists.cpp-35-void      FloatList::div(int index,float amount)// 	Divide a value
lib/src/plists.cpp-40-float     FloatList::min()// 	Return the smallest value
lib/src/plists.cpp-45-float     FloatList::max()// 	Return the largest value
lib/src/plists.cpp-50-void      FloatList::sort()// 	Sorts an array, lowest to highest
lib/src/plists.cpp-55-void      FloatList::sortReverse()// 	Reverse sort, orders values from highest to lowest
lib/src/plists.cpp-60-void      FloatList::reverse()// 	Reverse the order of the list elements
lib/src/plists.cpp-65-void      FloatList::shuffle()// 	Randomize the order of the list elements
lib/src/plists.cpp-70-sarray<float>     FloatList::array()// 	Create a new array with a copy of all the values
lib/src/plists.cpp-75-int      IntList::remove(int index)// 	Remove an element from the specified index
lib/src/plists.cpp-80-bool     IntList::hasValue(int   what)// 	Check if a number is a part of the list
lib/src/plists.cpp-85-void     IntList::add(int index,int   amount)// 	Add to a value
lib/src/plists.cpp-90-void     IntList::sub(int index,int   amount)// 	Subtract from a value
lib/src/plists.cpp-95-void     IntList::mult(int index,int   amount)// 	Multiply a value
lib/src/plists.cpp-100-void     IntList::div(int index,int   amount)// 	Divide a value
lib/src/plists.cpp-105-int      IntList::min()// 	Return the smallest value
lib/src/plists.cpp-110-int      IntList::max()// 	Return the largest value
lib/src/plists.cpp-115-void     IntList::sort()// 	Sorts an array, lowest to highest
lib/src/plists.cpp-120-void     IntList::sortReverse()// 	Reverse sort, orders values from highest to lowest
lib/src/plists.cpp-125-void     IntList::reverse()// 	Reverse the order of the list elements
lib/src/plists.cpp-130-void     IntList::shuffle()// 	Randomize the order of the list elements
lib/src/plists.cpp-135-sarray<int>  IntList::array()// 	Create a new array with a copy of all the values
lib/src/plists.cpp-140-String   StringList::remove(int index)// 	Remove an element from the specified index
lib/src/plists.cpp-145-bool     StringList::hasValue(_string_param   what)// Check if a number is a part of the list
lib/src/plists.cpp-150-void     StringList::sort()// 	Sorts an array, lowest to highest
lib/src/plists.cpp-156-void     StringList::sortReverse()// 	Reverse sort, orders values from highest to lowest
lib/src/plists.cpp-162-void     StringList::reverse()// 	Reverse the order of the list elements
lib/src/plists.cpp-168-void     StringList::shuffle()// 	Randomize the order of the list elements
lib/src/plists.cpp-174-void     StringList::lower()// 	Make the entire list lower case
lib/src/plists.cpp-180-void     StringList::upper()// 	Make the entire list upper case
lib/src/plists.cpp-186-sarray<int>  StringList::array()// 	Create a new array with a copy of all the values
lib/src/pnoise.cpp-11-    float noise(float x)
lib/src/pnoise.cpp-16-    float noise(float x,float  y)
lib/src/pnoise.cpp-21-    float noise(float x,float  y,float  z)
lib/src/pnoise.cpp-26-    void  noiseSeed(int seed)
lib/src/pnoise.cpp-31-    void noiseDetail(int lod)
lib/src/pnoise.cpp-36-    void noiseDetail(int lod,float falloff)
lib/src/pobject.cpp-11-    long Object::hashCode() const
lib/src/pshape.cpp-12-void beginShape()
lib/src/pshape.cpp-17-void beginShape(int kind)
lib/src/pshape.cpp-22-void endShape()
lib/src/pshape.cpp-27-void endShape(int mode)
lib/src/pshape.cpp-32-void vertex(float x,float y)
lib/src/pshape.cpp-37-void vertex(float x,float y,float z)
lib/src/pshape.cpp-42-void vertex(float v[])
lib/src/pshape.cpp-47-void vertex(float x,float y,float u,float v)
lib/src/pshape.cpp-52-void vertex(float x,float y,float z,float u,float v)
lib/src/pwindow.cpp-219-void redraw()
