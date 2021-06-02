
#include "tm4c123gh6pm.h"
#include "port_init.c"

#define LCD_RS  (GPIO_PORTB_DATA_R )    //PB.7 for 
#define LCD_EN  (GPIO_PORTB_DATA_R )   //PB.3 for enable 
 

/*function protoypes */
void LCD_CMD(unsigned long cmd);
void LCD_WRITE (char data);
void Delay(void);

/*this function must be writen as keil 
allows running of a function before the main*/

int main (void) {
   
    while(1) {
        LCD_CMD(0X38);  //8-bit bus mode, 2 line display mode, 5x8 dots display mode
        Delay();
        LCD_CMD(0X01);  //clear display
        Delay();
        LCD_CMD(0X10);  //cursor display shift
        Delay();
        LCD_CMD(0X0C);  //diplay is on
        Delay();
        LCD_WRITE('A'); //send character A on the LCD 
        Delay();
    }
}


//this function passes the command to the LCD
void LCD_CMD(unsigned long cmd) {
       
    GPIO_PORTB_DATA_R |= (GPIO_PORTB_DATA_R & ~0x08) | ((cmd & 0x01 ) << 3 )  ; // pb3 == D0
    GPIO_PORTC_DATA_R |= (GPIO_PORTC_DATA_R & ~0xF0) | ((cmd & 0x1E ) << 3 ); //pc 4,5,6,7 = D 1,2,3,4
    GPIO_PORTD_DATA_R |= (GPIO_PORTD_DATA_R & ~0xC0) | ((cmd & 0x60 ) << 1 ); // PD 6,7 = D 5,6
    GPIO_PORTF_DATA_R |= (GPIO_PORTF_DATA_R & ~0x10) | ((cmd & 0x80 ) << 3 ); //PF4 = D7
    
    
    LCD_RS = 0x00;  //set PB7 register select pin to low
    LCD_EN = 0x04;  //set enable pin to high
    Delay();        //short delay 
    LCD_EN = 0x00;  //set enable pin to low 
}

//this function passes the data to the LCD
void LCD_WRITE (char data) {
    GPIO_PORTB_DATA_R = data;   //write the data to PB7-0
    LCD_RS = 0x80;  //set PB7 to high
    LCD_EN = 0x04;  //set the enable pin high
    Delay();        //short delay
    LCD_EN = 0x00;  //set the enable pin to low
}

//short delay function
void Delay(void) {
    unsigned long  time;
    time = 500; 
    while(time){
        time--;
    }
}