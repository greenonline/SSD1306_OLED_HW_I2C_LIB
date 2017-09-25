// SSD1306_OLED_HW_I2C_LIB_Tests.ino
// Test sketch
//
// connect display SCL to pin A5, and SDA to pin A4
// connect LED to pin 4 (it will blink in case of I2C error)

#include <SSD1306_OLED_HW_I2C_LIB.h>
#include <avr/io.h>

SSD1306_OLED_HW_I2C_LIB lcd = SSD1306_OLED_HW_I2C_LIB();

void setup(void) {
  lcd.DINIT();
}


void loop(void) {

// Draws lines every 8 pixels
//  DrawScreenOfLines(); 

// Draw one line across middle of screen
  DrawLine();         // Demo mode
        

// Prints nothing
//  DrawFourLines1px();         

// Prints only one line
//  DrawThreeLines1pxOddNumber();         

// Prints multiple moving lines spaced by 1 px
//  DrawFourLines1pxNoDelay();         

// Prints only one line
//  DrawFourLines2px();         

// Prints multiple moving lines spaced by 2 px
//  DrawFourLines2pxNoDelay();   

// Prints one line
//  DrawOneLineAt0();

// Does not print any line
//  DrawOneLineAt1();

// Prints one line
//  DrawOneLineAt2();

// Does not print any line
//  DrawOneLineAt3();

// Prints three lines with alternating lower line
//  DrawTwoSetsOfLines();
  
// Slowly draws 8 lines
//  DrawScreenOfLines8pxSeries();
  
// Slowly draws 8 lines with, in theory, a 1px offset - but prints nothing
//  DrawScreenOfLines8pxSeries1pxOffset();

// Slowly draws 8 lines with a 2px offset
//  DrawScreenOfLines8pxSeries2pxOffset();

// Slowly draws 8 lines with, in theory, a 3px offset - but prints nothing
//  DrawScreenOfLines8pxSeries3pxOffset();

// Slowly draws 8 lines with, in theory, a 0px and then 2px offset - works well
//  DrawScreenOfLines8pxSeries0pxAnd2pxOffset();

// First function prints lines, second clears it :-(
//  DrawScreenOfLines8px();
//  DrawScreenOfLines8px1pxOffset();

}

const int heightLCD = 64;


