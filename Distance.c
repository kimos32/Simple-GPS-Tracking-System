#include "LCD.c"
#define LED   GPIO_PORTF_DATA_R

int main (void){

    int Distance;
    
    for (Distance=0 ; Distance <= 0 ; Distance ++ ){

        if (Distance >= 100){

             LED |= 0x08;
        }
        else {
            LED &= ~0x08;
        }
        LCD_CMD(0x0C);          // set cursor to beginning of second row 

        LCD_WRITE(Distance);
    }


}