/*
 * File:   main.c
 * Author: ajith
 *
 * Created on October 1, 2026, 3:47 PM
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

void main(void) {
    init_config();
    while(1){
        ;
    }
    return;
}
