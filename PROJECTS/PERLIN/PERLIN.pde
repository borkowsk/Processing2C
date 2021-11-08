/// Perlin noise test for Processing2C
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: PERLIN.pde
////////////////////////////////////////////////////////////////////
// Based on Processing examples for Perlin noise
// See also: https://en.wikipedia.org/wiki/Perlin_noise

void setup() 
{
  size(200,200);
  //noiseSeed(10);
}

void draw()
{
  draw3();
  //draw4();//THIS IS STIL NOT COMPATIBLE WITH Processing2C
}

float xoff = 0.0;
float yoff = 0.1;   // 2nd dimension of perlin noise

void draw0() /// Used before definition
{
  stroke(random(256),0,0);//stroke(frameCount%256,2*frameCount/100,0);//stroke(0, 10);
  xoff = xoff + .01;
  float n = noise(xoff) * width;
  line(n, 0, n, height);
}

void draw1() /// May be used before definition
{
  background(255);
  xoff = xoff + .01;
  float n = noise(xoff) * width;
  line(n, 0, n, height);
}

float noiseScale = 0.10;

void draw2() /// May be used before definition
{
  background(0);
  for (int x=0; x < width; x++) {
    float noiseVal = noise((mouseX+x)*noiseScale, mouseY*noiseScale);//!!! mouseMove not work under Processing2C
    stroke(noiseVal*255);
    line(x, mouseY+noiseVal*80, x, height);
  }
}

void draw3() /// May be used before definition
{
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width/2; x++) {
      
      noiseDetail(1,0.5);
      float noiseVal = noise((mouseX+x) * noiseScale, (mouseY+y) * noiseScale);
      stroke(noiseVal*255);
      point(x,y);
      
      noiseDetail(4,0.65);
      noiseVal = noise((mouseX + x + width/2) * noiseScale, 
                       (mouseY + y) * noiseScale);
      stroke(noiseVal * 255);
      point(x + width/2, y);
    }
  }
}

void draw4() /// May be used before definition
{ //https://processing.org/examples/noisewave.html
  background(51);

  fill(255);
  // We are going to draw a polygon out of the wave points
  beginShape(); //THIS IS STIL NOT IMPLEMENTED IN Processing2C
  
  float xoff = 0;       // Option #1: 2D Noise
  //float xoff = yoff; // Option #2: 1D Noise
  
  // Iterate over horizontal pixels
  for (float x = 0; x <= width; x += 10) {
    // Calculate a y value according to... noise of course, then map to... 
    float y = map(noise(xoff, yoff), 0, 1, height/10,height); // Option #1: 2D Noise
    // float y = map(noise(xoff), 0, 1, 200,300);    // Option #2: 1D Noise
    
    // Set the vertex
    vertex(x, y); //THIS IS STIL NOT IMPLEMENTED IN Processing2C
    // Increment x dimension for noise
    xoff += 0.05;
  }
  // increment y dimension for noise
  yoff += 0.01;
  vertex(width, height);
  vertex(0, height);
  endShape(CLOSE);//THIS IS STIL NOT IMPLEMENTED IN Processing2C
}

//See also: https://www.openprocessing.org/sketch/494102/
