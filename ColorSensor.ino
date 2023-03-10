 
#include <Arduino.h>
#include "ModbusServerWiFi.h"
#include "arduino_secrets.h"

char ssid[] = SECRET_SSID ;
char pass[] = SECRET_PASS;
// Set up a Modbus server
ModbusServerWiFi MBserver;
IPAddress lIP;                      // assigned local IP

const uint8_t MY_SERVER(1);
uint16_t memo[128];                 // Test server memory

// Worker function for serverID=1, function code 0x03 or 0x04
ModbusMessage FC03(ModbusMessage request) {
  uint16_t addr = 0;        // Start address to read
  uint16_t wrds = 0;        // Number of words to read
  ModbusMessage response;

  // Get addr and words from data array. Values are MSB-first, get() will convert to binary
  request.get(2, addr);
  request.get(4, wrds);
  
  // address valid?
  if (!addr || addr > 128) {
    // No. Return error response
    response.setError(request.getServerID(), request.getFunctionCode(), ILLEGAL_DATA_ADDRESS);
    return response;
  }

  // Modbus address is 1..n, memory address 0..n-1
  addr--;

  // Number of words valid?
  if (!wrds || (addr + wrds) > 127) {
    // No. Return error response
    response.setError(request.getServerID(), request.getFunctionCode(), ILLEGAL_DATA_ADDRESS);
    return response;
  }

  // Prepare response
  response.add(request.getServerID(), request.getFunctionCode(), (uint8_t)(wrds * 2));

  // Loop over all words to be sent
  for (uint16_t i = 0; i < wrds; i++) {
    // Add word MSB-first to response buffer
    response.add(memo[addr + i]);
  }

  // Return the data response
  return response;
// Define color sensor pins
} 
#define S0 5 
#define S1 18
#define S2 16
#define S3 17
#define sensorOut 4
 
// Variables for Color Pulse Width Measurements
 
int redPW = 0;
int greenPW = 0;
int bluePW = 0;
 
void setup() {
 
// Init Serial
  Serial.begin(115200);
  while (!Serial) {}
  Serial.println("__ OK __");

  // Register the worker function with the Modbus server
  MBserver.registerWorker(MY_SERVER, READ_HOLD_REGISTER, &FC03);
  
  // Register the worker function again for another FC
  MBserver.registerWorker(MY_SERVER, READ_INPUT_REGISTER, &FC03);
  
  // Connect to WiFi 
  WiFi.begin(ssid, pass);
  delay(200);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }

  // print local IP address:
  lIP = WiFi.localIP();
  Serial.printf("My IP address: %u.%u.%u.%u\n", lIP[0], lIP[1], lIP[2], lIP[3]);

  // Initialize server memory with consecutive values
  for (uint16_t i = 0; i < 128; ++i) {
    memo[i] = (i * 2) << 8 | ((i * 2) + 1);
  }

  // Start the Modbus TCP server:
  // Port number 502, maximum of 4 clients in parallel, 10 seconds timeout
  MBserver.start(502, 4, 10000);
  // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Set Sensor output as input
  pinMode(sensorOut, INPUT);
  
  // Set Pulse Width scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
}
 
void loop() {
  
  static uint32_t statusTime = millis();
  const uint32_t statusInterval(10000);
	// Read  Pulse Width
	redPW = getPW(LOW, LOW);
	greenPW = getPW(HIGH, HIGH);
	bluePW = getPW(LOW, HIGH);
	  

  // We will be idling around here - all is done in subtasks :D
  if (millis() - statusTime > statusInterval) {
    Serial.printf("%d clients running.\n", MBserver.activeClients());
    statusTime = millis();
  }
	// Read Green Pulse Width
//	greenPW = getGreenPW();
	// Delay to stabilize sensor
	  
	// Read Blue Pulse Width
//	bluePW = getBluePW();
	// Delay to stabilize sensor
	// Print output to Serial Monitor
	Serial.print("Red PW = ");
	Serial.print(redPW);
	Serial.print(" - Green PW = ");
	Serial.print(greenPW);
	Serial.print(" - Blue PW = ");
	Serial.println(bluePW);
memo[0]=redPW;
memo[1]=greenPW;
memo[2]=bluePW;
/*Values in light	
	if ((redPW > 78 && 108 > redPW)&&(greenPW > 68 && 101 > greenPW)&&(bluePW > 85 && 123 > bluePW))
	{
		Serial.println("White side");
	} 
	if ((redPW > 50 && 82 > redPW)&&(greenPW > 90 && 170 > greenPW)&&(bluePW > 138 && 190 > bluePW))
	{
		Serial.println("Yellow side");
	} 
	if ((redPW > 30 && 80 > redPW)&&(greenPW > 140 && 200 > greenPW)&&(bluePW > 170 && 230 > bluePW))
	{
		Serial.println("Orange side");
	} 
	if ((redPW > 76 && 118 > redPW)&&(greenPW > 170 && 320 > greenPW)&&(bluePW > 234 && 320 > bluePW))
	{
	rintln("Green side");
	} 
	*/
	//Values in dark
	/*
	if ((redPW > 250 && 310 > redPW)&&(greenPW > 270 && 330 > greenPW)&&(bluePW > 220 && 280 > bluePW))
	{
		Serial.println("White side");
	} 
	if ((redPW > 240 && 300 > redPW)&&(greenPW > 270 && 330 > greenPW)&&(bluePW > 390 && 450 > bluePW))
	{
		Serial.println("Yellow side");
	} 
	if ((redPW > 170 && 230 > redPW)&&(greenPW > 470 && 540 > greenPW)&&(bluePW > 430 && 490 > bluePW))
	{
		Serial.println("Orange side");
	} 
	if ((redPW > 220 && 290 > redPW)&&(greenPW > 580 && 650 > greenPW)&&(bluePW > 470 && 530 > bluePW))
	{
		Serial.println("Red side");
	} 
	if ((redPW > 600 && 670 > redPW)&&(greenPW > 570 && 640 > greenPW)&&(bluePW > 370 && 440 > bluePW))
	{
		Serial.println("Blue side");
	} 
	if ((redPW > 470 && 540 > redPW)&&(greenPW > 370 && 430 > greenPW)&&(bluePW > 440 && 500 > bluePW))
	{
		Serial.println("Green side");
	} 
	*/
}
 
 
// Function to read Red Pulse Widths
int getPW(bool x, bool y) {
 
  // Set sensor to read color only
  digitalWrite(S2,x);
  digitalWrite(S3,y);
  // Define integer to represent Pulse Width
  int PW;
  long sum = 0;
  int array[10];
  for (int i = 0 ; i < 10 ; i++)
  {

  // Fill up array with values
        array[i] = pulseIn(sensorOut, LOW);
//	delay(100);
  }
  // Return the sum value of array
  for (int i = 0 ; i < 10 ; i++)
  sum += array[i];
  // Get average
  PW=sum / 10;
  return PW;
 
}
