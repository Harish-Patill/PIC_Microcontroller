/*
 * File:   main.c
 * Author: Harish
 *
 * Created on 11 October, 2026, 1:00 AM
 */


#include <xc.h>
#include "timer0_header.h"

void init_config(){
    
    TRISB = 0x00;   //Configuring PORTB as output port
    PORTB = 0x00;
    
    init_timer0();  //configure the timer0
    
    GIE = 1;
    PEIE = 1;
}

void main(void) {
    init_config();
    while(1){
        ;
    }
    return;
}
