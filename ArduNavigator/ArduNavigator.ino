#include <Wire.h>
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

///////////////////////////////////////////////////////////////////
//----- OLED instance
#define OLED_RESET 8
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
//----- BT instance
SoftwareSerial BTSerial(11, 10); //Connect HC-06, RX, TX
const int BTspeed = 9600;
///////////////////////////////////////////////////////////////////

//----- Bluetooth transaction parsing


#define TR_START_BYTE_1 0xfd
#define TR_START_BYTE_2 0xfe
#define TR_END_BYTE_1 0xfe
#define TR_END_BYTE_2 0xfe

byte btMessage[4];


//----- Navigator variables
boolean navMode;
char navUnit , //unit : m - meters , k - kmeters , f - feet , n - miles
     navDir ; //directions : f - forward ,b - back ,l - left ,r - right
unsigned int navDist , navAng; //distance,angle

//----- Graphic stuff
const short
  cex=SSD1306_LCDWIDTH/2,  //center coordinates
  cey=SSD1306_LCDHEIGHT/2,

  ox=cex+20,
  oy=cey,

  r=20,asp=3,aac=6;  //circle radius,default angular speed,acceleration (acceleration decreases as the value of aac increases)

float a,b,diff,ar,br,uasp,  //arrow angle,destination angle,their radiants counterparts, "updated" angular speed
ax,bx,cx,ay,by,cy,mx,my,dx,dy;  //coordinates of arrow vertexes and of destination

//-----Utils
#define DEBUG 0

void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);  // initialize with the I2C addr 0x3c (for the 128x64)
  display.display();    // show splashscreen
  delay(1000);
  display.clearDisplay();

  if(DEBUG)Serial.begin(9600);
  
  BTSerial.begin(BTspeed);

  a=0;

}

void loop()
{
  //  if(BTSerial.available())
  //    Serial.println(BTSerial.read(),BIN);
  receiveBluetoothData();
  getInfos();
  
  
  if(!navMode)
    compassMode();
  else
    directionsMode();


}


