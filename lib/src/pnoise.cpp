//noise set of functions
#include "processing_consts.hpp"
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include <iostream>
#include <cmath>

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

class Random //JAVA like Random implementation
//https://docs.oracle.com/javase/8/docs/api/java/util/Random.html
{
    uint64_t seed=0;//Should be atomic in multithreated programs!
public:
    Random()
    //Creates a new random number generator.
    {
        seed=time(nullptr);
        seed=(seed ^ 0x5DEECE66DL) & ((1L << 48) - 1);
    }
    Random(long lseed)
    //Creates a new random number generator using a single long seed.
    {
        seed=lseed;
        seed=(seed ^ 0x5DEECE66DL) & ((1L << 48) - 1);
    }
    /**
     * @brief setSeed
     * @param useed
     * Sets the seed of this random number generator using a single long seed.
     * The general contract of setSeed is that it alters the state of this random number generator object
     * so as to be in exactly the same state as if it had just been created with the argument seed as a seed.
     * The method setSeed is implemented by class Random by atomically updating the seed to
        (seed ^ 0x5DEECE66DL) & ((1L << 48) - 1)
     */
    void setSeed(uint64_t useed)
    {
        seed=useed;
        seed=(seed ^ 0x5DEECE66DL) & ((1L << 48) - 1);
    }

    int nextInt()
    {
       return next(32);
    }

    /**
     * @brief nextFloat
     * @return float
     * Returns the next pseudorandom, uniformly distributed float value between 0.0 and 1.0
     * from this random number generator's sequence.
     */
    float	nextFloat()
    {
        return next(24) / ((float)(1 << 24));
    }

protected:
    /**
     * Generates the next pseudorandom number. Subclasses should override this, as this is used by all other methods.
     * The general contract of next is that it returns an int value and if the argument bits is between 1 and 32 (inclusive),
     * then that many low-order bits of the returned value will be (approximately) independently chosen bit values,
     * each of which is (approximately) equally likely to be 0 or 1.
     * The method next is implemented by class Random by atomically updating the seed to
        (seed * 0x5DEECE66DL + 0xBL) & ((1L << 48) - 1)
     * and returning
        (int)(seed >>> (48 - bits)).
     * This is a linear congruential pseudorandom number generator, as defined by D. H. Lehmer and described by Donald E. Knuth
     * in The Art of Computer Programming, Volume 3: Seminumerical Algorithms, section 3.2.1.
     */
    int next(int bits)
    {
        seed=(seed * 0x5DEECE66DL + 0xBL) & ((1L << 48) - 1);
        return (int)(seed >> (48 - bits));
    }
};

// precalculate sin/cos lookup tables [toxi]
// circle resolution is determined from the actual used radii
// passed to ellipse() method. this will automatically take any
// scale transformations into account too

// [toxi 031031]
// changed table's precision to 0.5 degree steps
// introduced new vars for more flexible code
static class SinCos
{
public:
  float*    sinLUT;
  float*    cosLUT;
  float     SINCOS_PRECISION = 0.5f;
  int       SINCOS_LENGTH = (int) (360.0f / SINCOS_PRECISION);

  SinCos()
  {
    sinLUT = new float[SINCOS_LENGTH];
    cosLUT = new float[SINCOS_LENGTH];
    for (int i = 0; i < SINCOS_LENGTH; i++)
    {
      sinLUT[i] = (float) sin(i * DEG_TO_RAD * SINCOS_PRECISION);
      cosLUT[i] = (float) cos(i * DEG_TO_RAD * SINCOS_PRECISION);
    }
  }

  ~SinCos()
  {
      delete [] sinLUT;
      delete [] cosLUT;
  }
} sincos;


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

