/*
 * File:   main.c
 * Author: Haris
 *
 * Created on 13 October, 2026, 11:09 AM
 */


#include <xc.h>
#include "timer2_header.h"

void init_config(){
    // configuring timer2
    
    TRISB = 0X00;       // config PORTB as output port
    PORTB = 0X00;
    
    GIE = 1;
    PEIE = 1;
    init_timer2();
}


void main(void) {
    init_config();
    
    while(1){
        ;
    }
    return;
}