void DrawOneLineAt0(void) {                                         // display lines 
        lcd.D_CLEAR();                                          // clear display
        lcd.D_DRAW_HOR(0, 0, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        _delay_ms(2000);
}

void DrawOneLineAt1(void) {                                         // display lines 
        lcd.D_CLEAR();                                          // clear display
        lcd.D_DRAW_HOR(0, 1, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        _delay_ms(2000);
}

void DrawOneLineAt2(void) {                                         // display lines 
        lcd.D_CLEAR();                                          // clear display
        lcd.D_DRAW_HOR(0, 2, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        _delay_ms(2000);
}

void DrawOneLineAt3(void) {                                         // display lines 
        lcd.D_CLEAR();                                          // clear display
        lcd.D_DRAW_HOR(0, 3, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        _delay_ms(2000);
}

void DrawFourLines1px(void) {                                         // display lines 
        lcd.D_CLEAR();                                          // clear display
        lcd.D_DRAW_HOR(0, 0, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 1, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 2, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 3, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        _delay_ms(2000);
}

void DrawThreeLines1pxOddNumber(void) {                                         // display lines 
        lcd.D_CLEAR();                                          // clear display
        lcd.D_DRAW_HOR(0, 0, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 1, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 2, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
//        lcd.D_DRAW_HOR(0, 3, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        _delay_ms(2000);
}

void DrawFourLines1pxNoDelay(void) {                                         // display lines 
        lcd.D_CLEAR();                                          // clear display
        lcd.D_DRAW_HOR(0, 0, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 1, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 2, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 3, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
//        _delay_ms(2000);
}

void DrawFourLines2px(void) {                                         // display lines 
        lcd.D_CLEAR();                                          // clear display
        lcd.D_DRAW_HOR(0, 0, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 2, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 4, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 6, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        _delay_ms(2000);
}

void DrawFourLines2pxNoDelay(void) {                                         // display lines 
        lcd.D_CLEAR();                                          // clear display
        lcd.D_DRAW_HOR(0, 0, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 2, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 4, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 6, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
//        _delay_ms(2000);
}

void DrawScreenOfLines8px(void) {                                         // display lines 
        lcd.D_CLEAR();                                          // clear display
        lcd.D_DRAW_HOR(0, 0, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 8, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 16, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 24, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 32, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 40, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 48, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 56, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 64, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        _delay_ms(2000);
}

void DrawScreenOfLines8px1pxOffset(void) {                                         // display lines 
        lcd.D_CLEAR();                                          // clear display
        lcd.D_DRAW_HOR(0, 1, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 9, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 17, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 25, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 33, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 41, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 49, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 57, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 65, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        _delay_ms(2000);
}

void DrawScreenOfLines8pxSeries(void) {                                         // display lines 
  lcd.D_CLEAR();                                          // clear display
// 1
  lcd.D_DRAW_HOR(0, 0, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 2
  lcd.D_DRAW_HOR(0, 8, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 3
  lcd.D_DRAW_HOR(0, 16, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 4
  lcd.D_DRAW_HOR(0, 24, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 5
  lcd.D_DRAW_HOR(0, 32, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 6
  lcd.D_DRAW_HOR(0, 40, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 7
  lcd.D_DRAW_HOR(0, 48, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 8
  lcd.D_DRAW_HOR(0, 56, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 9
  lcd.D_DRAW_HOR(0, 64, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
}

void DrawScreenOfLines8pxSeries1pxOffset(void) {                                         // display lines 
  lcd.D_CLEAR();                                          // clear display
// 1
  lcd.D_DRAW_HOR(0, 1, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 2
  lcd.D_DRAW_HOR(0, 9, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 3
  lcd.D_DRAW_HOR(0, 17, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 4
  lcd.D_DRAW_HOR(0, 25, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 5
  lcd.D_DRAW_HOR(0, 33, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 6
  lcd.D_DRAW_HOR(0, 41, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 7
  lcd.D_DRAW_HOR(0, 49, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 8
  lcd.D_DRAW_HOR(0, 57, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 9
  lcd.D_DRAW_HOR(0, 65, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
}

void DrawScreenOfLines8pxSeries2pxOffset(void) {                                         // display lines 
  lcd.D_CLEAR();                                          // clear display
// 1
  lcd.D_DRAW_HOR(0, 2, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 2
  lcd.D_DRAW_HOR(0, 10, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 3
  lcd.D_DRAW_HOR(0, 18, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 4
  lcd.D_DRAW_HOR(0, 26, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 5
  lcd.D_DRAW_HOR(0, 34, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 6
  lcd.D_DRAW_HOR(0, 42, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 7
  lcd.D_DRAW_HOR(0, 50, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 8
  lcd.D_DRAW_HOR(0, 58, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 9
  lcd.D_DRAW_HOR(0, 66, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
}

void DrawScreenOfLines8pxSeries3pxOffset(void) {                                         // display lines 
  lcd.D_CLEAR();                                          // clear display
// 1
  lcd.D_DRAW_HOR(0, 3, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 2
  lcd.D_DRAW_HOR(0, 11, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 3
  lcd.D_DRAW_HOR(0, 19, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 4
  lcd.D_DRAW_HOR(0, 27, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 5
  lcd.D_DRAW_HOR(0, 35, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 6
  lcd.D_DRAW_HOR(0, 43, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 7
  lcd.D_DRAW_HOR(0, 51, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 8
  lcd.D_DRAW_HOR(0, 59, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 9
  lcd.D_DRAW_HOR(0, 67, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
}

void DrawScreenOfLines8pxSeries0pxAnd2pxOffset(void) {                                         // display lines 
  lcd.D_CLEAR();                                          // clear display
// 1
  lcd.D_DRAW_HOR(0, 0, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 2
  lcd.D_DRAW_HOR(0, 8, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 3
  lcd.D_DRAW_HOR(0, 16, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 4
  lcd.D_DRAW_HOR(0, 24, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 5
  lcd.D_DRAW_HOR(0, 32, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 6
  lcd.D_DRAW_HOR(0, 40, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 7
  lcd.D_DRAW_HOR(0, 48, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 8
  lcd.D_DRAW_HOR(0, 56, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 9
  lcd.D_DRAW_HOR(0, 64, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 1
  lcd.D_DRAW_HOR(0, 2, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 2
  lcd.D_DRAW_HOR(0, 10, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 3
  lcd.D_DRAW_HOR(0, 18, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 4
  lcd.D_DRAW_HOR(0, 26, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 5
  lcd.D_DRAW_HOR(0, 34, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 6
  lcd.D_DRAW_HOR(0, 42, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 7
  lcd.D_DRAW_HOR(0, 50, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 8
  lcd.D_DRAW_HOR(0, 58, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
// 9
  lcd.D_DRAW_HOR(0, 66, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
  _delay_ms(2000);
}


void DrawScreenOfLines(void) {                                         // display lines 
        lcd.D_CLEAR();                                          // clear display
        lcd.D_DRAW_HOR(0, 0, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 8, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 16, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 24, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 32, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 40, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 48, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 56, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 64, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
       _delay_ms(2000);
}

void DrawScreenOfLinesTest(void) {                                         // display lines 
        lcd.D_CLEAR();                                          // clear display
        lcd.D_DRAW_HOR(0, 0, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 8, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 16, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 24, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 32, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 40, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 48, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 56, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 64, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
       _delay_ms(2000);
        lcd.D_DRAW_HOR(0, 63, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 63, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
       _delay_ms(2000);
}

void DrawLine(void) {                                         // display lines 
        lcd.D_CLEAR();                                          // clear display
        lcd.D_DRAW_HOR(0, 16, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
       _delay_ms(2000);
}

// Printing at y=64, moves the line at y=30
void DrawTwoSetsOfLines(void) {                                         // display lines 
        lcd.D_CLEAR();                                          // clear display
        lcd.D_DRAW_HOR(0, 0, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 8, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 30, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 63, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
       _delay_ms(2000);
        lcd.D_CLEAR();                                          // clear display
        lcd.D_DRAW_HOR(0, 0, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 8, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 30, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
        lcd.D_DRAW_HOR(0, 64, 127);                              // top horiz line (start x, start y, length) - this doesn't print top line
       _delay_ms(2000);
}

