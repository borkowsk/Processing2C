#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
#include "processing_inlines.hpp" //is optional. Use when project is already compilable

namespace Processing
{

int       max(int a,int b)
{
        return (a>b?a:b);
}

double    max(double a,double b)
{
        return (a>b?a:b);
}

}//END OF NAMESPACE Processing

