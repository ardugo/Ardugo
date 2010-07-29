#include "PCFCrystal.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "WProgram.h"


#include "../Wire/Wire.h"

// When the display powers up, it is configured as follows:
//
// 1. Display clear
// 2. Function set: 
//    DL = 1; 8-bit interface data 
//    N = 0; 1-line display 
//    F = 0; 5x8 dot character font 
// 3. Display on/off control: 
//    D = 0; Display off 
//    C = 0; Cursor off 
//    B = 0; Blinking off 
// 4. Entry mode set: 
//    I/D = 1; Increment by 1 
//    S = 0; No shift 
//
// Note, however, that resetting the Arduino doesn't reset the LCD, so we
// can't assume that its in that state when a sketch starts (and the
// PCFCrystal constructor is called).

PCFCrystal::PCFCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
			     uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
			     uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, 
		             uint8_t address, uint8_t addressextra, uint8_t *buffer, uint8_t *bufferextra)
{
  init(0, rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7, address, addressextra, buffer, bufferextra);
}

PCFCrystal::PCFCrystal(uint8_t rs, uint8_t enable,
			     uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
			     uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
		             uint8_t address, uint8_t addressextra, uint8_t *buffer, uint8_t *bufferextra)
{
  init(0, rs, 0, enable, d0, d1, d2, d3, d4, d5, d6, d7, address, addressextra, buffer, bufferextra);
}

PCFCrystal::PCFCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
			     uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, 
			     uint8_t address, uint8_t *buffer)
{
  init(1, rs, rw, enable, d0, d1, d2, d3, 0, 0, 0, 0, address, 0, buffer, 0);
}

PCFCrystal::PCFCrystal(uint8_t rs,  uint8_t enable,
			     uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, 
			     uint8_t address, uint8_t *buffer)
{
  init(1, rs, 0, enable, d0, d1, d2, d3, 0, 0, 0, 0, address, 0, buffer, 0);
}

void PCFCrystal::init(uint8_t fourbitmode, uint8_t rs, uint8_t rw, uint8_t enable,
			 uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
			 uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, 
	                 uint8_t address, uint8_t addressextra, uint8_t *buffer, uint8_t *bufferextra)
{
  _rs_pin = rs;
  _rw_pin = rw;
  _enable_pin = enable;
  
  _data_pins[0] = d0;
  _data_pins[1] = d1;
  _data_pins[2] = d2;
  _data_pins[3] = d3; 
  _data_pins[4] = d4;
  _data_pins[5] = d5;
  _data_pins[6] = d6;
  _data_pins[7] = d7; 

  _data = buffer;
  _dataextra = bufferextra;
  _address = address;
  _addressextra = addressextra;

/*
  // ORIGINAL CODE
  pinMode(_rs_pin, OUTPUT);
  // we can save 1 pin by not using RW. Indicate by passing -1 instead of pin#
  if (_rw_pin != -1) { 
    pinMode(_rw_pin, OUTPUT);
  }
  pinMode(_enable_pin, OUTPUT);
*/  

  if (fourbitmode)
    _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
  else 
    _displayfunction = LCD_8BITMODE | LCD_1LINE | LCD_5x8DOTS;
  
// Can't initialize the display because Wire may have not been initialized yet 
// begin(16, 1);  
}

void PCFCrystal::begin(uint8_t cols, uint8_t lines, uint8_t dotsize) {
  if (lines > 1) {
    _displayfunction |= LCD_2LINE;
  }
  _numlines = lines;
  _currline = 0;

  // for some 1 line displays you can select a 10 pixel high font
  if ((dotsize != 0) && (lines == 1)) {
    _displayfunction |= LCD_5x10DOTS;
  }

  // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
  // according to datasheet, we need at least 40ms after power rises above 2.7V
  // before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
  delayMicroseconds(50000); 
  // Now we pull both RS and R/W low to begin commands
/*
  // ORIGINAL CODE
  digitalWrite(_rs_pin, LOW);
  digitalWrite(_enable_pin, LOW);
  if (_rw_pin != -1) { 
    digitalWrite(_rw_pin, LOW);
  }
*/

  uint8_t *buff = modeBuffer();
  setBit(buff, _rs_pin, LOW);
  setBit(buff, _enable_pin, LOW);
  if (_rw_pin)
    setBit(buff, _rw_pin, LOW);
  writePCF(modeAddress(), *buff);
  
  //put the LCD into 4 bit or 8 bit mode
  if (! (_displayfunction & LCD_8BITMODE)) {
    // this is according to the hitachi HD44780 datasheet
    // figure 24, pg 46

    // we start in 8bit mode, try to set 4 bit mode
    write4bits(0x03);
    delayMicroseconds(4500); // wait min 4.1ms

    // second try
    write4bits(0x03);
    delayMicroseconds(4500); // wait min 4.1ms
    
    // third go!
    write4bits(0x03); 
    delayMicroseconds(150);

    // finally, set to 8-bit interface
    write4bits(0x02); 
  } else {
    // this is according to the hitachi HD44780 datasheet
    // page 45 figure 23

    // Send function set command sequence
    command(LCD_FUNCTIONSET | _displayfunction);
    delayMicroseconds(4500);  // wait more than 4.1ms

    // second try
    command(LCD_FUNCTIONSET | _displayfunction);
    delayMicroseconds(150);

    // third go
    command(LCD_FUNCTIONSET | _displayfunction);
  }

  // finally, set # lines, font size, etc.
  command(LCD_FUNCTIONSET | _displayfunction);  

  // turn the display on with no cursor or blinking default
  _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;  
  display();

  // clear it off
  clear();

  // Initialize to default text direction (for romance languages)
  _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
  // set the entry mode
  command(LCD_ENTRYMODESET | _displaymode);

}

