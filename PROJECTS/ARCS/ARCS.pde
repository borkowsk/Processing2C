//Division of the ellipse into sectors
//The coordinate system is treated as rotated!
void setup()
{
  
size(500,500);

arc(0,0,200,200,0,PI/2.0,OPEN);//or PIE or CHORD
ellipse(250, 250, 200, 200);

fill(0);
arc(250, 250, 190, 190, PI/2.0,PI);
fill(128);
arc(250, 250, 190, 190, PI,PI*2);
fill(255);

ellipseMode(CENTER);
arc(400,400,100,100,radians(0),radians(180),PIE);


//http://processingwedukacji.blogspot.com
saveFrame();//If saveFrame() is used without parameters, it will save files as screen-0000.tif, screen-0001.tif
}
