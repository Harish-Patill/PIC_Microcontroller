/*
 * File:   main.c
 * Author: Harish
 *
 * Created on 6 October, 2026, 4:37 PM
 */


#include <xc.h>
#include "header.h"


void init_config(){
    TRISB = 0;                  // make all of PORTB as o/p
    RB0 = 0;                    // setting first 3 led's value as 0
    RB1 = 0;
    RB2 = 0;
        
    init_timer0();              // timer0,1,2 configuration
    init_timer1();
    init_timer2();
    
    GIE = 1;                    // global enable
    PEIE = 1;                   // pheripheral enable
}


void main(void) {
    init_config();
    while(1){
        ;
    }
    return;
}
