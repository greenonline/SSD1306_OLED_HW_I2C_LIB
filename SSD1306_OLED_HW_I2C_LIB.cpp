/*
** SSD1306_OLED_HW_I2C_LIB — a minimalistic adaptation of Neven Boyanov’s SSD1306 library (http://tinusaur.org)
** Author: Ilya Perederiy
** Licence: open source (see LICENSE.txt for details)
** https://bitbucket.org/paraglider/ssd1306_oled_hw_i2c/
** Modified by Greenonline 2017

This library is designed to control a 128x64 OLED display with an SSD1306 controller over I2C. In essence, it is a minimalistic adaptation of a library written for ATTiny85 and similar micro-controllers. The purpose of this adaptation is to reduce the memory footprint, and add hardware support for I2C communication (supported on ATmega328P, ATmega32U4 and some other micro-controllers). The library can be used with Arduino IDE or in a plain C environment.

The following functions have been implemented in the library:
   - initialize display				D_INIT();
   - clear display					D_CLEAR();
   - turn off (sleep)					D_OFF();
   - turn on (wake up)					D_ON();
   - change brightness (same as contrast)		D_CONTRAST (0-255 or 0x00-0xFF);	
   - set position					D_SETPOS(x coordinate [0-127], character row [0-7]);	// (0,0) corresponds to the upper left corner, 
   - print string (8x6 ascii font)			D_PRINT_STR(“string”);
   - print variable(integers only)			D_PRINT_INT(integer or int variable);
   - draw horizontal line				D_DRAW_HOR(starting x coordinate [0-127], starting y coordinate [0-63], length);
   - draw vertical line				D_DRAW_VERT(starting x coordinate [0-127], starting y coordinate [0-63], length);
   - demonstration mode				D_DEMO();

Note: even though it is possible to specify the exact y coordinate in D_DRAW_HOR, 8 adjacent pixel rows will be rendered (but only one of these rows will light up). As a result any text that was printed in the same group of rows will be overwritten. For example, the following code will result in the line completely erasing the text because pixel rows 0-6 will be rendered dark:

D_SETPOS(0, 1);	
D_PRINT_STR(“some text”);
D_DRAW_HOR(0, 7, 128);


Below are credits from the original SSD1306 library:

  * Copyright (c) 2016 Neven Boyanov, Tinusaur Team. All Rights Reserved.
  * Distributed as open source software under MIT License, see LICENSE.txt file.
  * Please, as a favor, retain the link http://tinusaur.org to The Tinusaur Project.
  * Source code available at: https://bitbucket.org/tinusaur/ssd1306xled

  * NUM2STR - Function to handle the conversion of numeric vales to strings.
  * @created	2014-12-18
  * @author	Neven Boyanov
  * @version	2016-04-17 (last modified)
  * NOTE: This implementation is borrowed from the LCDDDD library.
  * Original source code at: https://bitbucket.org/boyanov/avr/src/default/lcdddd/src/lcdddd/lcdddd.h
*/

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "SSD1306_OLED_HW_I2C_LIB.h"

