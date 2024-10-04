/// Ellipse,Rect & Text alignment test for Processing2C
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: "ALIGNMENT.PDE"
// @date 2024-10-04 (last change)
//*///////////////////////////////////////////////////////////////


void cross(float x,float y)
{
  line(x-5,y,x+5,y);
  line(x,y-5,x,y+5);
}

float width1_2,width1_4,width3_4;
float height1_2,height1_4,height3_4;

void setVariables()
{
  width1_2=width/2;
  width1_4=width/4;
  width3_4=width1_4*3;
  height1_2=height/2;
  height1_4=height/4;
  height3_4=height1_4*3;
}

void processing_window::setup()
{
  size(600,600);
  setVariables();
  line(0,0,width,height);
  line(0,height,width,0);
  line(0,height1_2,width,height1_2);
  line(width1_2,height,width1_2,0);
  stroke(255);
  line(width1_4,height1_4,width3_4,height1_4);
  line(width1_4,height1_4,width1_4,height3_4);
  line(width1_4,height3_4,width3_4,height3_4);
  line(width3_4,height1_4,width3_4,height3_4);
  setFrameRate(3);
  textSize(16);
  text("DEFAULT",width/2,height/2);
}

void processing_window::draw()
{
  setVariables();
  stroke(random(255),random(255),random(255));
  float R,G,B;
  int selector=(int)random(5);
  
  switch(selector){
  case 0:
    rectMode(CORNER);  // Default rectMode is CORNER
    ellipseMode(CORNER);
    fill(R=random(255),G=random(255),B=random(255));
    rect(width1_4,height1_4,100,100);
    ellipse(width3_4,height3_4,100,100);
    fill(R=random(255),G=random(255),B=random(255));
    textAlign(LEFT,TOP);
    text("CORNER",width1_4,height1_4);
    text("CORNER",width3_4,height3_4);
  break;
  case 1:
    rectMode(CENTER);
    ellipseMode(CENTER);
    fill(R=random(255),G=random(255),B=random(255));
    rect(width1_4,height3_4,100,100);
    ellipse(width3_4,height1_4,100,100);
    fill(255-R,255-G,255-B);
    textAlign(CENTER,TOP);
    text("CENTER",width1_4,height3_4);
    text("CENTER",width3_4,height1_4);
  break;
  case 2:
    rectMode(CORNERS);
    ellipseMode(CORNERS);
    fill(R=random(255),G=random(255),B=random(255));
    rect(0,0,width1_4,width1_4);
    ellipse(width3_4,height3_4,width,height);
    fill(255-R,255-G,255-B);
    textAlign(RIGHT,BOTTOM);
    text("CORNERS",width1_4,height1_4);
    textAlign(RIGHT,BOTTOM);
    text("CORNERS",width,height);
  break;
  case 3:
    rectMode(RADIUS);
    ellipseMode(RADIUS);
    fill(R=random(255),G=random(255),B=random(255));
    rect(width1_4,height3_4,100,100);
    ellipse(width3_4,height1_4,100,100);
    fill(255-R,255-G,255-B);
    textAlign(CENTER,BOTTOM);
    text("RADIUS",width1_4,height3_4);
    text("RADIUS",width3_4,height1_4);
  break;
  default:
    fill(random(128),random(128),random(128));
    textAlign(CENTER,CENTER);
    text("CENTER*CENTER",width1_2,height1_2);
    textAlign(CENTER,TOP);
    text("^CENTER*TOP^",width1_2,0);
    textAlign(CENTER,BOTTOM);
    text("_CENTER*BOTTOM_",width1_2,height);
    textAlign(LEFT,TOP);
    text("|LEFT*TOP^",0,0);
    textAlign(LEFT,BOTTOM);
    text("|LEFT*BOTTOM_",0,height);
    textAlign(RIGHT,TOP);
    text("^TOP*RIGHT|",width,0);
    textAlign(RIGHT,BOTTOM);
    text("_BOTTOM*RIGHT|",width,height);
  break;
  }
  stroke(0);
  cross(0,0);
  cross(width1_4,height1_4);
  cross(width3_4,height3_4);
  cross(width1_4,height3_4);
  cross(width3_4,height1_4);
  cross(width-1,height-1);
}

//NOTE! ../../scripts did it 2024-10-04 13:54:20

