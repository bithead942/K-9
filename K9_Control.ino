/************************************************************************
K9 Control Sketch
by Bithead942

Board:  Arduino Uno

Controls multiple functions for K9 including the remote control voice 
commands, the Laser in his nose, the Ear movement, and the Eye sensor.

Pins:
   0 - Serial TX
   1 - Serial RX
   2 - Xbee TX
   3 - Xbee RX
   4 - 
   5 - RC Channel5 Input - Nose laser
   6 - RC Channel6 Input - Eye sensor
   7 - 
   8 - Laser LED
   9 - Nose Servo
  10 - Ear Servo
  11 - Eye Sensor Servo
  12 - MDFly (Sound Board) TX
  13 - MDFly (Sound Board) Busy

*************************************************************************/

#include <serMP3.h>
#include <SoftwareSerial.h>
#include <Servo.h>


#define Debug Serial
#define Channel5 5
#define Channel6 6
#define LaserLED 8

serMP3 mp3(12, 13); //TX pin, Busy Pin
SoftwareSerial Xbee(2, 3); // pin 2 = RX, pin 3 = TX

Servo NoseLaser;
Servo Ears;
Servo EyeSensor;

int inByte = 0;         // incoming serial byte
int ch5;                // Incoming RC pulse width for Channel 5 (Laser)
int ch6;                // Incoming RC pulse width for Channel 6 (Eye Sensor)

void setup() {
  pinMode(Channel5, INPUT);   //RC channel for Laser 
  pinMode(Channel6, INPUT);   //RC channel for Eye Sensor
  pinMode(LaserLED, OUTPUT);

  // initialize Serial ports
  Serial.begin(9600);
  Xbee.begin(9600);

  mp3.begin(24);  //Start MDFly with initial volume of 24

  NoseLaser.attach(9);
  Ears.attach(10);
  EyeSensor.attach(11);

 mp3.play(1);  //startup sound
  Serial.println("Ready.");
}

void loop() {
  //Ears.write(92);  //slow clockwise (92)
  Ears.write(65);  //slow counter-clockwise (77, 75)
 
  ch5 = pulseIn(Channel5, HIGH, 25000); // RC channel for Laser
  ch6 = pulseIn(Channel6, HIGH, 25000); // RC channel for Eye Sensor

  if (ch5 < 1000) {
    NoseLaser.write(900);  //Retract
    digitalWrite(LaserLED, LOW);
  }
  else {
    NoseLaser.write(2000);  //Extend
    digitalWrite(LaserLED, HIGH);
  }
  
  if (ch6 < 1000) {
    EyeSensor.write(15);  //Retract
  }
  else {
    EyeSensor.write(110);  //Extendff
  }

  if (Xbee.available() > 0) {
    inByte = Xbee.read();
    if (inByte >= 1 && inByte <= 13) {
      mp3.play(inByte);
      Serial.println(inByte);
    }
  }

  delay(10);
}