//  ASCII 6x8 font with leading zero bytes (character padding) removed
//  Each byte represents a column of 8 pixels
const uint8_t D_FONT6x8 [] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, // space 0
    0x00, 0x00, 0x2f, 0x00, 0x00, // ! 1
    0x00, 0x07, 0x00, 0x07, 0x00, // " 2
    0x14, 0x7f, 0x14, 0x7f, 0x14, // # 3
    0x24, 0x2a, 0x7f, 0x2a, 0x12, // $ 4
    0x62, 0x64, 0x08, 0x13, 0x23, // % 5
    0x36, 0x49, 0x55, 0x22, 0x50, // & 6
    0x00, 0x05, 0x03, 0x00, 0x00, // ' 7
    0x00, 0x1c, 0x22, 0x41, 0x00, // ( 8
    0x00, 0x41, 0x22, 0x1c, 0x00, // ) 9
    0x14, 0x08, 0x3E, 0x08, 0x14, // * 10
    0x08, 0x08, 0x3E, 0x08, 0x08, // + 11
    0x00, 0x00, 0xA0, 0x60, 0x00, // , 12
    0x08, 0x08, 0x08, 0x08, 0x08, // - 13
    0x00, 0x60, 0x60, 0x00, 0x00, // . 14
    0x20, 0x10, 0x08, 0x04, 0x02, // / 15
    0x3E, 0x51, 0x49, 0x45, 0x3E, // 0 16
    0x00, 0x42, 0x7F, 0x40, 0x00, // 1 17
    0x42, 0x61, 0x51, 0x49, 0x46, // 2 18
    0x21, 0x41, 0x45, 0x4B, 0x31, // 3 19
    0x18, 0x14, 0x12, 0x7F, 0x10, // 4 20
    0x27, 0x45, 0x45, 0x45, 0x39, // 5 21
    0x3C, 0x4A, 0x49, 0x49, 0x30, // 6 22
    0x01, 0x71, 0x09, 0x05, 0x03, // 7 23
    0x36, 0x49, 0x49, 0x49, 0x36, // 8 24
    0x06, 0x49, 0x49, 0x29, 0x1E, // 9 25
    0x00, 0x36, 0x36, 0x00, 0x00, // : 26
    0x00, 0x56, 0x36, 0x00, 0x00, // ; 27
    0x08, 0x14, 0x22, 0x41, 0x00, // < 28
    0x14, 0x14, 0x14, 0x14, 0x14, // = 29
    0x00, 0x41, 0x22, 0x14, 0x08, // > 30
    0x02, 0x01, 0x51, 0x09, 0x06, // ? 31
    0x32, 0x49, 0x59, 0x51, 0x3E, // @ 32
    0x7C, 0x12, 0x11, 0x12, 0x7C, // A 33
    0x7F, 0x49, 0x49, 0x49, 0x36, // B 34
    0x3E, 0x41, 0x41, 0x41, 0x22, // C 35
    0x7F, 0x41, 0x41, 0x22, 0x1C, // D 36
    0x7F, 0x49, 0x49, 0x49, 0x41, // E 37
    0x7F, 0x09, 0x09, 0x09, 0x01, // F 38
    0x3E, 0x41, 0x49, 0x49, 0x7A, // G 39
    0x7F, 0x08, 0x08, 0x08, 0x7F, // H 40
    0x00, 0x41, 0x7F, 0x41, 0x00, // I 41
    0x20, 0x40, 0x41, 0x3F, 0x01, // J 42
    0x7F, 0x08, 0x14, 0x22, 0x41, // K 43
    0x7F, 0x40, 0x40, 0x40, 0x40, // L 44
    0x7F, 0x02, 0x0C, 0x02, 0x7F, // M 45
    0x7F, 0x04, 0x08, 0x10, 0x7F, // N 46
    0x3E, 0x41, 0x41, 0x41, 0x3E, // O 47
    0x7F, 0x09, 0x09, 0x09, 0x06, // P 48
    0x3E, 0x41, 0x51, 0x21, 0x5E, // Q 49
    0x7F, 0x09, 0x19, 0x29, 0x46, // R 50
    0x46, 0x49, 0x49, 0x49, 0x31, // S 51
    0x01, 0x01, 0x7F, 0x01, 0x01, // T 52
    0x3F, 0x40, 0x40, 0x40, 0x3F, // U 53
    0x1F, 0x20, 0x40, 0x20, 0x1F, // V 54
    0x3F, 0x40, 0x38, 0x40, 0x3F, // W 55
    0x63, 0x14, 0x08, 0x14, 0x63, // X 56
    0x07, 0x08, 0x70, 0x08, 0x07, // Y 57
    0x61, 0x51, 0x49, 0x45, 0x43, // Z 58
    0x00, 0x7F, 0x41, 0x41, 0x00, // [ 59
    0x55, 0x2A, 0x55, 0x2A, 0x55, // 55 60
    0x00, 0x41, 0x41, 0x7F, 0x00, // ] 61
    0x04, 0x02, 0x01, 0x02, 0x04, // ^ 62
    0x40, 0x40, 0x40, 0x40, 0x40, // _ 63
    0x00, 0x01, 0x02, 0x04, 0x00, // ' 64
    0x20, 0x54, 0x54, 0x54, 0x78, // a 65
    0x7F, 0x48, 0x44, 0x44, 0x38, // b 66
    0x38, 0x44, 0x44, 0x44, 0x20, // c 67
    0x38, 0x44, 0x44, 0x48, 0x7F, // d 68
    0x38, 0x54, 0x54, 0x54, 0x18, // e 69
    0x08, 0x7E, 0x09, 0x01, 0x02, // f 70
    0x18, 0xA4, 0xA4, 0xA4, 0x7C, // g 71
    0x7F, 0x08, 0x04, 0x04, 0x78, // h 72
    0x00, 0x44, 0x7D, 0x40, 0x00, // i 73
    0x40, 0x80, 0x84, 0x7D, 0x00, // j 74
    0x7F, 0x10, 0x28, 0x44, 0x00, // k 75
    0x00, 0x41, 0x7F, 0x40, 0x00, // l 76
    0x7C, 0x04, 0x18, 0x04, 0x78, // m 77
    0x7C, 0x08, 0x04, 0x04, 0x78, // n 78
    0x38, 0x44, 0x44, 0x44, 0x38, // o 79
    0xFC, 0x24, 0x24, 0x24, 0x18, // p 80
    0x18, 0x24, 0x24, 0x18, 0xFC, // q 81
    0x7C, 0x08, 0x04, 0x04, 0x08, // r 82
    0x48, 0x54, 0x54, 0x54, 0x20, // s 83
    0x04, 0x3F, 0x44, 0x40, 0x20, // t 84
    0x3C, 0x40, 0x40, 0x20, 0x7C, // u 85
    0x1C, 0x20, 0x40, 0x20, 0x1C, // v 86
    0x3C, 0x40, 0x30, 0x40, 0x3C, // w 87
    0x44, 0x28, 0x10, 0x28, 0x44, // x 88
    0x1C, 0xA0, 0xA0, 0xA0, 0x7C, // y 89
    0x44, 0x64, 0x54, 0x4C, 0x44, // z 90
};


