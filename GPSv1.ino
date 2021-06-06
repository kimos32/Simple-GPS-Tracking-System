#include "tm4c123gh6pm.h"

 #define LCD_RS GPIO_PORTB_DATA_R
 #define LCD_EN GPIO_PORTB_DATA_R
 #define GreenLED GPIO_PORTF_DATA_R

  int Distance = 0;
  int Desired_Distance = 100;

void setup() {
  LED_init();
  LCD_init();
  
for(Distance=0; Distance<=9999; Distance++){ //main counter loop
  LCD_CMD(0x80);
  LCD_String ("Distance: ");
  LCD_CMD(0xC0);
  LCD_String("    ");
  LCD_NUM(Distance);
  LCD_String(" meters");
  delay(1000);
  LCD_CMD(0x01);
    if(Distance >= Desired_Distance){ //Turns green LED ON when the distance reaches the desired distance
    GreenLED |= 0x08;
    } 
  }
}

void LED_init(void){
  SYSCTL_RCGCGPIO_R |= 0x20;

  GPIO_PORTF_DIR_R |= 0x08;
  GPIO_PORTF_DEN_R |= 0x08;
  }

void LCD_init(void){

  SYSCTL_RCGCGPIO_R |= 0x03;
  
  GPIO_PORTB_DIR_R |= 0xCC; //PB2,3,6,7 = ouput
  GPIO_PORTC_DIR_R |= 0xF0; //PC4,5,6,7 = output
  GPIO_PORTD_DIR_R |= 0xC0; //PD6,7 = output

  GPIO_PORTB_DEN_R |= 0xCC; //Enables digital signals
  GPIO_PORTC_DEN_R |= 0xF0;
  GPIO_PORTD_DEN_R |= 0xC0;

  LCD_CMD(0x38);
  LCD_CMD(0x06);
  LCD_CMD(0x0C);
  LCD_CMD(0x01);

}

void LCD_CMD(char cmd){
    LCD_RS &= 0x7F;  //set PB7 register select pin to low
    
    GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & ~0x08) | ((cmd & 0x01) << 3); //PB3 = D0
    GPIO_PORTC_DATA_R = (GPIO_PORTC_DATA_R & ~0xF0) | ((cmd & 0x1E) << 3); //PC4,5,6,7 = D1,2,3,4
    GPIO_PORTD_DATA_R = (GPIO_PORTD_DATA_R & ~0xC0) | ((cmd & 0x60) << 1); //PD6,7 = D5,6
    GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & ~0x40) | ((cmd & 0x80) >> 1); //PB6 = D7
    
    LCD_EN |= 0x04;  //set enable pin to high
    delay(3);
    LCD_EN &= 0xFB;  //set enable pin to low
  
}

void LCD_DATA(char data){
    LCD_RS |= 0x80;  //set PB7 register select pin to high
    
    GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & ~0x08) | ((data & 0x01) << 3); //PB3 = D0
    GPIO_PORTC_DATA_R = (GPIO_PORTC_DATA_R & ~0xF0) | ((data & 0x1E) << 3); //PC4,5,6,7 = D1,2,3,4
    GPIO_PORTD_DATA_R = (GPIO_PORTD_DATA_R & ~0xC0) | ((data & 0x60) << 1); //PD6,7 = D5,6
    GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & ~0x40) | ((data & 0x80) >> 1); //PB6 = D7

    LCD_EN |= 0x04;  //set enable pin to high
    delay(3);
    LCD_EN &= 0xFB;  //set enable pin to low

}

//Allows writing strings on the LCD
void LCD_String (char *phrase)
{
  int v;
  for(v=0;phrase[v]!=0;v++)
  {
    delay(1);
    LCD_DATA(phrase[v]);
  }
}

//Allows writing numbers on the LCD
void LCD_NUM(int x){
    LCD_DATA((x/1000)+48); //Outputs thousands with ASCII offset
    x %= 1000;

    LCD_DATA((x/100)+48); //Outputs hundreds with ASCII offset
    x %= 100;

    LCD_DATA((x/10)+48); //Outputs tens with ASCII offset
    x %= 10;

    LCD_DATA(x+48); //Outputs ones with ASCII offset
}

void loop() {  

}
