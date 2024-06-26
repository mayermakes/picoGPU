
#include <PicoDVI.h>
#include <Fonts/FreeSansBold18pt7b.h>
DVIGFX16 display(DVI_RES_320x240p60, pico_sock_cfg);
//settings dependent on pinout chosen in HW design, be aware of impedance matching!!!


#include <Wire.h>
int lastmsg;
//wire is the i2c library
//this is the GPU code - this unit receives commands from the main mcu/cpu
//int SDA = 4;
//int SCL = 5; // default RPi pico pins
int ID = 0x05; //i2c ID this device. set in HW on ready made devices but set at will on MCUs
// MSG format: indexed 0
//ID,COM,TXT,colorcode,locX,locY,wide,tall,inverter,rotation

String MSG = "";//message buffer
String COM = ""; //command
String TXT = ""; //transmitted text
uint16_t colorcode;
int locX;
int locY;//location on screen
int wide = 1;
int tall = 1;
bool inverter=0;//invert display color 0= normal
int rotation = 0;//rotation of display 0= normal
void setup() {
Serial.begin(9600); //Debug output  
Wire.begin(ID); //change pins if needed
Wire.onReceive(receiveEvent);
display.begin();
delay(5000);
Serial.println("GPU ready");

}
void receiveEvent(int howMany){
  MSG = "";//CLEAR BUFFER 
  while( Wire.available()){
    MSG += (char)Wire.read();
     
}

I2Cparser(MSG); // cut my String into pieces
lastmsg = howMany; //this is my last resort
executer(); //execution , no breathing
}

void I2Cparser(String msg){
  //ID,COM,TXT,colorcode,locX,locY,wide,tall,inverter,rotation

  //spilt MSG into elements
  //find the indexes of each element
int i1 = msg.indexOf(',');
int i2 = msg.indexOf(',', i1+1); 
int i3 = msg.indexOf(',', i2+1); 
int i4 = msg.indexOf(',', i3+1); 
int i5 = msg.indexOf(',', i4+1); 
int i6 = msg.indexOf(',', i5+1); 
int i7 = msg.indexOf(',', i6+1); 
int i8 = msg.indexOf(',', i7+1); 
int i9 = msg.indexOf(',', i8+1); 
int i10 = msg.indexOf(',', i9+1); 
//sort values to each substring and convert to integer if needed
//String STRID = msg.substring(0, i1);
//ID = STRID.toInt(); //left better show how parsing is done. also this could be used as a check for multiple gpus on a bus if the data was meant for them.
//but ID shall not be reassigned to not screw up the adressing.
COM = msg.substring(i1+1, i2);
TXT = msg.substring(i2+1, i3);
String STRcolorcode = msg.substring(i3+1, i4);
colorcode = STRcolorcode.toInt();
String STRlocX = msg.substring(i4+1, i5);
locX = STRlocX.toInt();
String STRlocY = msg.substring(i5+1, i6);
locY = STRlocY.toInt();
String STRwide = msg.substring(i6+1, i7);
wide = STRwide.toInt();
String STRtall = msg.substring(i7+1, i8);
tall = STRtall.toInt();
String STRinverter = msg.substring(i8+1, i9);
inverter = STRinverter.toInt();
String STRrotation = msg.substring(i9+1, i10);
rotation = STRrotation.toInt();


//debug output:
Serial.print("ID=" );
Serial.println(ID);
Serial.print("COM=" );
Serial.println(COM);
Serial.print("TXT=" );
Serial.println(TXT);
Serial.print("colorcode=" );
Serial.println(colorcode);
Serial.print("locX=" );
Serial.println(locX);
Serial.print("locY=" );
Serial.println(locY);
Serial.print("wide=" );
Serial.println(wide); 
Serial.print("tall=" );
Serial.println(tall); 
Serial.print("inverter=" );
Serial.println(inverter);
Serial.print("rotation=" );
Serial.println(rotation);  
}



void GFXsetRotation(uint8_t r=0){
  display.setRotation(r);
}

void GFXfillScreen(uint16_t color){
  display.fillScreen(color);
  
}

void GFXinvertDisplay(bool i=0){
  display.invertDisplay(i);
}

void GFXshow_basic_text(String text,uint16_t color = 0,int x=0,int y=0,int w=1,int t=1) {
  
  
  display.setTextColor(color);//set color of text
  display.setFont();  // Use default font
  display.setCursor(x, y); // set cursor position
  display.setTextSize(w,t);   //set width and height           
  display.println(text); //print the text to the screen
} 

void GFXdrawPixel (int16_t x, int16_t y, uint16_t color){
  display.drawPixel(x, y, color);
}


// EXECUTER I CHOOSE YOUUUUUUUUUUU!!!!!!!!!!!!!!!1

void executer(){
  //execute command based on MSG contents
 //if COM == keyword--> do this and pass on the right values
  if (COM == "text"){
    GFXshow_basic_text(TXT,colorcode,locX,locY,wide,tall);
    
  }
  else if (COM == "fillscreen"){
    GFXfillScreen(colorcode);
  }
  else if (COM == "setRotation"){
    GFXsetRotation(rotation);
  }
  else if (COM == "invertDisplay"){
    GFXinvertDisplay(inverter);
  }
  else if (COM == "drawPixel"){
    GFXdrawPixel (locX, locY, colorcode);
  }
}

void loop() {
  //nothing...nothing.....nooooooooothiiiiiiiiing
}