// Display initialization sequence
const uint8_t init_sequence [] PROGMEM = {
	0xAE,			// Display OFF (sleep mode)
	0x20, 0b00,		// Set Memory Addressing Mode
					// 00=Horizontal Addressing Mode; 01=Vertical Addressing Mode;
					// 10=Page Addressing Mode (RESET); 11=Invalid
	0xB0,			// Set Page Start Address for Page Addressing Mode, 0-7
	0xC8,			// Set COM Output Scan Direction
	0x00,			// ---set low column address
	0x10,			// ---set high column address
	0x40,			// ---set start line address
	0x81, 0x00,		// Set contrast control register
	0xA1,			// Set Segment Re-map. A0=address mapped; A1=address 127 mapped. 
	0xA6,			// Set display mode. A6=Normal; A7=Inverse
	0xA8, 0x3F,		// Set multiplex ratio(1 to 64)
	0xA4,			// Output RAM to Display
					// 0xA4=Output follows RAM content; 0xA5,Output ignores RAM content
	0xD3, 0x00,		// Set display offset. 00 = no offset
	0xD5,			// --set display clock divide ratio/oscillator frequency
	0xF0,			// --set divide ratio
	0xD9, 0x22,		// Set pre-charge period
	0xDA, 0x12,		// Set com pins hardware configuration		
	0xDB,			// --set vcomh
	0x20,			// 0x20,0.77xVcc
	0x8D, 0x14,		// Set DC-DC enable
	0xAF			// Display ON in normal mode
};


/*
// An alternative initialization sequence
const uint8_t init_sequence [] PROGMEM = {	// Initialization Sequence
    0xAE,			// Display OFF (sleep mode)
    0xA8, 0x3F,     // Set mux ratio tp select max number of rows - 64
    0xD3, 0x00,		// Set display offset. 00 = no offset
    0xA1,			// Set Segment Re-map. A0=address mapped; A1=address 127 mapped.
	0xC8,			// Set COM Output Scan Direction
    0xDA, 0x12,     // Default - alternate COM pin map
    0x81, 0x00,		// Set contrast control register
	0xA4,			// Set display to enable rendering from GDDRAM (Graphic Display Data RAM)
    0xA6,			// Set display mode. A6=Normal; A7=Inverse
	0xD5, 0x80,     // Default oscillator clock (alt 0xF0)
    0x8D, 0x14,     // Enable the charge pump
    0xD9, 0x22,		// Set pre-charge period
	0xDB, 0x30,     // Set the V_COMH deselect volatage to max (alt 0x20 for 0.77xVcc)
    0x20, 0b00,		// Set Memory Addressing Mode
                    // 00=Horizontal Addressing Mode; 01=Vertical Addressing Mode;
                    // 10=Page Addressing Mode (RESET); 11=Invalid
    0xAF			// Display ON in normal mode
};
*/

