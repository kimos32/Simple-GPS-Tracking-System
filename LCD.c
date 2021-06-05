#include "port_init.c"

#define LCD_RS  (GPIO_PORTB_DATA_R) //PB7 - Register Select 
#define LCD_EN  (GPIO_PORTB_DATA_R) //PB3 - Enable
#define LCD_RW  (GPIO_PORTD_DATA_R) //PD0 - Read/Write
 

//function protoypes for initialization

void LCD_CMD(char cmd);
void LCD_DATA(char data);
void LCD_NUM(int n);
void LCD_String(char *str);
void delay(unsigned long time);




//this function passes the command to the LCD
void LCD_CMD(unsigned long cmd) {
       
    GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & ~0x08) | ((cmd & 0x01) << 3); //PB3 = D0
    GPIO_PORTC_DATA_R = (GPIO_PORTC_DATA_R & ~0xF0) | ((cmd & 0x1E) << 3); //PC4,5,6,7 = D1,2,3,4
    GPIO_PORTD_DATA_R = (GPIO_PORTD_DATA_R & ~0xC0) | ((cmd & 0x60) << 1); //PD6,7 = D5,6
    GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & ~0x40) | ((cmd & 0x80) >> 1); //PB6 = D7
    
    
    LCD_RS &= 0x7F;  //set PB7 register select pin to low
    LCD_RW &= 0x00;  //clear PD0
    LCD_EN |= 0x04;  //set enable pin to high
    delay(30000);         //short delay 
    LCD_EN &= 0xFB;  //set enable pin to low 
}

//this function passes the data to the LCD
void LCD_DATA (char data) {
    GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & ~0x08) | ((data & 0x01) << 3); //PB3 = D0
    GPIO_PORTC_DATA_R = (GPIO_PORTC_DATA_R & ~0xF0) | ((data & 0x1E) << 3); //PC4,5,6,7 = D1,2,3,4
    GPIO_PORTD_DATA_R = (GPIO_PORTD_DATA_R & ~0xC0) | ((data & 0x60) << 1); //PD6,7 = D5,6
    GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & ~0x40) | ((data & 0x80) >> 1); //PB6 = D7

    LCD_RS |= 0x80;  //set PB7 to high
    LCD_RW &= 0x00;  //clear PD0
    LCD_EN |= 0x04;  //set the enable pin high
    delay(30000);        //short delay
    LCD_EN &= 0xFB;  //set the enable pin to low
}

// Controls LCD delay
void delay(unsigned long  time) { //in microseconds
    while(time){
        time--;
    }
}


//Allows writing strings on the LCD
void LCD_String (char *phrase)
{
  int v;
  for(v=0;phrase[v]!=0;v++)
  {
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

