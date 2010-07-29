/*
  PCFCrystal Library - Blink
 
Demonstrates the use a 16x2 LCD display using the I2C capabilities of Arduino.
This library is a porting of the original LiquidCrystal library, prepared to
control the LCD display via one or two PCF8574.
The LiquidCrystal and PCFLiquidCrystal
libraries work with all LCD displays that are compatible with the
Hitachi HD44780 driver. There are many of them out there, and you
can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD and makes the 
 cursor block blink.
 
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
// initialize the library with the numbers of the interface pins
// rs, en, d0, d1, d2, d3, address, buffer
//PCFCrystal lcd(B00100000, B00010000, B00001000, B00000100, B00000010, B00000001, 0x20, &buffer);
PCFCrystal lcd(B00100000, B00010000, B00000001, B00000010, B00000100, B00001000, 0x20, &buffer);

void setup() {
  Wire.begin();
  // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // Turn off the blinking cursor:
  lcd.noBlink();
  delay(3000);
   // Turn on the blinking cursor:
  lcd.blink();
  delay(3000);
}


