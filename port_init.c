#include "tm4c123gh6pm.h"
#define unlock 0x4C4F434B;

void port_init(void){
SYSCTL_RCGCGPIO_R |= 0x2E; //Initializes ports B, C, D, & F clks
SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R1; //Initializes UART - 1 clk

UART1_CTL_R &= ~UART_CTL_UARTEN; //disables UART control
UART1_IBRD_R = 104; //baudrate = 9600
UART1_FBRD_R = 11;
UART1_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN); //sets length of 8 bits & FIFO
UART1_CTL_R |= (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN); // enables read, write, & control

GPIO_PORTC_LOCK_R |= unlock; //unlocks ports C, D, & F
GPIO_PORTD_LOCK_R |= unlock; //rest of the ports are always unlocked
GPIO_PORTF_LOCK_R |= unlock;

GPIO_PORTC_CR_R |= 0xF0; //required with previous group
GPIO_PORTD_CR_R |= 0xC0;
GPIO_PORTF_CR_R |= 0x18;

GPIO_PORTB_DIR_R |= 0x8E; //PB1,2,3,7 = ouput
GPIO_PORTB_DIR_R &= ~0x01; //PB0 = input
GPIO_PORTC_DIR_R |= 0xF0; //PC4,5,6,7 = output
GPIO_PORTD_DIR_R |= 0xC0; //PD6,7 = output
GPIO_PORTF_DIR_R |= 0x18; //PF3,4 = output

GPIO_PORTB_DEN_R |= 0x8F; //Enables digital signals
GPIO_PORTC_DEN_R |= 0xF0;
GPIO_PORTD_DEN_R |= 0xC0;
GPIO_PORTF_DEN_R |= 0x18;

GPIO_PORTB_AMSEL_R &= ~0x8F; //disables analog signals
GPIO_PORTC_AMSEL_R &= ~0xF0;
GPIO_PORTD_AMSEL_R &= ~0xC0;
GPIO_PORTF_AMSEL_R &= ~0x18;

GPIO_PORTB_AFSEL_R |= 0x03; //enables PB0,1 alternate functions
GPIO_PORTB_AFSEL_R &= ~0x8C; //disables alternate functions for the rest
GPIO_PORTC_AFSEL_R &= ~0xF0;
GPIO_PORTD_AFSEL_R &= ~0xC0;
GPIO_PORTF_AFSEL_R &= ~0x18;

GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & ~0xFF) | (GPIO_PCTL_PB1_U1TX | GPIO_PCTL_PB0_U1RX);
//specifies pin control functions for PB0,1
GPIO_PORTB_PCTL_R &= ~0xF000FF00; //clears the bits of the other pins
GPIO_PORTD_PCTL_R &= ~0xFF000000;
GPIO_PORTC_PCTL_R &= ~0xFFFF0000;
GPIO_PORTF_PCTL_R &= ~0x000FF000;

GPIO_PORTF_PUR_R|= 0x08; //Pull-up resistance for PF3 (LED)
}