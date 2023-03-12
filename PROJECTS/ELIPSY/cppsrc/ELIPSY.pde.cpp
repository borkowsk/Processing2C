/// Simple graphics test for Processing2C
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: "ELIPSY.pde"
//*//////////////////////////////////////////////////////////////////

int W=600; /// Control parameter

int radius() ///< Example of the user declared function
{
  return int(random(W/10));
}

/// Initialisation
void processing_window::setup()
{
  size(600,600);
  setFrameRate(500); // draw( ) about 500 times per sec.(if possible!)
                  //Nie za dużo bo Xorg zablokuje kompa!
}

/// Running - visualisation and dynamics
void processing_window::draw()
{
  fill(random(255),random(255),random(255),random(255));
  float r=radius();
  float x=random(W);
  float y=random(W);
  ellipse(x,y,r,r);
  stroke(255);
  point(x,y);
  println(frameRate);
}

//NOTE! ../../scripts did it

