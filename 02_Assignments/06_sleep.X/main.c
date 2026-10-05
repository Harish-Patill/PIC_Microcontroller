/*
 * File:   main.c
 * Author: Harish
 *
 * Created on 5 October, 2026, 3:51 PM
 */


#include <xc.h>
#include "timer0.h"

void init_config(){
    //configure the timer0
    TRISB = 0x00;   //Configuring PORTB as output port
    PORTB = 0x00;
    init_timer0();
    GIE = 1;
    PEIE = 1;
}

void display(char *ssd){
    for(int i=0; i<4; i++){
        PORTD = ssd[i];
        PORTA = (PORTA & 0XF0) | 1<<i;
        for(int delay=800; delay--;);  // this delay does the work of keeping the digits lit.
    }
}

void main(void) {
    
    
    PORTD = 0x00;
    TRISD = 0x00;           // PORTD = all outputs ? drives the 7-segment patterns

    TRISA = TRISA & 0xF0;   // clear lower 4 bits of TRISA ? RA0-RA3 as outputs, upper 4 untouched
    PORTA = PORTA & 0xF0;   // clear lower 4 bits of PORTA ? start with all digit-select lines off
    
    char ssd[4];
    unsigned char digit[]={0X21,0XCB,0X6B,0X2D};

    for(int i=0;i<5;i++){
        ssd[i]=digit[i];
    }
    init_config();
    
    while(1){
        for(unsigned int t=0;t<500;t++){
            display(ssd);
        }
        
        SLEEP();
        
    }
    return;
}
