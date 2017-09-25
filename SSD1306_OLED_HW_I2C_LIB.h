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




#ifndef SSD1306_OLED_HW_I2C_LIB_h
#define SSD1306_OLED_HW_I2C_LIB_h

#define OLED_CMD_SET_COLUMN_RANGE       0x21        // can be used only in HORZ/VERT mode - follow with 0x00 and 0x7F = COL127
#define OLED_CMD_SET_PAGE_RANGE         0x22        // can be used only in HORZ/VERT mode - follow with 0x00 and 0x07 = PAGE7

#define SLA_W                           0x78        // slave address + 0
#define ERROR_PIN                       4           // LED pin to indicate I2C error (2-7)

#define USINT2DECASCII_MAX_DIGITS 5


#include <stdint.h>


class SSD1306_OLED_HW_I2C_LIB {

  public: 

    SSD1306_OLED_HW_I2C_LIB(void);

    void D_INIT(void);
    void D_SETPOS(uint8_t x, uint8_t y);
    void D_CLEAR(void);
    void D_CONTRAST (uint8_t contrast);
    void D_ON(void);
    void D_OFF(void);
    void D_PRINT_CHAR(char ch);
    void D_PRINT_STR(char *s);
    void D_PRINT_INT(uint16_t num);
    void D_DRAW_HOR(uint8_t xpos, uint8_t ypos, uint8_t length);
    void D_DRAW_VERT(uint8_t xpos, uint8_t ypos, uint8_t length);

    void D_DEMO(void);

  private:

    void CLK_DIV_1(void);
    void CLK_DIV_8(void);
    uint8_t usint2decascii(uint16_t, char *);

    void D_ERROR(void);
    void D_START_CMD(void);
    void D_START_DAT(void);
    void D_TX(uint8_t DATA);
    void D_STOP (void);
};

#endif
