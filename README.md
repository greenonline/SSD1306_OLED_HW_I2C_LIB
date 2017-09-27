# SSD1306_OLED_HW_I2C_LIB
A full Arduino library of [SSD1306_OLED_HW_I2C](https://bitbucket.org/paraglider/ssd1306_oled_hw_i2c/). The original [SSD1306_OLED_HW_I2C](https://bitbucket.org/paraglider/ssd1306_oled_hw_i2c/) was not a class. 

See [New minimalistic library for 128x64 I2C OLED displays](https://www.reddit.com/r/arduino/comments/63ic5y/new_minimalistic_library_for_128x64_i2c_oled/)

> I came across a simple OLED library made by Neven Boyanov (http://tinusaur.org) a couple of weeks ago. The library was written for ATtiny85, but probably could run on other microcontrollers with minor adaptations since it uses bitbanging for I2C comms. I decided to port the library to ATmega328P and ATmega32U4 which support hardware I2C. In addition, I wanted to reduce the memory footprint by replacing some functions. I thought I'd share the result here in case anyone wants to test this minimalistic library:
> 
> https://bitbucket.org/paraglider/ssd1306_oled_hw_i2c/
> 
> Q: What is this library good for? A: Printing text and integer variables, drawing horizontal and vertical lines — all while taking a couple of kilobytes of PROGMEM and next to zero RAM.
> 
> Q: What is this library not good for? A: Anything complex. You can't display bitmaps, you can't draw skewed lines, you can't control pixel rows (although it is possible to control groups of 8 pixel rows). If you need those functions, and you can afford using lots of RAM and PROGMEM, check out U8G2.
> 
> I'll monitor this thread and answer questions in case anyone wants to try the library.

