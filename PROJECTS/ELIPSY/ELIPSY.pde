/// Simple graphics test for Processing2C
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: "ELIPSY.pde"
// @date 2024-09-30 (last change)
//*//////////////////////////////////////////////////////////////////

int W=600; /// Control parameter

int radius() ///< Example of the user declared function
{
  return int(random(W/10));
}

/// Initialisation
void setup()
{
  size(600,600);
  background(255);
  frameRate(500); // draw( ) about 500 times per sec.(if possible!)
                  //Nie za dużo bo Xorg zablokuje kompa!
}

/// Running - visualisation and dynamics
void draw()
{
  fill(random(255),random(255),random(255),random(255));
  float r=radius();
  float x=random(W);
  float y=random(W);
  ellipse(x,y,r,r);
  
  noStroke();
  //stroke(255);
  point(x,y);
  
  println(frameRate);
}
