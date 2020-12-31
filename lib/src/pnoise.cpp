//noise set of functions
#include "processing_consts.hpp"
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include <iostream>

// PERLIN NOISE
// Directly translated from PApplet.java
//
// [toxi 040903]
// octaves and amplitude amount per octave are now user controlled
// via the noiseDetail() function.

// [toxi 030902]
// cleaned up code and now using bagel's cosine table to speed up

// [toxi 030901]
// implementation by the german demo group farbrausch
// as used in their demo "art": http://www.farb-rausch.de/fr010src.zip

namespace Processing
{

class Random
{
    uint64_t seed=0;
public:
    void setSeed(uint64_t useed)
    { this->seed=useed;}
};


static const int PERLIN_YWRAPB = 4;
static const int PERLIN_YWRAP = 1<<PERLIN_YWRAPB;
static const int PERLIN_ZWRAPB = 8;
static const int PERLIN_ZWRAP = 1<<PERLIN_ZWRAPB;
static const int PERLIN_SIZE = 4095;

static int perlin_octaves = 4; // default to medium smooth
static float perlin_amp_falloff = 0.5f; // 50% reduction/octave

// [toxi 031112]
// new vars needed due to recent change of cos table in PGraphics
static int perlin_TWOPI;
static int perlin_PI;

float* perlin_cosTable;//[];
float* perlin;//[];

Processing::Random *perlinRandom;

float noise(float x)
{
   return noise(x, 0.0f, 0.0f);
}

float noise(float x,float  y)
{
   return noise(x, y, 0.0f);
}

void  noiseSeed(long seed)
{
    if (perlinRandom == nullptr) perlinRandom = new Random();
    perlinRandom->setSeed(seed);
    // force table reset after changing the random number seed [0122]
    perlin = nullptr;
}

void noiseDetail(int lod)
{
    if (lod>0) perlin_octaves=lod;
}

void noiseDetail(int lod,float falloff)
{
    if (lod>0) perlin_octaves=lod;
    if (falloff>0) perlin_amp_falloff=falloff;
}

// [toxi 031112]
  // now adjusts to the size of the cosLUT used via
  // the new variables, defined above
inline float noise_fsc(float i)
{
    // using bagel's cosine table instead
    return 0.5f*(1.0f-perlin_cosTable[(int)(i*perlin_PI)%perlin_TWOPI]);
}


float noise(float x,float  y,float  z)
{
    //processing/core/src/processing/core/PApplet.java:5300
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
}

}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2020-12-29                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
