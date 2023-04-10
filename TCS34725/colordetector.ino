#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include "SPI.h"
#include "TFT_eSPI.h"
#include <TFT_Touch.h>

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite img = TFT_eSprite(&tft);
Adafruit_TCS34725 tcs = Adafruit_TCS34725();
TFT_Touch touch = TFT_Touch(33,25,32,39); //DCS, DCLK, DIN, DOUT

const int Led1Red = 4;
const int Led1Green = 16;
const int Led1Blue = 17;
bool redStat = false;
bool greenStat = false;
bool blueStat = false;
int deb = 0;
void setup(void) 
{

Wire.begin(27,22);
Serial.begin(9600);

pinMode(Led1Red, OUTPUT);  
pinMode(Led1Green, OUTPUT);  
pinMode(Led1Blue, OUTPUT);  
digitalWrite(Led1Red, HIGH);
digitalWrite(Led1Green, HIGH);
digitalWrite(Led1Blue, HIGH);

tft.begin();
tft.setRotation(2);
tft.fillScreen(TFT_BLACK);
tft.fillRect(20,140,40,40,TFT_DARKGREY);
tft.fillRect(20,200,40,40,TFT_DARKGREY);
tft.fillRect(20,260,40,40,TFT_DARKGREY);

img.setColorDepth(5);
img.createSprite(240,130);
img.fillSprite(TFT_BLACK);
img.setTextColor(TFT_GREEN, TFT_BLACK);

touch.setCal(0,4095,0,4095,240,320,0);//Raw xmin, xmax, ymin, ymax, width, height
touch.setRotation(2);

if (tcs.begin()) 
{
	Serial.println("Found sensor");
} 
else 
{
	Serial.println("No TCS34725 found ... check your connections");
	while (1);
}

}

void loop(void) 
{
uint16_t r, g, b, c, colorTemp, lux;
unsigned int X_Raw;
unsigned int Y_Raw;
X_Raw = touch.RawX();
Y_Raw = touch.RawY();

tcs.getRawData(&r, &g, &b, &c);
colorTemp = tcs.calculateColorTemperature(r, g, b);
//colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
lux = tcs.calculateLux(r, g, b);
img.fillSprite(TFT_BLACK);
img.drawString("Color Temperature :",20,20,2);img.drawNumber(colorTemp,150,20,2);
img.drawString("Lux :",20,35,2);img.drawNumber(lux,55,35,2);
img.drawString("R :",20,50,2);img.drawNumber(r,45,50,2);
img.drawString("G :",20,65,2);img.drawNumber(g,45,65,2);
img.drawString("B :",20,80,2);img.drawNumber(b,45,80,2);
//	img.drawString("C :",20,95,2);img.drawNumber(c,45,95,2);
if (touch.Pressed()) // Note this function updates coordinates stored within library variables
{ 
	img.drawString("X :",20,95,2);img.drawNumber(X_Raw,45,95,2);
	img.drawString("Y :",20,110,2);img.drawNumber(Y_Raw,45,110,2);
	if (deb==0)
	{
		deb=1;
		if (X_Raw > 500 && X_Raw < 1100 && Y_Raw > 1700 && Y_Raw < 2100)
		{
			if (redStat == false)
			{
				tft.fillRect(20,140,40,40,TFT_RED);
				digitalWrite(Led1Red,LOW);
				redStat = true;
			}
			else if (redStat == true)
			{
				tft.fillRect(20,140,40,40,TFT_DARKGREY);
				digitalWrite(Led1Red,HIGH);
				redStat = false;
			}
		}
		if (X_Raw > 500 && X_Raw < 1100 && Y_Raw > 1000 && Y_Raw < 1400)
		{
			if (greenStat == false)
			{
				tft.fillRect(20,200,40,40,TFT_GREEN);
				digitalWrite(Led1Green,LOW);
				greenStat = true;
			}
			else if (greenStat == true)
			{
				tft.fillRect(20,200,40,40,TFT_DARKGREY);
				digitalWrite(Led1Green,HIGH);
				greenStat = false;
			}
		}
		if (X_Raw > 500 && X_Raw < 1100 && Y_Raw > 350 && Y_Raw < 750)
		{
			if (blueStat== false)
			{
				tft.fillRect(20,260,40,40,TFT_BLUE);
				digitalWrite(Led1Blue,LOW);
				blueStat= true;
			}
			else if (blueStat == true)
			{
				tft.fillRect(20,260,40,40,TFT_DARKGREY);
				digitalWrite(Led1Blue,HIGH);
				blueStat = false;
			}
		}
	}
	else
	deb=0;

}
img.pushSprite(0,0);
}