/**
   * ( begin auto-generated from noise.xml )
   *
   * Returns the Perlin noise value at specified coordinates. Perlin noise is
   * a random sequence generator producing a more natural ordered, harmonic
   * succession of numbers compared to the standard <b>random()</b> function.
   * It was invented by Ken Perlin in the 1980s and been used since in
   * graphical applications to produce procedural textures, natural motion,
   * shapes, terrains etc.<br /><br /> The main difference to the
   * <b>random()</b> function is that Perlin noise is defined in an infinite
   * n-dimensional space where each pair of coordinates corresponds to a
   * fixed semi-random value (fixed only for the lifespan of the program).
   * The resulting value will always be between 0.0 and 1.0. Processing can
   * compute 1D, 2D and 3D noise, depending on the number of coordinates
   * given. The noise value can be animated by moving through the noise space
   * as demonstrated in the example above. The 2nd and 3rd dimension can also
   * be interpreted as time.<br /><br />The actual noise is structured
   * similar to an audio signal, in respect to the function's use of
   * frequencies. Similar to the concept of harmonics in physics, perlin
   * noise is computed over several octaves which are added together for the
   * final result. <br /><br />Another way to adjust the character of the
   * resulting sequence is the scale of the input coordinates. As the
   * function works within an infinite space the value of the coordinates
   * doesn't matter as such, only the distance between successive coordinates
   * does (eg. when using <b>noise()</b> within a loop). As a general rule
   * the smaller the difference between coordinates, the smoother the
   * resulting noise sequence will be. Steps of 0.005-0.03 work best for most
   * applications, but this will differ depending on use.
   *
   * ( end auto-generated )
   *
   * @webref math:random
   * @param x x-coordinate in noise space
   * @param y y-coordinate in noise space
   * @param z z-coordinate in noise space
   * @see PApplet#noiseSeed(long)
   * @see PApplet#noiseDetail(int, float)
   * @see PApplet#random(float,float)
   */
float noise(float x,float  y,float  z)
{
    if (perlin == nullptr) {
          if (perlinRandom == nullptr) {
            perlinRandom = new Random();
          }
          perlin = new float[PERLIN_SIZE + 1];
          for (int i = 0; i < PERLIN_SIZE + 1; i++) {
            perlin[i] = perlinRandom->nextFloat(); //(float)Math.random();
          }
          // [toxi 031112]
          // noise broke due to recent change of cos table in PGraphics
          // this will take care of it
          perlin_cosTable = sincos.cosLUT;
          perlin_TWOPI = perlin_PI = sincos.SINCOS_LENGTH;
          perlin_PI >>= 1;
        }

        if (x<0) x=-x;
        if (y<0) y=-y;
        if (z<0) z=-z;

        int xi=(int)x, yi=(int)y, zi=(int)z;
        float xf = x - xi;
        float yf = y - yi;
        float zf = z - zi;
        float rxf, ryf;

        float r=0;
        float ampl=0.5f;

        float n1,n2,n3;

        for (int i=0; i<perlin_octaves; i++) {
          int of=xi+(yi<<PERLIN_YWRAPB)+(zi<<PERLIN_ZWRAPB);

          rxf=noise_fsc(xf);
          ryf=noise_fsc(yf);

          n1  = perlin[of&PERLIN_SIZE];
          n1 += rxf*(perlin[(of+1)&PERLIN_SIZE]-n1);
          n2  = perlin[(of+PERLIN_YWRAP)&PERLIN_SIZE];
          n2 += rxf*(perlin[(of+PERLIN_YWRAP+1)&PERLIN_SIZE]-n2);
          n1 += ryf*(n2-n1);

          of += PERLIN_ZWRAP;
          n2  = perlin[of&PERLIN_SIZE];
          n2 += rxf*(perlin[(of+1)&PERLIN_SIZE]-n2);
          n3  = perlin[(of+PERLIN_YWRAP)&PERLIN_SIZE];
          n3 += rxf*(perlin[(of+PERLIN_YWRAP+1)&PERLIN_SIZE]-n3);
          n2 += ryf*(n3-n2);

          n1 += noise_fsc(zf)*(n2-n1);

          r += n1*ampl;
          ampl *= perlin_amp_falloff;
          xi<<=1; xf*=2;
          yi<<=1; yf*=2;
          zi<<=1; zf*=2;

          if (xf>=1.0f) { xi++; xf--; }
          if (yf>=1.0f) { yi++; yf--; }
          if (zf>=1.0f) { zi++; zf--; }
        }
        return r;
}

}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2022-10-11                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
