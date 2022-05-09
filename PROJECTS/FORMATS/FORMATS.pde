/// Test foir number formating functions (test project for Processing2C)
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: "FORMATS.pde"
//*////////////////////////////////////////////////////////////////////////////////

int fontSize=16; ///< FontSize is not implemented in Pricessing2C
                 ///  but 16px is a default font hight there!

void setup()
{
  size(450,800);
  
  //Uncomment the following two lines to see the available fonts 
  //String[] fontList = PFont.list();
  //printArray(fontList);
  PFont myFont = createFont("Courier", 16); //Fixed width font
  textFont(myFont);
  textSize(fontSize);
  
  String forSplit="Ala ma kota i dwa psy";
  String[] splited=split(forSplit,' ');
  for(String s:splited)
    println(s);
    
  int pos=0;
  textAlign(LEFT,BOTTOM);
  text("nf*_________4:" + nf(4),10,pos+=fontSize);
  text("nf2_________4:" + nf(4,2),10,pos+=fontSize);
  text("nf2,1_______4:" + nf(4,2,1),10,pos+=fontSize);
  text("nf2________-4:" + nf(-4,2),10,pos+=fontSize);
  text("nf2,1______-4:" + nf(-4,2,1),10,pos+=fontSize);
  text("nf*____0.0001:" + nf(0.0001),10,pos+=fontSize);
//text("nf2____0.0001:" + nf(0.0001,2),10,pos+=fontSize);
  text("nf1,4__0.0001:" + nf(0.0001,1,4),10,pos+=fontSize);
  text("nf1,4_-0.0001:" + nf(-0.0001,1,4),10,pos+=fontSize);
  text("nf2,1__0.0001:" + nf(0.0001,2,1),10,pos+=fontSize);
  text("nf2,1__10000.:" + nf(10000.0,2,1),10,pos+=fontSize);
  text("nf2,1_-10000.:" + nf(-10000.0,2,1),10,pos+=fontSize);
  pos+=fontSize;
//text("nfs*________4:" + nfs(4),10,pos+=fontSize);
  text("nfs2________4:" + nfs(4,2),10,pos+=fontSize);
  text("nfs2,1______4:" + nfs(4,2,1),10,pos+=fontSize);
  text("nfs2_______-4:" + nfs(-4,2),10,pos+=fontSize);
  text("nfs2,1_____-4:" + nfs(-4,2,1),10,pos+=fontSize);
//text("nfs*___0.0001:" + nfs(0.0001),10,pos+=fontSize);
//text("nfs2___0.0001:" + nfs(0.0001,2),10,pos+=fontSize);
  text("nfs1,4_0.0001:" + nfs(0.0001,1,4),10,pos+=fontSize);
  text("nfs1,4-0.0001:" + nfs(-0.0001,1,4),10,pos+=fontSize);
  text("nfs2,1_0.0001:" + nfs(0.0001,2,1),10,pos+=fontSize);
  text("nfs2,1_10000.:" + nfs(10000.0,2,1),10,pos+=fontSize);
  text("nfs2,1-10000.:" + nfs(-10000.0,2,1),10,pos+=fontSize);
  pos+=fontSize;
//text("nfp*________4:" + nfp(4),10,pos+=fontSize);
  text("nfp2________4:" + nfp(4,2),10,pos+=fontSize);
  text("nfp2,1______4:" + nfp(4,2,1),10,pos+=fontSize);
  text("nfp2_______-4:" + nfp(-4,2),10,pos+=fontSize);
  text("nfp2,1_____-4:" + nfp(-4,2,1),10,pos+=fontSize);
//text("nfp*___0.0001:" + nfp(0.0001),10,pos+=fontSize);
//text("nfp2___0.0001:" + nfp(0.0001,2),10,pos+=fontSize);
  text("nfp1,4_0.0001:" + nfp(0.0001,1,4),10,pos+=fontSize);
  text("nfp1,4-0.0001:" + nfp(-0.0001,1,4),10,pos+=fontSize);
  text("nfp2,1_0.0001:" + nfp(0.0001,2,1),10,pos+=fontSize);
  text("nfp2,1_10000.:" + nfp(10000.0,2,1),10,pos+=fontSize);
  text("nfp2,1-10000.:" + nfp(-10000.0,2,1),10,pos+=fontSize);
  pos+=fontSize;
  text("nfc*________4:" + nfc(4),10,pos+=fontSize);
  text("nfc*_____4000:" + nfc(4000),10,pos+=fontSize);
  text("nfc2________4:" + nfc(4,2),10,pos+=fontSize);
  text("nfc2_______-4:" + nfc(-4,2),10,pos+=fontSize);
//text("nfc2,1_____-4:" + nfc(-4,2,1),10,pos+=fontSize);
//text("nfc2,1______4:" + nfc(4,2,1),10,pos+=fontSize);
//text("nfc*___0.0001:" + nfc(0.0001),10,pos+=fontSize);
  text("nfc2___0.0001:" + nfc(0.0001,2),10,pos+=fontSize);
  text("nfc2__-0.0001:" + nfc(-0.0001,2),10,pos+=fontSize);
//text("nfc1,4_0.0001:" + nfc(0.0001,1,4),10,pos+=fontSize);
//text("nfc2,1_0.0001:" + nfc(0.0001,2,1),10,pos+=fontSize);
  text("nfc2___10000.:" + nfc(10000.0,2),10,pos+=fontSize);
  text("nfc2__-10000.:" + nfc(-10000.0,2),10,pos+=fontSize);
  pos+=fontSize;
  int   value=0x5555;
  color gray=0xAAAAAA;
  text("hex____0x5555:" + hex(value)   ,10,pos+=fontSize);
  text("binary_0x5555:",10,pos+=fontSize);
  text("      " + binary(value),10,pos+=fontSize); 
  text("hex______gray:" + hex(gray)   ,10,pos+=fontSize);
  text("binary___gray:" ,10,pos+=fontSize);
  text("      " + binary(gray),10,pos+=fontSize); 
}

