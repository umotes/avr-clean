

/*===========================================================================
Author:   Elegantcircuits.com
File:     $Id: ssd1306_control_panel
Software: AVR-GCC 3.3
Hardware: Atmega328P AVR 
Description:
    This example shows how to create an OLED based control panel based on user input
HW Description:
*****************************************************************************/
#include <avr/io.h>
#include <avr/delay.h>
#include <stdlib.h>
#include "i2cmaster.h"
#include "myFont.h"

#define DevSSD1306  0x78      // device address of SSD1306 OLED, uses 8-bit address (0x3c)!!! 

static uint8_t buffer[(128 * 64) / 8] = { // 128 x 64 
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
};

int main(void)
{
    unsigned char ret;

    DDRB  = 0xff;                              // use all pins on port B for output 
    PORTB = 0x00;                              // (LED's low & off)

    i2c_init();                                // init I2C interface

    ret = i2c_start(DevSSD1306+I2C_WRITE);       // set device address and write mode
    if ( ret ) {
        /* failed to issue start condition, possibly no device found */
        i2c_stop();
        PORTB=0xff;                            // activate all 8 LED to show error */
    }
    else {
    /* issuing start condition ok, device accessible */
    setup_i2c();
    setup_adc();
    }
    for(;;){
        clearBuffer(buffer);

        // get accelerometer values
        sample_adc_channel(1);
        sample_adc_channel(2);
        sample_adc_channel(3);

        PORTB=0x00;
        drawBuffer(0, 0, buffer);
        PORTB=0xFF;
        _delay_ms(500);

    }
}

void setup_adc(){
    ADCSRA |= ((1<<ADPS1)|(1<<ADPS0));   // setups up ADC clock prescalar to 16
    ADMUX |= (1<<REFS0);                            // set ref voltage to AVCC
    //ADMUX |= (1<<ADLAR);                            // left align results in ADC registers (10 bits across 2 regs)

    ADCSRB &= ~(1<<ADTS2);  // These three cleared should enable free-running mode
    ADCSRB &= ~(1<<ADTS1);
    ADCSRB &= ~(1<<ADTS0); 

    ADCSRA |= (1<<ADATE);                           // ??
    ADCSRA |= (1<<ADEN);                            // enable

    ADCSRA |= (1<<ADSC);                            // start sampling

}
void sample_adc_channel(uint8_t channel){
    ADMUX &= ~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));    // Clear ADC Mux Bits
    if(channel == 1){
        ADMUX |= (1<<MUX0);                             // setup ADC Channel 1
        uint16_t adcVal;
        char valueIn[4];

        lcd_draw_string(0, 0, "ADXL335 Readings: " , buffer);

        ADCSRA |= (1 << ADSC); // Start a new conversion, 
        adcVal = ADC;       // 10 bit reading
        itoa(adcVal, valueIn, 10);
        lcd_draw_string(0,2, "X: " , buffer);
        lcd_draw_string(13, 2, valueIn, buffer);
    }
    else if(channel == 2){
        ADMUX |= (1<<MUX1);                             // setup ADC Channel 2
        uint16_t adcVal;
        char valueIn[4];

        ADCSRA |= (1 << ADSC); // Start a new conversion, 
        adcVal = ADC;       // 10 bit reading
        itoa(adcVal, valueIn, 10);
        lcd_draw_string(0, 3, "Y: ", buffer);
        lcd_draw_string(13, 3, valueIn, buffer);
    }
    else if(channel == 3){
        ADMUX |= ((1<<MUX1)|(1<<MUX0));                 // setup ADC Channel 3
        uint16_t adcVal;
        char valueIn[4];

        ADCSRA |= (1 << ADSC); // Start a new conversion, 
        adcVal = ADC;       // 10 bit reading
        itoa(adcVal, valueIn, 10);
        lcd_draw_string(0, 4, "Z: ", buffer);
        lcd_draw_string(13, 4, valueIn, buffer);
    }


}

