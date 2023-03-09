  /*
  Color Sensor Calibration
  color-sensor-calib.ino
  Calibrate RGB Color Sensor output Pulse Widths
  Uses values obtained for RGB Sensor Demo sketch 
 
  DroneBot Workshop 2020
  https://dronebotworkshop.com
*/
 
// Define color sensor pins
 
#define S0 22
#define S1 21
#define S2 34
#define S3 32
#define sensorOut 33
 
// Variables for Color Pulse Width Measurements
 
int redPW = 0;
int greenPW = 0;
int bluePW = 0;
 
void setup() {
 
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
  
  // Setup Serial Monitor
  Serial.begin(115200);
}
 
void loop() {
  
	// Read Red Pulse Width
	redPW = getRedPW();
	// Delay to stabilize sensor
	delay(200);
	  
	// Read Green Pulse Width
	greenPW = getGreenPW();
	// Delay to stabilize sensor
	delay(200);
	  
	// Read Blue Pulse Width
	bluePW = getBluePW();
	// Delay to stabilize sensor
	delay(200);
	
	// Print output to Serial Monitor
	Serial.print("Red PW = ");
	Serial.print(redPW);
	Serial.print(" - Green PW = ");
	Serial.print(greenPW);
	Serial.print(" - Blue PW = ");
	Serial.println(bluePW);
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
		Serial.println("Red side");
	} 
	if ((redPW > 300 && 400 > redPW)&&(greenPW > 140 && 200 > greenPW)&&(bluePW > 120 && 200 > bluePW))
	{
		Serial.println("Blue side");
	} 
	if ((redPW > 150 && 210 > redPW)&&(greenPW > 170 && 250 > greenPW)&&(bluePW > 210 && 270 > bluePW))
	{
		Serial.println("Green side");
	} 
	*/
	//Values in dark
	if ((redPW > 130 && 150 > redPW)&&(greenPW > 100 && 145 > greenPW)&&(bluePW > 120 && 150 > bluePW))
	{
		Serial.println("White side");
	} 
	if (9redPW > 90 && 110 > redPW)&&(greenPW > 180 && 210 > greenPW)&&(2luePW > 225 && 250 > bluePW))
	{
		Serial.println("Yellow side");
	} 
	if ((redPW > 30 && 80 > redPW)&&(greenPW > 140 && 200 > greenPW)&&(bluePW > 170 && 230 > bluePW))
	{
		Serial.println("Orange side");
	} 
	if ((redPW > 110 && 150 > redPW)&&(greenPW > 270 && 330 > greenPW)&&(bluePW > 330 && 400 > bluePW))
	{
		Serial.println("Red side");
	} 
	if ((redPW > 300 && 400 > redPW)&&(greenPW > 140 && 200 > greenPW)&&(bluePW > 120 && 200 > bluePW))
	{
		Serial.println("Blue side");
	} 
	if ((redPW > 150 && 210 > redPW)&&(greenPW > 170 && 250 > greenPW)&&(bluePW > 210 && 270 > bluePW))
	{
		Serial.println("Green side");
	} 
}
 
 
// Function to read Red Pulse Widths
int getRedPW() {
 
  // Set sensor to read Red only
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
 
}
 
// Function to read Green Pulse Widths
int getGreenPW() {
 
  // Set sensor to read Green only
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
 
}
 
// Function to read Blue Pulse Widths
int getBluePW() {
 
  // Set sensor to read Blue only
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
 
}
