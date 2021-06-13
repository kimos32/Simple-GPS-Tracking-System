#include "LCD.c"
#define GreenLED GPIO_PORTF_DATA_R
#include "convert.c"
#define Desired_Distance 100

int main (void){
  int error = 0;
	void gps();

  port_init();
	
	LCD_CMD(0X38); //Setups 2 row mode
  LCD_CMD(0x06); //shifts display 1 digit to the left
  LCD_CMD(0X0C); //hides cursor
  LCD_CMD(0X01); //clears the display

  while(1){ //main counter loop
  gps();
  
    if (Distance> 100){               //Condition for +100 meter phase (w/ error)
      LCD_CMD(0x80);
      LCD_String ("Distance: ");LCD_NUM(Desired_Distance); LCD_DATA('m');
      LCD_CMD(0xC0);
        error = Distance - Desired_Distance;
      LCD_String("Error: ");LCD_NUM(error); LCD_DATA('m');
      delay(5000000);
      LCD_CMD(0x01);
    } 
      else if(Distance<= Desired_Distance){                       //Condtion for -100 meter phase
        LCD_CMD(0x80);
      LCD_String ("Distance: ");LCD_NUM(Distance); LCD_DATA('m');
      delay(5000000);
      LCD_CMD(0x01);
    }

    if(Distance >= Desired_Distance){ //Turns green LED ON when the distance reaches the desired distance
    GreenLED |= 0x08;
    }
  
  

  }
	
}

