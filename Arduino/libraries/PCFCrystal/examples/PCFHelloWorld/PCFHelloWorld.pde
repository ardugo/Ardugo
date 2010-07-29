/*
PCFCrystal Library - Hello World

Demonstrates the use a 16x2 LCD display using the I2C capabilities of Arduino.
This library is a porting of the original LiquidCrystal library, prepared to
control the LCD display via one or two PCF8574.
The LiquidCrystal and PCFLiquidCrystal
libraries work with all LCD displays that are compatible with the
Hitachi HD44780 driver. There are many of them out there, and you
can usually tell them by the 16-pin interface.

This sketch prints "Hello World!" to the LCD
and shows the time and the time consumed to print a single character

The circuit (4 bits interface):
* LCD RS pin to PCF8574 output 5 (pin 10)
* LCD Enable pin to PCF8574 output 4 (pin 9)
* LCD D4 pin to PCF8574 output 0 (pin 4)
* LCD D5 pin to PCF8574 output 1 (pin 5)
* LCD D6 pin to PCF8574 output 2 (pin 6)
* LCD D7 pin to PCF8574 output 3 (pin 7)
* 10K resistor:
* ends to +5V and ground
* wiper to LCD VO pin (pin 3)

Library PCFCrystal created on June 2010
http://ardugonic.blogspot.com

Liquid Crystal:
Library originally added 18 Apr 2008
by David A. Mellis
library modified 5 Jul 2009
by Limor Fried (http://www.ladyada.net)
example added 9 Jul 2009
by Tom Igoe
modified 25 July 2009
by David A. Mellis


http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <Wire.h>
#include <PCFCrystal.h>

byte buffer = 0;
byte data = 0;
// initialize the library with the numbers of the interface pins
// rs, en, d0, d1, d2, d3, address, buffer
// 4 bits
PCFCrystal lcd(B00100000, B00010000, B00000001, B00000010, B00000100, B00001000, 0x20, &buffer);
// 8 bits
//PCFCrystal lcd(B00100000, B00010000, B10000000, B01000000, B00100000, B00010000, B00000001, B00000010, B00000100, B00001000, 0x21, 0x20, &data, &buffer);

void setup() {
  Wire.begin();
  
  // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("scnds:loop:micrs");
}

long counter = 0;
int led = HIGH;

void loop() {
  counter++;

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis()/1000);
  // print the number of loops since reset
  lcd.print(":");
  lcd.print(counter);
  // print the time to print 1 char
  long mics = micros();
  lcd.print(":");
  lcd.print(micros() - mics );
  
  if (counter % 27 == 0) {
    if (led == LOW) {
      buffer = buffer | B01000000;
      led = HIGH;
    }
    else {
      buffer = buffer & ~B01000000;
      led = LOW;
    }

    Wire.beginTransmission(0x20);
    Wire.send(buffer);
    Wire.endTransmission();
  }
}