char ssd1306_numdec_buffer[USINT2DECASCII_MAX_DIGITS + 1];

//constructors

SSD1306_OLED_HW_I2C_LIB::SSD1306_OLED_HW_I2C_LIB(void)
{
  // SCL bit rate = CLK / (16 + 2*TWBR*[TWSR prescaler])
  TWSR = 0x00;    // I2C prescaler 1
  TWBR = 2;       // I2C divider 2
}


void SSD1306_OLED_HW_I2C_LIB::CLK_DIV_1(void) {          // Set clock divider to 1 (fast operation)
    cli();
    CLKPR = (1<<CLKPCE);
    CLKPR = 0x00;                          // div 1
    sei();
}

void SSD1306_OLED_HW_I2C_LIB::CLK_DIV_8(void) {          // Set clock divider to 8 (slow operation)
    cli();
    CLKPR = (1<<CLKPCE);
    CLKPR = (1<<CLKPS1)|(1<<CLKPS0);        // div 8
    sei();
}

uint8_t SSD1306_OLED_HW_I2C_LIB::usint2decascii(uint16_t num, char *buffer)      // convert integer to string
{
// @author	Neven Boyanov
// NOTE: This implementation is borrowed from the LCDDDD library.
// Original source code at: https://bitbucket.org/boyanov/avr/src/default/lcdddd/src/lcdddd/lcdddd.h

	const unsigned short powers[] = { 10000u, 1000u, 100u, 10u, 1u }; // The "const unsigned short" combination gives shortest code.
	char digit; // "digit" is stored in a char array, so it should be of type char.
	uint8_t digits = USINT2DECASCII_MAX_DIGITS - 1;
	for (uint8_t pos = 0; pos < 5; pos++) // "pos" is index in array, so should be of type int.
	{
		digit = 0;
		while (num >= powers[pos])
		{
			digit++;
			num -= powers[pos];
		}
		// ---- CHOOSE (1), (2) or (3) ----
		// CHOICE (1) Fixed width, zero padded result.
		/*
		//buffer[pos] = digit + '0';	// Convert to ASCII
		*/
		// CHOICE (2) Fixed width, zero padded result, digits offset.
		/*
		buffer[pos] = digit + '0';	// Convert to ASCII
		// Note: Determines the offset of the first significant digit.
		if (digits == -1 && digit != 0) digits = pos;
		// Note: Could be used for variable width, not padded, left aligned result.
		*/
		// CHOICE (3) Fixed width, space (or anything else) padded result, digits offset.
		// Note: Determines the offset of the first significant digit.
		// Note: Could be used for variable width, not padded, left aligned result.
		if (digits == USINT2DECASCII_MAX_DIGITS - 1)
		{
			if (digit == 0)
			{
				if (pos < USINT2DECASCII_MAX_DIGITS - 1)	// Check position, so single "0" will be handled properly.
					digit = -16;	// Use: "-16" for space (' '), "-3" for dash/minus ('-'), "0" for zero ('0'), etc. ...
			}
			else
			{
				digits = pos;
			}
		}
		buffer[pos] = digit + '0';	// Convert to ASCII
	}
	// NOTE: The resulting ascii text should not be terminated with '\0' here.
	//       The provided buffer maybe part of a larger text in both directions.
	return digits;
}


void SSD1306_OLED_HW_I2C_LIB::D_ERROR(void) {                            // I2C comm error handler. Blinks ERROR_PIN in PORTD
    for (uint8_t i = 0; i < 10; i++) {
        PORTD ^= 1 << ERROR_PIN;
        _delay_ms(300);
    }
}


void SSD1306_OLED_HW_I2C_LIB::D_START_CMD(void) {                        // Start I2C and tell the display to await commands
    cli();                                      // disable interrupts for the time being
    //CLK_DIV_1();                                // increase clock speed to max
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);     // START I2C
    while (!(TWCR&(1<<TWINT)));                 // wait
    if ((TWSR & 0xF8) != 0x08) D_ERROR();       // success or error


    TWDR = SLA_W;                               // slave address
    TWCR = (1<<TWINT) |(1<<TWEN);               // transmit
    while (!(TWCR & (1<<TWINT)));               // wait for transmission
    if ((TWSR & 0xF8) != 0x18) D_ERROR();       // success or error

    D_TX(0x00);                                 // prep command stream: C0=0 D/C#=0, followed by 6 zeros (datasheet 8.1.5.2)
}

