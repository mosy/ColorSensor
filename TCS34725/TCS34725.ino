#include <Wire.h>
#include <WiFi.h>
#include "arduino_secrets.h"
#include <ModbusIP_ESP8266.h>
#include "Adafruit_TCS34725.h"
#include "SPI.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725();

bool redStat = false;
bool greenStat = false;
bool blueStat = false;
int deb = 0;
ModbusIP mb;
void setup(void) 
{

Wire.begin();
Serial.begin(9600);
WiFi.begin(SECRET_SSID, SECRET_PASS);
  
while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
}
 
Serial.println("");
Serial.println("WiFi connected");  
Serial.println("IP address: ");
Serial.println(WiFi.localIP());

mb.server();
mb.addIreg(1,0,3);




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

tcs.getRawData(&r, &g, &b, &c);
colorTemp = tcs.calculateColorTemperature(r, g, b);
//colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
lux = tcs.calculateLux(r, g, b);
   mb.task();
	mb.Ireg(1, r);
	mb.Ireg(2, g);
	mb.Ireg(3, b);
}
