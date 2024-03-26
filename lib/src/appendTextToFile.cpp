//
// Created by borkowsk on 26.03.24.
//
#include "processing_string.hpp"  //Processing::String class
#include <fstream>
using namespace std;

/// @note This may not be fully safe if file is append with more than one process concurrently!!!
void appendTextToFile(Processing::String fname, Processing::String line)
{
    ofstream app_out(fname, ios::app);
    app_out<<line<<endl;
    app_out.flush();
    app_out.close();
}