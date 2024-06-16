#include <IRremote.h>
#include<LiquidCrystal.h>
#define RECV_PIN 4

LiquidCrystal lcd(13,12,11,10,9,8); // LCD Pins

const int tempIn = A0; // Pin for the temp sensor
int redLED = 7; // Pin for the red LED
int greenLED = 6;  // Pin for the green LED
int blueLED = 3;   // Pin for the blue LED
int MotorPin = 5;   //moto pin

// Defining Variables
int motorSpeed = 0;
int tempFan = 25;
unsigned long results; // IR value
int RawValue= 0; // temp sensor value
double Voltage = 0;// temp sensor value in millivots
double tempC = 0;
double tempF = 0;

void setup()
{
  pinMode(MotorPin, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  
  pinMode(tempIn, INPUT);
  IrReceiver.begin(RECV_PIN);
  Serial.begin(9600);
  lcd.begin(16, 2); 
}

void loop(){
  
  // Temperature reading
  RawValue = analogRead(tempIn);
  Voltage = (RawValue / 1023.0) * 5000; // 5000 to get millivots.
  tempC = (Voltage-500) * 0.1; // 500 is the offset
  tempF = (tempC * 1.8) + 32; // convert to F
  
  Serial.print("Temperature in C = ");
  Serial.print(tempC,1);
  Serial.print("\t Temperature in F = ");
  Serial.println(tempF,1);
  
  lcd.setCursor(0,0);          
  lcd.print("Temperature:"); 
  lcd.print(tempC); 
  lcd.setCursor(0,1);           
  lcd.print("fan:"); 
  lcd.print(tempFan); 
  
  // Motor 
  if (tempC > tempFan) {
  	motorSpeed = map(tempC, 0, 125, 0, 255);
    analogWrite(MotorPin, motorSpeed);
  } else {
    analogWrite(MotorPin, 0);
  }
  
  // Led 
 if (tempC < 22) { // cold
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, HIGH);
    digitalWrite(redLED, LOW);
 }
  else if (tempC >= 22 && tempC <= 26) {
    digitalWrite(greenLED, HIGH);
    digitalWrite(blueLED, LOW);
    digitalWrite(redLED, LOW);
  } 
  else { // hot
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);
    digitalWrite(redLED, HIGH);
  }
  // IR sensor  
  if (IrReceiver.decode()){
 	results = IrReceiver.decodedIRData.decodedRawData;  
    switch(results){
      case 0xF708BF00: tempFan--; break; // button down
      case 0xF50ABF00: tempFan++; break; // button up
    }
      Serial.print("current temp to turn on fan: ");
      Serial.println(tempFan);
  }
  IrReceiver.resume();
  delay(100);
}