void SSD1306_OLED_HW_I2C_LIB::D_START_DAT(void) {                        // Start I2C and tell the display to await data (pixels)
    cli();                                      // disable interrupts for the time being
    //CLK_DIV_1();                                // increase clock speed to max
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);     // START I2C
    while (!(TWCR&(1<<TWINT)));                 // wait
    if ((TWSR & 0xF8) != 0x08) D_ERROR();       // success or error

    TWDR = SLA_W;                               // slave address
    TWCR = (1<<TWINT) |(1<<TWEN);               // transmit
    while (!(TWCR & (1<<TWINT)));               // wait for transmission
    if ((TWSR & 0xF8) != 0x18) D_ERROR();       // success or error

    D_TX(0x40);                                 // prep for data stream: C0 = 0 D/C#=1, followed by 6 zeros (datasheet 8.1.5.2)
}

void SSD1306_OLED_HW_I2C_LIB::D_TX(uint8_t DATA) {                       // transmit 1 byte
    TWDR = DATA;                                // data to transmit
    TWCR = (1<<TWINT) |(1<<TWEN);               // transmit
    while (!(TWCR & (1<<TWINT)));               // wait for transmission
    if ((TWSR & 0xF8) != 0x28) D_ERROR();       // success or error
}

void SSD1306_OLED_HW_I2C_LIB::D_STOP (void) {                            // Stop I2C communication
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);     // stop
    //CLK_DIV_8();                                // decrease CLK speed
    sei();                                      // re-enable interrupts
}


// 

void SSD1306_OLED_HW_I2C_LIB::D_INIT(void) {                             // Initialize display
    D_START_CMD();
    for (uint8_t i = 0; i < sizeof (init_sequence); i++) {
        D_TX(pgm_read_byte(&init_sequence[i]));}            // read init sequence from progmem
    D_TX(OLED_CMD_SET_COLUMN_RANGE);
    D_TX(0x00);
    D_TX(0x7F);
    D_TX(OLED_CMD_SET_PAGE_RANGE);
    D_TX(0);
    D_TX(0x07);
    D_STOP();
}


void SSD1306_OLED_HW_I2C_LIB::D_SETPOS(uint8_t x, uint8_t y) {           // Set cursor position
    D_START_CMD();
	D_TX(0xB0 + y);
	D_TX(((x & 0xF0) >> 4) | 0x10);
    D_TX((x & 0x0f));
	D_STOP();
}

void SSD1306_OLED_HW_I2C_LIB::D_CLEAR(void) {                            // clear display
    D_SETPOS(0, 0);
    D_START_DAT();
    for (uint16_t i = 0; i < 128 * 8; i++) {
        D_TX(0);
    }
    D_STOP();

}

void SSD1306_OLED_HW_I2C_LIB::D_ON(void) {                               // turn on display (wake up)
    D_START_CMD();
    D_TX(0xAF);
    D_STOP();
}

void SSD1306_OLED_HW_I2C_LIB::D_OFF(void) {                              // turn off display (sleep)
    D_START_CMD();
    D_TX(0xAE);
    D_STOP();
}

void SSD1306_OLED_HW_I2C_LIB::D_CONTRAST (uint8_t contrast) {           // change contrast (brightness)
    D_START_CMD();
    D_TX(0x81);                                // Set contrast control register
    D_TX(contrast);                            // contrast 0-255
    D_STOP();
}

// Draw a horizontal line
// Note: even though the line is 1px thick, it will affect 8 pixel rows
void SSD1306_OLED_HW_I2C_LIB::D_DRAW_HOR(uint8_t xpos, uint8_t ypos, uint8_t length) {
    uint8_t ypage = ypos / 8;                       // determine page (8 vertical pixels) from pixel position
    uint8_t dot_byte = 1 << (ypos % 8);             // create a byte with a dot at the specified position within the page
    D_SETPOS(xpos, ypage);
    D_START_DAT();
    for (uint8_t i = 0; i < length; i++) {
        D_TX(dot_byte);
    }
	D_STOP();
}

