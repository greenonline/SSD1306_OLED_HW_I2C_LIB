// SSD1306_OLED_HW_I2C_LIB_Demo.ino
// Demo sketch
//
// connect display SCL to pin A5, and SDA to pin A4
// connect LED to pin 4 (it will blink in case of I2C error)

#include <SSD1306_OLED_HW_I2C_LIB.h>
#include <avr/io.h>

SSD1306_OLED_HW_I2C_LIB lcd = SSD1306_OLED_HW_I2C_LIB();


void setup(void) {
   lcd.D_INIT();       // Initialize OLED
}


void loop(void) {
  DemoScreen();         // Demo mode
}

const int heightLCD = 64;


void DemoScreen(void) {                                         // display demonstration 
       lcd.D_CLEAR();                                          // clear display
       lcd.D_DRAW_HOR(0, 0, 127);                              // top horiz line (start x, start y, length)
//       lcd.D_DRAW_HOR(0, 1, 127);                              // top horiz line (start x, start y, length) - this prints top line
       lcd.D_DRAW_HOR(0, heightLCD-1, 127);                             // bottom horiz line (start x, start y, length)
//       lcd.D_DRAW_HOR(0, heightLCD, 127);                             // bottom horiz line (start x, start y, length)
       lcd.D_DRAW_VERT(0, 0, heightLCD);                              // left vert line (start x, start y, length)
       lcd.D_DRAW_VERT(127, 0, heightLCD);                            // right vert line (start x, start y, length)
       lcd.D_SETPOS(25,1);                                     // set cursor position
       lcd.D_PRINT_STR("DEMONSTRATION");                       // print message
       lcd.D_SETPOS(6,3);
       lcd.D_PRINT_STR("The display will be");
       lcd.D_SETPOS(34,4);
       lcd.D_PRINT_STR("turned off");
       lcd.D_SETPOS(30,5);
       lcd.D_PRINT_STR("temporarily");
        _delay_ms(2000);
       lcd.D_OFF();                                            // turn off display (conserve power)
        _delay_ms(500);
       lcd.D_CLEAR();
       lcd.D_ON();                                             // turn on display
        _delay_ms(500);

       lcd.D_SETPOS(2,3);
       lcd.D_PRINT_STR("   Counter = ");
        for (uint16_t i = 800; i>0; i--) {
           lcd.D_SETPOS(2+13*6,3);
           lcd.D_PRINT_INT(i);                                 // print counter variable
        }
    
       lcd.D_CLEAR();
       lcd.D_SETPOS(18,4);
       lcd.D_PRINT_STR("LOWEST CONTRAST");
        _delay_ms(1000);
       lcd.D_CONTRAST(0xFF);                                   // change contrast (0-255 or 0x00-0xFF)
       lcd.D_SETPOS(14,4);
       lcd.D_PRINT_STR("HIGHEST CONTRAST");
        _delay_ms(1000);
       lcd.D_CONTRAST(0x00);
}

