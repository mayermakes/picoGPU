#include <Wire.h>
//wire is the i2c library
//this is the main/master code - this unit sends commands to the GPU-Rp2040
//int SDA = 4;
//int SCL = 5; // default RPi pico pins
int ID = 0x05; //i2c ID of the device we want to talk to. set in HW on ready made devices but set at will on MCUs

//#define BLACK 0x0000
//#define BLUE 0x001F
//#define RED 0xF800
//#define GREEN 0x07E0
//#define CYAN 0x07FF
//#define MAGENTA 0xF81F
//#define YELLOW 0xFFE0
//#define WHITE 0xFFFF




void setup() {
  
Wire.begin(); //change pins if needed
}



// MSG format: indexed 0
//ID,COM,TXT,colorcode,locX,locY,wide,tall,inverter,rotation

void i2ctransmit(int IDs=ID,String COM="text",String TXT="nothing", uint16_t colorcode=0xFFFF , int locX=0, int locY=0, int wide=1, int tall=1,bool inverter=0, int rotation=0){
    Wire.beginTransmission(IDs); // transmit to device #9
  Wire.print(IDs);
  Wire.write(",");
  Wire.print(COM);
  Wire.write(",");
  Wire.print(TXT);
  Wire.write(",");
  Wire.print(colorcode);
  Wire.write(",");
  Wire.print(locX);
  Wire.write(",");
  Wire.print(locY);
  Wire.write(",");
  Wire.print(wide);
  Wire.write(",");
  Wire.print(tall);
  Wire.write(",");
  Wire.print(inverter);
  Wire.write(",");
  Wire.print(rotation);
    Wire.endTransmission();    // stop transmitting
  
  delay(500);
}


void loop() {
randomSeed(analogRead(7));  
  // MSG format: indexed 0
//ID,COM,TXT,colorcode,locX,locY,wide,tall,inverter,rotation

i2ctransmit(ID,"fillscreen","nothing",0x0000, 0, 0, 1, 1,0,0);
delay(1000);
i2ctransmit(ID,"text","Hello World", 0xFFFF, 0, 0, 1, 1,0, 0);
delay(2000);  
i2ctransmit(ID,"fillscreen","nothing",random(0x0000,0xFFFF), 0, 0, 1, 1,0,0);
delay(1000);
i2ctransmit(ID,"setRotation","Hello World", 0xFFFF, 0, 0, 1, 1,0, 1);
i2ctransmit(ID,"text","Weird world", 0xFFFF, 20, 20, 4, 4,0, 0);
delay(2000);
i2ctransmit(ID,"invertDisplay","Hello World", 0xFFFF, 0, 0, 1, 1,1, 1);
i2ctransmit(ID,"setRotation","Hello World", 0xFFFF, 0, 0, 1, 1,0, 0);  
delay(1000);
i2ctransmit(ID,"text","ELEMENT14", 0xFFFF, 50, 50, 4, 2,0, 0);
delay(500);
i2ctransmit(ID,"text","presents", 0xFFFF, 100, 100, 2, 4,0, 0);
delay(500);
i2ctransmit(ID,"invertDisplay","Hello World", 0xFFFF, 0, 0, 1, 1,0, 0);
delay(1000);
i2ctransmit(ID,"fillscreen","nothing",0x0000, 0, 0, 1, 1,0,0);
for (int i=0;i>= 1000;i++){
i2ctransmit(ID,"drawPixel","nothing",random(0x0000,0xFFFF), random(0,320), random(0,240), 1, 1,0,0);
delay(50);
}
}