// Draw a vertical line
void SSD1306_OLED_HW_I2C_LIB::D_DRAW_VERT(uint8_t xpos, uint8_t ypos, uint8_t length) {
    uint8_t ypage_start = ypos / 8;                         // determine starting page from pixel position
    uint8_t ypage_end = (ypos + length) / 8;                // determine last page from pixel position
    uint8_t ypages_span = ypage_end - ypage_start;          // how many pages does the line span?

    uint8_t dot_byte_start = 0xFF << (ypos % 8);            // create a byte with dots to represent first page (a column of 8 pixels)
    uint8_t dot_byte_end = 0XFF >> ((ypos+length) % 8);     // create a byte with dot to represent last page
    
    if (ypages_span == 0) {                                 // line is 8 pixels or shorter
        D_SETPOS(xpos, ypage_start);
        D_START_DAT();
        D_TX(dot_byte_start&dot_byte_end);
        D_STOP();
    }
    else {                                                  // line is >8 pixels long
        D_SETPOS(xpos, ypage_start);
        D_START_DAT();
        D_TX(dot_byte_start);                               // draw first 8 pixels (first page)
        D_STOP();
        
        if (ypages_span > 1) {                              // if the line >16 pixels long, draw the intermediate pages
            for (uint8_t i = ypage_start + 1; i < ypage_end; i++) {
                D_SETPOS(xpos, i);
                D_START_DAT();
                D_TX(0xFF);
                D_STOP();
            }
        }
        D_SETPOS(xpos, ypage_end);
        D_START_DAT();
        D_TX(dot_byte_end);                                 // draw the last 8 pixels (last page)
        D_STOP();
    }
}


void SSD1306_OLED_HW_I2C_LIB::D_PRINT_CHAR(char ch) {                                // print 1 character
	uint8_t c = ch - 32;
    D_START_DAT();
    D_TX(0x00);                                             // character leading 1 px space
	for (uint8_t i = 0; i < 5; i++)
    {
		D_TX(pgm_read_byte(&D_FONT6x8[c * 5 + i]));
	}
	D_STOP();
}

void SSD1306_OLED_HW_I2C_LIB::D_PRINT_STR(char *s) {                                 // print string (char array)
	while (*s) {
		D_PRINT_CHAR(*s++);
	}
}

void SSD1306_OLED_HW_I2C_LIB::D_PRINT_INT(uint16_t num) {                            // print integer variable
	ssd1306_numdec_buffer[USINT2DECASCII_MAX_DIGITS] = '\0';   // Terminate the string.
	uint8_t digits = usint2decascii(num, ssd1306_numdec_buffer);
	D_PRINT_STR(ssd1306_numdec_buffer + digits);
}

void SSD1306_OLED_HW_I2C_LIB::D_DEMO(void) {                                         // display demonstration 
        D_CLEAR();                                          // clear display
        D_DRAW_HOR(0, 0, 127);                              // top horiz line (start x, start y, length)
        D_DRAW_HOR(0, 63, 127);                             // bottom horiz line (start x, start y, length)
        D_DRAW_VERT(0, 0, 64);                              // left vert line (start x, start y, length)
        D_DRAW_VERT(127, 0, 64);                            // right vert line (start x, start y, length)
        D_SETPOS(25,1);                                     // set cursor position
        D_PRINT_STR("DEMONSTRATION");                       // print message
        D_SETPOS(6,3);
        D_PRINT_STR("The display will be");
        D_SETPOS(34,4);
        D_PRINT_STR("turned off");
        D_SETPOS(30,5);
        D_PRINT_STR("temporarily");
        _delay_ms(2000);
        D_OFF();                                            // turn off display (conserve power)
        _delay_ms(500);
        D_CLEAR();
        D_ON();                                             // turn on display
        _delay_ms(500);

        D_SETPOS(2,3);
        D_PRINT_STR("   Counter = ");
        for (uint16_t i = 800; i>0; i--) {
            D_SETPOS(2+13*6,3);
            D_PRINT_INT(i);                                 // print counter variable
        }
    
        D_CLEAR();
        D_SETPOS(18,4);
        D_PRINT_STR("LOWEST CONTRAST");
        _delay_ms(1000);
        D_CONTRAST(0xFF);                                   // change contrast (0-255 or 0x00-0xFF)
        D_SETPOS(14,4);
        D_PRINT_STR("HIGHEST CONTRAST");
        _delay_ms(1000);
        D_CONTRAST(0x00);
}


