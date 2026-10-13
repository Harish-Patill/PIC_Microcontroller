/*
 * File:   main.c
 * Author: Haris
 *
 * Created on 6 October, 2026, 4:37 PM
 */


#include <xc.h>
#include "header.h"


void init_config(){
    TRISB = 0;
    RB0 = 0;
    RB1 = 0;
    RB2 = 0;
        
    init_timer0();
    init_timer1();
    init_timer2();
    
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
