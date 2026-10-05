/*
 * File:   main.c
 * Author: Harish
 *
 * Created on 1 October, 2026, 4:46 PM
 */


#include <xc.h>
#include "timer1.h"

void init_config(){
    //configure the timer0
    TRISB = 0x00;   //Configuring PORTB as output port
    PORTB = 0x00;
    
    init_timer1();
    
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
