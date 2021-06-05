#include "LCD.c"
#define Green_LED GPIO_PORTF_DATA_R

int main (void){
  port_init();

  int Distance = 0;
  int Desired_Distance = 100;

	LCD_CMD(0X38); //Setups 2 row mode
  LCD_CMD(0x06); //shifts display 1 digit to the left
  LCD_CMD(0X0C); //hides cursor
  LCD_CMD(0X01); //clears the display

  for(Distance=0; Distance<=9999; Distance++){ //main counter loop
  LCD_String ("Distance: ");
  LCD_NUM(Distance);
  delay(1000000);
  LCD_CMD(0x01);
  
    if(Distance >= Desired_Distance){ //Turns green LED ON when the distance reaches the desired distance
    Green_LED |= 0x08;
    }

  }
}