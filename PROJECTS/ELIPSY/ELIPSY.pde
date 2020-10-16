/// Simple graphics test for Processing2C
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: ELIPSY.pde
////////////////////////////////////////////////////////////////////

int W=600;//Control parameter

int radius()
{
  return int(random(W/10));
}

//Initialisation
void setup()
{
  size(600,600);
  frameRate(500); // draw( ) about 500 times per sec.(if possible!)
                  //Nie za dużo bo Xorg zablokuje kompa!
}

//Running - visualisation and dynamics
void draw()
{
  fill(random(255),random(255),random(255),random(255));
  float r=radius();
  ellipse(random(W),random(W),r,r);
  println(frameRate);
}
