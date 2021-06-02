#include "tm4c123gh6pm.h"
#include "stdint.h"
#include <uart_init.c>
#define PF3 0x04

void LED_init(void){
SYSCTL_RCGCGPIO_R |= 0x20;
while ((SYSCTL_PRGPIO_R & 0x20) == 0){};

GPIO_PORTF_LOCK_R = 0x4C4F434B;
GPIO_PORTF_CR_R |= PF3;
GPIO_PORTF_DIR_R |= PF3;
GPIO_PORTF_DEN_R |= PF3;
GPIO_PORTF_AMSEL_R &= ~PF3;
GPIO_PORTF_AFSEL_R &= ~PF3;
GPIO_PORTF_PCTL_R &= ~0x0000F000;
GPIO_PORTF_PUR_R |= PF3;
}