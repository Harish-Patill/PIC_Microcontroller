/*
 * File:   main.c
 * Author: Haris
 *
 * Created on 13 October, 2026, 9:12 AM
 */


#include <xc.h>
#include "timer1_header.h"

void init_config(){
    //configure the timer1
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
