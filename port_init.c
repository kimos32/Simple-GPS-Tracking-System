#include "tm4c123gh6pm.h"
#define unlock 0x4C4F434B;

void port_init(void){
SYSCTL_RCGCGPIO_R |= 0x2E; //Initializes ports B, C, D, & F clks
SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R1; //Initializes UART - 1 clk
while ((SYSCTL_PRGPIO_R&0x2E) == 0){}; //waits until ports are initialized

GPIO_PORTC_LOCK_R |= unlock; //unlocks ports C, D, & F
GPIO_PORTD_LOCK_R |= unlock; //rest of the ports are always unlocked
GPIO_PORTF_LOCK_R |= unlock;

GPIO_PORTC_CR_R |= 0xF0; //required with previous group
GPIO_PORTD_CR_R |= 0xC0;
GPIO_PORTF_CR_R |= 0x18;

GPIO_PORTB_DIR_R |= 0x0E; //PB1,2,3 = ouput
GPIO_PORTB_DIR_R &= ~0x01; //PB0 = input
GPIO_PORTC_DIR_R |= 0xF0; //PC4,5,6,7 = output
GPIO_PORTD_DIR_R |= 0xC0; //PD6,7 = output
GPIO_PORTF_DIR_R |= 0x18; //PF3,4 = output

GPIO_PORTB_DEN_R |= 0x0F; //Enables digital signals
GPIO_PORTC_DEN_R |= 0xF0;
GPIO_PORTD_DEN_R |= 0xC0;
GPIO_PORTF_DEN_R |= 0x18;


}