/********** high level commands, for the user! */
void PCFCrystal::clear()
{
  command(LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
  delayMicroseconds(2000);  // this command takes a long time!
}

void PCFCrystal::home()
{
  command(LCD_RETURNHOME);  // set cursor position to zero
  delayMicroseconds(2000);  // this command takes a long time!
}

void PCFCrystal::setCursor(uint8_t col, uint8_t row)
{
  int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
  if ( row > _numlines ) {
    row = _numlines-1;    // we count rows starting w/0
  }
  
  command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

// Turn the display on/off (quickly)
void PCFCrystal::noDisplay() {
  _displaycontrol &= ~LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void PCFCrystal::display() {
  _displaycontrol |= LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void PCFCrystal::noCursor() {
  _displaycontrol &= ~LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void PCFCrystal::cursor() {
  _displaycontrol |= LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor
void PCFCrystal::noBlink() {
  _displaycontrol &= ~LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void PCFCrystal::blink() {
  _displaycontrol |= LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
void PCFCrystal::scrollDisplayLeft(void) {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void PCFCrystal::scrollDisplayRight(void) {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void PCFCrystal::leftToRight(void) {
  _displaymode |= LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void PCFCrystal::rightToLeft(void) {
  _displaymode &= ~LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor
void PCFCrystal::autoscroll(void) {
  _displaymode |= LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
void PCFCrystal::noAutoscroll(void) {
  _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void PCFCrystal::createChar(uint8_t location, uint8_t charmap[]) {
  location &= 0x7; // we only have 8 locations 0-7
  command(LCD_SETCGRAMADDR | (location << 3));
  for (int i=0; i<8; i++) {
    write(charmap[i]);
  }
}

/*********** mid level commands, for sending data/cmds */

inline void PCFCrystal::command(uint8_t value) {
  send(value, LOW);
}

inline void PCFCrystal::write(uint8_t value) {
  send(value, HIGH);
}

/************ low level data pushing commands **********/

// write either command or data, with automatic 4/8-bit selection
void PCFCrystal::send(uint8_t value, uint8_t mode) {
/*  
  // ORIGINAL CODE
  digitalWrite(_rs_pin, mode);

  // if there is a RW pin indicated, set it low to Write
  if (_rw_pin != -1) { 
    digitalWrite(_rw_pin, LOW);
  }
*/

  setBit(modeBuffer(), _rs_pin, mode);
  // if there is a RW pin indicated, set it low to Write
  if (_rw_pin) { 
    setBit(modeBuffer(), _rw_pin, LOW);
  }
  writePCF(modeAddress(), *modeBuffer());
//return;

  if (_displayfunction & LCD_8BITMODE) {
    write8bits(value); 
  } else {
    write4bits(value>>4);
    write4bits(value);
  }
}

void PCFCrystal::pulseEnable(void) {
  // Set the value if it's in a separate PCF
  if (_addressextra)
    writePCF(_address, *_data);

/*
  // ORIGINAL CODE
  digitalWrite(_enable_pin, LOW);
  delayMicroseconds(1);    
  digitalWrite(_enable_pin, HIGH);
  delayMicroseconds(1);    // enable pulse must be >450ns
  digitalWrite(_enable_pin, LOW);
  delayMicroseconds(100);   // commands need > 37us to settle
*/
  uint8_t *buff = modeBuffer();
  uint8_t address = modeAddress();
  
  setBit(buff, _enable_pin, LOW);
  writePCF(address, *buff);
// ORIGINAL CODE. These 3 delays are omitted as the PCF writing takes longer
//  delayMicroseconds(1);
  
  setBit(buff, _enable_pin, HIGH);
  writePCF(address, *buff);
//  delayMicroseconds(1);    // enable pulse must be >450ns
  
  setBit(buff, _enable_pin, LOW);
  writePCF(address, *buff);
//  delayMicroseconds(100);   // commands need > 37us to settle
}

void PCFCrystal::write4bits(uint8_t value) {
  for (int i = 0; i < 4; i++) {
/*
  // ORIGINAL CODE
    pinMode(_data_pins[i], OUTPUT);
    digitalWrite(_data_pins[i], (value >> i) & 0x01);
*/
    setBit(_data, _data_pins[i], (value >> i) & 0x01);    
  }

  pulseEnable();
}

void PCFCrystal::write8bits(uint8_t value) {
  for (int i = 0; i < 8; i++) {
/*
  // ORIGINAL CODE
    pinMode(_data_pins[i], OUTPUT);
    digitalWrite(_data_pins[i], (value >> i) & 0x01);
*/
    setBit(_data, _data_pins[i], (value >> i) & 0x01);    
  }
  
  pulseEnable();
}

/************ New functions **********/
void PCFCrystal::setBit(uint8_t *buff, uint8_t mask, uint8_t value)
{
  if (value)
    (*buff) = (*buff) | mask;
  else
    (*buff) = (*buff) & (~mask);
}

void PCFCrystal::writePCF(uint8_t address, uint8_t value)
{
  Wire.beginTransmission(address);
  Wire.send(value);
  Wire.endTransmission();
  
}


