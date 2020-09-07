//Control parameters
int W=600;

int radius()
{
  return int(random(W/10));
}

//Initialisation
void setup()
{
  size(600,600);
  frameRate(1000);//Nie za dużo bo Xorg zablokuje kompa!
}

//Running - visualisation and dynamics (about 30 times per sec.)
void draw()
{
  fill(random(255),random(255),random(255),random(255));
  float r=radius();
  ellipse(random(W),random(W),r,r);
  println(frameRate);
}
