// SSD1306_OLED_HW_I2C_LIB.ino
// Demo sketch - uses built in demonstration function, D_DEMO()
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
  lcd.D_DEMO();         // Demo mode
}
