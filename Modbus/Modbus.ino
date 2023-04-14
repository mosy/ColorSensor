#include <WiFi.h>
#include "arduino_secrets.h"
#include <ModbusIP_ESP8266.h>


ModbusIP mb;
void setup(void) 
{

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
mb.addHreg(1,0xABCD);


}

void loop(void) 
{
   mb.task();
}
