#include "LCD.c"
#define LED   GPIO_PORTF_DATA_R

int main (void){

    int Distance;
		int i = 0;
     port_init();
	
	       /*this function must be written as Keil 
         allows running of a function before the main*/
	      while(1) {
        LCD_CMD(0X38);  //8-bit bus mode, 2 line display mode, 5x8 dots display mode
        Delay();
        LCD_CMD(0X01);  //clear display
        Delay();
        LCD_CMD(0X0C);  //display is on 
        Delay();
        LCD_CMD(0x80);  // set cursor to beginning of first row
        Delay(); 
		   	LCD_WRITE('K'); //send Distance on the LCD 
        Delay();
    
				   for (Distance=0 ; Distance <= 0 ; Distance ++ ){

        if (Distance >= 100){

             LED |= 0x08;
        }
        else {
            LED &= ~0x08;
        }
        LCD_CMD(0x0C);              // set cursor to beginning of second row 
				
        while (i < 12){
            LCD_CMD(0x14);          // Shift cursor position to right
					i++;
        }
        LCD_WRITE(Distance);    // write value of Distance on the "LCD" 
    }

				
				}
	
 
	}
