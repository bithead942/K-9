/*
K9 Voice Remote Control
 by Bithead942
 
 Board:  Fio v3 3.3V/8MHz

 Remote control of the voice playback for the K9 platform

 The Fio v3 board initiates communication by sending a single character to the K9 platform via Xbee Pro (Series 1)
 There is only 1-way communication between the remote and the K9 unit.
 
 The character corresponds to a .WAV file stored on the Adafruit FX Sound Board:

 0:  I am K9 the Doctor's faithful friend
 1:  Affirmative
 2:  Negative
 3:  Insufficent Data to forumulate a reply
 4:  Laser (sound effect)
 5:  Computing (sound effect)
 6:  Most Satisfactory
 7:  I must check my records
 8:  Farewell
 9:  This unit does not appreciate the term "Dog", "Boy", or "Heel"
 A:  Danger, Doctor, Danger
 B:  It does not matter

 An rocker switch is used for fast scrolling through the list in either forward or reverse.  
 The selection is displayed on a 16x2 LCD display.  
 A button press sends the character for the corresponding selection.

 PINS USED:
 Serial1 (Xbee)
 Tx       0
 Rx       1
 
 Buttons
 D        8   Up
 D        9   Down
 D        10  Speak

 Display
 Rx       5
 Tx       6

 Other
 Trigger Button   4

 */
#include <SoftwareSerial.h>
#define Xbee Serial1
#define Debug Serial
#define btnUp 8
#define btnDown 9
#define btnSpeak 10


SoftwareSerial LCD(5, 6); // pin 5 = RX, pin 6 = TX
int OldVal = 0;
int NewVal = 0;

void setup() {

  // switch off ADC
  ADCSRA = ADCSRA & 0x7F;  // clear ADEN
  // switch off analog comparator
  ACSR = ACSR & 0x7F;

  // initialize Serial ports
  Debug.begin(9600);
  Xbee.begin(9600);  // Serial1 set up Serial1 port for 9600 baud
  LCD.begin(9600); // LCD set up serial port for 9600 baud
  delay(1000);  // wait for display to boot up
  pinMode(btnUp, INPUT);
  digitalWrite(btnUp, HIGH);
  pinMode(btnDown, INPUT);
  digitalWrite(btnDown, HIGH);
  pinMode(btnSpeak, INPUT);
  digitalWrite(btnSpeak, HIGH);

  LCD.write(254); // set cursor move mode
  LCD.write(128); // move cursor to beginning of first line
  LCD.write("1.  I am K9     ");
  LCD.write("                ");
  Debug.println("Ready.");
}

void loop() {
    if (NewVal != OldVal) {
      Debug.println(NewVal, DEC);
      switch (NewVal){
        case 1:
           LCD.write(254); // set cursor move mode
           LCD.write(128); // move cursor to beginning of first line
           LCD.write("1.  I am K9     ");
           LCD.write("                ");
           break;
        case 2:
           LCD.write(254); // set cursor move mode
           LCD.write(128); // move cursor to beginning of first line
           LCD.write("2.  Affirmative ");
           LCD.write("                ");
           break;
        case 3:
           LCD.write(254); // set cursor move mode
           LCD.write(128); // move cursor to beginning of first line
           LCD.write("3.  Negative    ");
           LCD.write("                ");
           break;
        case 4:
           LCD.write(254); // set cursor move mode
           LCD.write(128); // move cursor to beginning of first line
           LCD.write("4.  Insufficent ");
           LCD.write("    Data        ");
           break;
        case 5:
           LCD.write(254); // set cursor move mode
           LCD.write(128); // move cursor to beginning of first line
           LCD.write("5.  Laser sound ");
           LCD.write("                ");
           break;  
        case 6:
           LCD.write(254); // set cursor move mode
           LCD.write(128); // move cursor to beginning of first line
           LCD.write("6.  Computing   ");
           LCD.write("    sound       ");
           break;  
        case 7:
           LCD.write(254); // set cursor move mode
           LCD.write(128); // move cursor to beginning of first line
           LCD.write("7.  Most        ");
           LCD.write("    satisfactory");
           break;    
        case 8:
           LCD.write(254); // set cursor move mode
           LCD.write(128); // move cursor to beginning of first line
           LCD.write("8.  I must check");
           LCD.write("    my records  ");
           break;   
        case 9:
           LCD.write(254); // set cursor move mode
           LCD.write(128); // move cursor to beginning of first line
           LCD.write("9.  Farewell    ");
           LCD.write("                ");
           break;
        case 10:
           LCD.write(254); // set cursor move mode
           LCD.write(128); // move cursor to beginning of first line
           LCD.write("10.  Dog, Boy or");
           LCD.write("     Heel       ");
           break;
        case 11:
           LCD.write(254); // set cursor move mode
           LCD.write(128); // move cursor to beginning of first line
           LCD.write("11.  Danger,    ");
           LCD.write("  Doctor Danger!");
           break;
        case 12:
           LCD.write(254); // set cursor move mode
           LCD.write(128); // move cursor to beginning of first line
           LCD.write("12.  It does not");
           LCD.write("     matter     ");
           break;
      }
    OldVal = NewVal;
    delay(350);
  }
  if (digitalRead(btnSpeak) == LOW){
     Xbee.write(NewVal);
     LCD.write(254); // set cursor move mode
     LCD.write(128); // move cursor to beginning of first line
     LCD.write("      VOICE     ");
     LCD.write("     PLAYING    ");
     Debug.print("Button pressed: ");
     Debug.println(NewVal);
     OldVal = 25;  // force option to repaint after delay
     delay(1000);  // avoid multiple sends
  }
  
  if (digitalRead(btnUp) == LOW) {
     NewVal = NewVal + 1;
     if (NewVal > 12) {
       NewVal = 0;
     }
  }
  
  if (digitalRead(btnDown) == LOW) {
     NewVal = NewVal - 1;
     if (NewVal < 1) {
       NewVal = 12;
     }
  }
 
}
