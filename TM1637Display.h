//  Author: avishorp@gmail.com
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#ifndef __TM1637__
#define __TM1637__

#include <inttypes.h>

//define commands
#define TM1637_I2C_COMM1    0x40
#define TM1637_I2C_COMM2    0xC0
#define TM1637_I2C_COMM3    0x80

//define segments
//
//      A
//     ---
//  F |   | B
//     -G-
//  E |   | C
//     ---
//      D
//
#define SEG_A   0b00000001
#define SEG_B   0b00000010
#define SEG_C   0b00000100
#define SEG_D   0b00001000
#define SEG_E   0b00010000
#define SEG_F   0b00100000
#define SEG_G   0b01000000

// Defines position of Colon (0 lowest 3 highest)
#define COLON_POSITION 1

//define brightness level
#define  BRIGHT_OFF      0
#define  BRIGHT_LOW      8
#define  BRIGHT_MID     10
#define  BRIGHT_HIGH    15

//digit to segment
const uint8_t digitToSegment[] = {
 // XGFEDCBA
  0b00111111,    // 0
  0b00000110,    // 1
  0b01011011,    // 2
  0b01001111,    // 3
  0b01100110,    // 4
  0b01101101,    // 5
  0b01111101,    // 6
  0b00000111,    // 7
  0b01111111,    // 8
  0b01101111,    // 9
  0b01110111,    // A
  0b01111100,    // B
  0b00111001,    // C
  0b01011110,    // D
  0b01111001,    // E
  0b01110001     // F
  };
  
  
class TM1637 {
 
public:

  TM1637(uint8_t pinClk, uint8_t pinDIO);
  // Initialize a TM1637Display object, setting the clock and data pins.
  // PARAMETERS
  //  pinClk - The number of the digital pin connected to the clock pin of the module.
  //  pinDIO - The number of the digital pin connected to the DIO pin of the module. 
  
  
  void setBrightness(uint8_t brightness); 
  // Sets the brightness of the display.
  // The setting takes effect when a command is given to change the data being displayed.
  // PARAMETERS
  //  brightness A number from 0 (lowes brightness) to 7 (highest brightness)


  void setSegments(const uint8_t segments[], uint8_t length = 4, uint8_t pos = 0);
  // Display arbitrary data on the module
  // This function receives raw segment values as input and displays them. The segment data
  // is given as a byte array, each byte corresponding to a single digit. Within each byte,
  // bit 0 is segment A, bit 1 is segment B etc.
  // The function may either set the entire display or any desirable part on its own. The first
  // digit is given by the @ref pos argument with 0 being the leftmost digit. The @ref length
  // argument is the number of digits to be set. Other digits are not affected.
  // PARAMETERS  
  //  segments An array of size @ref length containing the raw segment values
  //  length The number of digits to be modified
  //  pos The position from which to start the modification (0 - leftmost, 3 - rightmost)


  void setColon(const bool colon);  
  // Sets the colon indicator mode on or off
  // PARAMETERS
  //  colon When true, lights up the colon on next use of showNumberDec


  void showNumberDec(int num, bool leading_zero = false, uint8_t length = 4, uint8_t pos = 0);
  // Displayes a decimal number
  // Dispalyes the given argument as a decimal number
  // PARAMETERS
  //  num The number to be shown
  //  leading_zero When true, leading zeros are displayed. Otherwise unnecessary digits are blank
  //  length The number of digits to set. The user must ensure that the number to be shown
  //         fits to the number of digits requested (for example, if two digits are to be displayed,
  //         the number must be between 0 to 99)
  //  pos The position least significant digit (0 - leftmost, 3 - rightmost)

  
  uint8_t encodeDigit(uint8_t digit);  
  // Translate a single digit into 7 segment code
  // The method accepts a number between 0 - 15 and converts it to the
  // code required to display the number on a 7 segment display.
  // Numbers between 10-15 are converted to hexadecimal digits (A-F)
  // PARAMETERS
  //  digit A number between 0 to 15
  // RETURN
  //   A code representing the 7 segment image of the digit (LSB - segment A;
  //   bit 6 - segment G; bit 7 - always zero)
  
  void clear(void);
  // Clear display.


protected:
   void bitDelay();
   void start();
   void stop();
   bool writeByte(uint8_t b);
   
private:
  uint8_t m_pinClk;
  uint8_t m_pinDIO;
  uint8_t m_brightness;
    
  bool m_colon;
  //indicates if the colon element should be on
};

#endif // __TM1637__
