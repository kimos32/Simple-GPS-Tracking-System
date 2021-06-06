#include "LCD.c"
#define GreenLED GPIO_PORTF_DATA_R

int main (void){
  int Distance = 0;
  int Desired_Distance = 100;
	
  port_init();
	
	LCD_CMD(0X38); //Setups 2 row mode
  LCD_CMD(0x06); //shifts display 1 digit to the left
  LCD_CMD(0X0C); //hides cursor
  LCD_CMD(0X01); //clears the display

  for(Distance=0; Distance<=9999; Distance++){ //main counter loop
  LCD_CMD(0x80);
	LCD_String ("Distance: ");
  LCD_CMD(0xC0);
	LCD_String("    ");
	LCD_NUM(Distance);
	LCD_String(" meters");
  delay(3000000);
  LCD_CMD(0x01);
  
    if(Distance >= Desired_Distance){ //Turns green LED ON when the distance reaches the desired distance
    GreenLED |= 0x08;
    }

  }
}

