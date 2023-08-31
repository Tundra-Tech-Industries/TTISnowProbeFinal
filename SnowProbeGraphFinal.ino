#include <SPI.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>

//touchscreen stuff
#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

#define MINPRESSURE 10
#define MAXPRESSURE 1000

int paused = 0;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define GREY    0x8410
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

MCUFRIEND_kbv tft;

int incrementation = 24;

int scale1 = 1;
int scale2 = 2;
int scale4 = 4;
int scale8 = 8;

void setup(void) {

tft.reset();
tft.begin(0x9341);
tft.fillScreen(BLACK);
tft.setRotation(1);
tft.fillRect(20,15,3,145,WHITE);
tft.fillRect(20,160,272,3,WHITE);

tft.setCursor(30,190);
tft.setTextColor(CYAN);
tft.setTextSize(1);
tft.println("Light Snow");

tft.setCursor(125,190);
tft.setTextColor(YELLOW);
tft.setTextSize(1);
tft.println("Medium Snow");

tft.setCursor(212,190);
tft.setTextColor(RED);
tft.setTextSize(1);
tft.println("Dense Snow");

tft.drawLine(33,160,33,166,WHITE);
tft.drawLine(43,160,43,166,WHITE);
tft.drawLine(53,160,53,166,WHITE);
tft.drawLine(63,160,63,166,WHITE);
tft.drawLine(73,160,73,166,WHITE);
tft.drawLine(83,160,83,166,WHITE);
tft.drawLine(93,160,93,166,WHITE);
tft.drawLine(103,160,103,166,WHITE);
tft.drawLine(113,160,113,166,WHITE);
tft.drawLine(123,160,123,166,WHITE);
tft.drawLine(133,160,133,166,WHITE);
tft.drawLine(143,160,143,166,WHITE);
tft.drawLine(153,160,153,166,WHITE);
tft.drawLine(163,160,163,166,WHITE);
tft.drawLine(173,160,173,166,WHITE);
tft.drawLine(183,160,183,166,WHITE);
tft.drawLine(193,160,193,166,WHITE);
tft.drawLine(203,160,203,166,WHITE);
tft.drawLine(213,160,213,166,WHITE);
tft.drawLine(223,160,223,166,WHITE);
tft.drawLine(233,160,233,166,WHITE);
tft.drawLine(243,160,243,166,WHITE);
tft.drawLine(253,160,253,166,WHITE);
tft.drawLine(263,160,263,166,WHITE);
tft.drawLine(273,160,273,166,WHITE);
tft.drawLine(283,160,283,166,WHITE);
tft.drawLine(17,87,20,87,WHITE);
tft.drawLine(17,15,20,15,WHITE);

tft.setCursor(3,3);
tft.setTextColor(WHITE);
tft.setTextSize(1);
tft.println("Analog Values (max : 1024) ");

tft.setCursor(188,171);
tft.setTextColor(WHITE);
tft.setTextSize(1);
tft.println("Time (in seconds)");

tft.setCursor(10,164);
tft.setTextColor(WHITE);
tft.setTextSize(1);
tft.println("0");

tft.setCursor(31,170);
tft.setTextColor(WHITE);
tft.setTextSize(1);
tft.println(scale1);

tft.setCursor(41,170);
tft.setTextColor(WHITE);
tft.setTextSize(1);
tft.println(scale2);

tft.setCursor(61,170);
tft.setTextColor(WHITE);
tft.setTextSize(1);
tft.println(scale4);

tft.setCursor(101,170);
tft.setTextColor(WHITE);
tft.setTextSize(1);
tft.println(scale8);

pinMode(13, OUTPUT);
}
void loop(void) {
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

unsigned long start = micros();

int vala = analogRead(A15);
/*
if (p.z > 500 && paused == 0) {
  paused = 1;
  Serial.print("paused");
  delay(1000);
}

if (p.z > 500 && paused == 1) {
  paused = 0;
  Serial.print("unpaused");
  delay(1000);
}

while (paused == 1) {
  delay(1);
}
*/

Serial.println(p.z);

int valab = map(vala,0,1024,159,15);

if (valab >= 140) {
  tft.drawLine(incrementation, 160, incrementation, valab, CYAN);
}

else if (valab >= 120 && valab < 140) {
  tft.drawLine(incrementation, 160, incrementation, valab, YELLOW);
}

else {
  tft.drawLine(incrementation, 160, incrementation, valab, RED);
}
incrementation++;

delay(100);

if(scale1==27){
tft.fillRect(3,120,16,60,BLACK);
}
if(incrementation>282){
tft.fillRect(10,166,100,12,BLACK);
scale1 = scale1+26;
scale2 = scale2+26;
scale4 = scale4+26;
scale8 = scale8+26;
tft.setCursor(26,170);
tft.setTextColor(WHITE);
tft.setTextSize(1);
tft.println(scale1);
tft.setCursor(41,170);
if(scale2>10){
tft.setCursor(39,170);
}
if(scale2<100){
tft.setTextColor(WHITE);
tft.setTextSize(1);
tft.println(scale2);
}
tft.setCursor(61,170);
tft.setTextColor(WHITE);
tft.setTextSize(1);
tft.println(scale4);
tft.setCursor(101,170);
tft.setTextColor(WHITE);
tft.setTextSize(1);
tft.println(scale8);
tft.fillRect(23,14,269,146,BLACK);

incrementation = 24;
}
return micros() - start;
}