void setup_i2c(){
    // Init sequence for 128x64 OLED module
    i2c_write(0xAE);                    // Display Off
    
    i2c_write(0x00 | 0x0);            // low col = 0
    i2c_write(0x10 | 0x0);           // hi col = 0
    i2c_write(0x40 | 0x0);            // line #0

    i2c_write(0x81);                   // Set Contrast 0x81
    i2c_write(0xCF);
                                        // flips display
    i2c_write(0xA1);                    // Segremap - 0xA1
    i2c_write(0xC8);                    // COMSCAN DEC 0xC8 C0
    i2c_write(0xA6);                    // Normal Display 0xA6 (Invert A7)
    
    i2c_write(0xA4);                // DISPLAY ALL ON RESUME - 0xA4
    i2c_write(0xA8);                    // Set Multiplex 0xA8
    i2c_write(0x3F);                    // 1/64 Duty Cycle 

    i2c_write(0xD3);                    // Set Display Offset 0xD3
    i2c_write(0x0);                     // no offset

    i2c_write(0xD5);                    // Set Display Clk Div 0xD5
    i2c_write(0x80);                    // Recommneded resistor ratio 0x80

    i2c_write(0xD9);                  // Set Precharge 0xd9
    i2c_write(0xF1);

    i2c_write(0xDA);                    // Set COM Pins0xDA
    i2c_write(0x12);

    i2c_write(0xDB);                 // Set VCOM Detect - 0xDB
    i2c_write(0x40);

    i2c_write(0x20);                    // Set Memory Addressing Mode
    i2c_write(0x00);                    // 0x00 - Horizontal

    i2c_write(0x40 | 0x0);              // Set start line at line 0 - 0x40 

    i2c_write(0x8D);                    // Charge Pump -0x8D
    i2c_write(0x14); 


    i2c_write(0xA4);              //--turn on all pixels - A5. Regular mode A4
    i2c_write(0xAF);                //--turn on oled panel - AF
}
void drawPixel(int16_t x, int16_t y){//, int16_t color){
//void drawPixel(int16_t x, int16_t y, int16_t color){
    buffer[x+(y/8)*128] |= (1 << (y & 7));
}

void clearBuffer(uint8_t *buff){
    memset(buff, 0, ((128 * 64)/8));
}

void drawBuffer(uint8_t column_address, uint8_t page_address, uint8_t *buff){
    i2c_start(DevSSD1306+I2C_WRITE); 
    i2c_write(0x21);        // column address
    i2c_write(0);           // column start address (0 = reset)
    i2c_write(127);         // column end addres (127 = reset)

    i2c_write(0x22);        // page address
    i2c_write(0);           // page start address (0 = reset);
    i2c_write(7);           // page end address

    uint8_t twbrbackup = TWBR;
    TWBR = 12;

    for (uint16_t i=0; i<((128*64)/8); i++){
        unsigned char ret = i2c_start(DevSSD1306+I2C_WRITE);   // set device address and write mode
        if ( ret ) {
            /* failed to issue start condition, possibly no device found */
            i2c_stop();
            PORTB=0xff;                            // activate all 8 LED to show error */
        }
        else {
            i2c_write(0x40);                        // set display RAM display start line register
            for (uint8_t x=0; x<16; x++){
                i2c_write(buff[i]);
                i++;
            }
            i--;
            i2c_stop();
            TWBR = twbrbackup;
        }
    }
}

void lcd_draw_char(unsigned char column, unsigned char page, unsigned char letter, uint8_t *buff){
    uint8_t ascii_offset = 32;
    for(uint8_t i=0; i<5; i++){
        buff[i+((page*128)+column)] = Ascii_1[letter-ascii_offset][i];
    }
}
void lcd_draw_string(uint8_t column, uint8_t page, char *string, uint8_t *buff){
    uint8_t i = 0;
    while(string[0] != 0){
        //column += 6; // 6 pixels wide
        //if (column + 6 >= 128) {
        //  column = 0;    // ran out of this line
        //  page++;
        //}
        //if (page >= 8)
        //  return;        // ran out of space :(
        lcd_draw_char(column+(5*i), page, (string[0]), buff);
        string++;
        i++;
    }
}
