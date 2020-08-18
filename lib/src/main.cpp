// main.cpp must be for Processing derived application
// but user may generate and use its own versions
//////////////////////////////////////////////////////////////
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include <iostream>

#define DEBUG 1

using namespace Processing;

Processing::processing_window Processing::_processing_window_instance;

static int DELAY=100;

int main(int argc, char *argv[])
{
#ifdef DEBUG
    std::cout<<"DEFAULT MAIN FOR PROCESSING2C TRANSLATOR"<<std::endl;//DEBUG
    std::cout<<"SETUP:"<<std::endl;//DEBUG
#endif
    _processing_window_instance.setup();
    while(1)
    {
#ifdef DEBUG
        std::cout<<"DRAW:"<<std::endl;//DEBUG
#endif
        _processing_window_instance.draw();
        delay(DELAY);
    }
    return 0;
}

