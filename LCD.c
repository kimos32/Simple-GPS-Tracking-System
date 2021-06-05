
#include "tm4c123gh6pm.h"
#include "port_init.c"

#define LCD_RS  (GPIO_PORTB_DATA_R )    //PB.7 for 
#define LCD_EN  (GPIO_PORTB_DATA_R )   //PB.3 for enable 
 

/*function protoypes */
void LCD_CMD(unsigned long cmd);
void LCD_WRITE (char data);
void Delay(void);
void LCD_CURSOR (void);





//this function passes the command to the LCD
void LCD_CMD(unsigned long cmd) {
       
    GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & ~0x08) | ((cmd & 0x01 ) << 3 ); //PB3 = D0
    GPIO_PORTC_DATA_R = (GPIO_PORTC_DATA_R & ~0xF0) | ((cmd & 0x1E ) << 3 ); //PC4,5,6,7 = D1,2,3,4
    GPIO_PORTD_DATA_R = (GPIO_PORTD_DATA_R & ~0xC0) | ((cmd & 0x60 ) << 1 ); //PD6,7 = D5,6
    GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & ~0x40) | ((cmd & 0x80 ) >> 1 ); //PB6 = D7
    
    
    LCD_RS &= 0x7F;  //set PB7 register select pin to low
    LCD_EN |= 0x04;  //set enable pin to high
    Delay();        //short delay 
    LCD_EN &= 0xFB;  //set enable pin to low 
}

//this function passes the data to the LCD
void LCD_WRITE (char data) {
    GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & ~0x08) | ((data & 0x01 ) << 3 ); //PB3 = D0
    GPIO_PORTC_DATA_R = (GPIO_PORTC_DATA_R & ~0xF0) | ((data & 0x1E ) << 3 ); //PC4,5,6,7 = D1,2,3,4
    GPIO_PORTD_DATA_R = (GPIO_PORTD_DATA_R & ~0xC0) | ((data & 0x60 ) << 1 ); //PD6,7 = D5,6
    GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & ~0x40) | ((data & 0x80 ) >> 1 ); //PB6 = D7

    LCD_RS |= 0x80;  //set PB7 to high
    LCD_EN |= 0x04;  //set the enable pin high
    Delay();        //short delay
    LCD_EN &= 0xFB;  //set the enable pin to low
}

//short delay function
void Delay(void) {
    unsigned long  time;
    time = 500; 
    while(time){
        time--;
    }
}

//LCD_cursor function to move the cursor to right
void LCD_CURSOR (void){
    LCD_CMD(0x06);
}
