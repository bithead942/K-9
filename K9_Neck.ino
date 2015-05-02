/************************************************************************
K9 Neck Sketch
by Bithead942

Board:  Arduino Uno

Controls the linear actuator that raises and lowers the neck.
An Adafruit motor shield v2 is on top of the Arduino Uno and 
provides forward and backward motor control of the linear actuator.
A 12V power source is connected to the shield to provide power for the
motor, and a separate 5V power source powers the Arduino.
The Arduio communicates with the shield via the SPI interface.

Pins:
   0 - Serial TX
   1 - Serial RX
   2 - 
   3 - 
   4 - 
   5 - 
   6 - 
   7 - RC Channel7 Input (AUX2 knob)
   8 - 
   9 - 
  10 -
  11 - 
  12 - 
  13 - 
  
  A0 - Linear actuator potentiometer
  
The make the movement more smooth, logic was added to adjust the delay
values while making a move - kind of a weak version of PID.  The dif value 
ranges from 0 to 55.  Also, an RC buffer value was added to reduce the 
amount of head adjustment when the unit is moving (and receiving mild 
bumps).
*************************************************************************/
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

const int RCbuffer = 5;

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *NeckMotor = AFMS.getMotor(1);
int ch3;
int neck;

void setup() {
  
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(7, INPUT);   // RC AUX2
  
  digitalWrite(A0, HIGH);  // set pullup on analog pin 0
  AFMS.begin();  

}
void loop() {
  ch3 = 0;
  for (int i = 0; i <= 3; i++) {
     ch3 = ch3 + pulseIn(7, HIGH, 25000);
  }
  ch3 = ch3/4;   //get average
  ch3 = (ch3 / 10) + 3;  //adjust RC input to align with linear actuator potentiometer
  neck =  analogRead(0);
//  Serial.print("RC = ");
//  Serial.print(ch3);
//  Serial.print("\t Neck = ");
//  Serial.println(neck);
  if (ch3 + RCbuffer <= neck || ch3 - RCbuffer >= neck) {
     if (ch3 < neck) {
       //Serial.println("Down");
       NeckGoDown();
     }
     else {
       //Serial.println("Up");
       NeckGoUp();
     }
  }
}

void NeckGoDown()
{
  int dif = 0;
  
  NeckMotor->run(FORWARD);
  NeckMotor->setSpeed(245);
  dif = neck - ch3;
  Serial.println(dif);
  if (dif >= 23) {delay(1000);}      //delay of 1000 adjust dif by 20
  else if (dif >= 12) {delay(300);}  //delay of 300 adjust dif by 7.5
  else {delay(90);}                 //delay of 100 adjust dif by 2.5
  NeckMotor->run(RELEASE);
}

void NeckGoUp()
{
  int dif = 0;
  
  NeckMotor->run(BACKWARD);
  NeckMotor->setSpeed(245);
  dif = ch3 - neck;
  Serial.println(dif);
  if (dif >= 23) {delay(1000);}      //delay of 1000 adjust dif by 20
  else if (dif >= 12) {delay(300);}  //delay of 300 adjust dif by 7.5
  else {delay(90);}                 //delay of 100 adjust dif by 2.5
  NeckMotor->run(RELEASE);
}
