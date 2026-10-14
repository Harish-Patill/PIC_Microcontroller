/*
 * File:   timer1.c
 * Author: Haris
 *
 * Created on 6 October, 2026, 4:37 PM
 */


#include <xc.h>
#include "header.h"

void init_timer1(void){
    
    // we can either directly assign value to T1CON or set values for each bits
    // T1CON = 0x80;       // 1000 0000 -> RD16=1, prescale 1:1, internal clock, timer OFF
    
    // so for the RD16 we have 3 methods to set the value where RD16 = 1 is not one of them
        // 1. use T1RD16
        // 2. T1CONbits.RD16 = 1;
        // 3. use the T1CON method
    
    
    //T1CONbits.RD16 = 1;
    T1RD16 = 1;         // 16-bit read/write mode
    
    TMR1CS = 0;         // internal clock (Fosc/4)
    T1CKPS1 = 0;        // prescale 1:1  (T1CKPS1:T1CKPS0 = 00)
    T1CKPS0 = 0;        // for 1:8 set both to 1

    TMR1 = 3036;        // preload (65536 - 62500)

    TMR1IF = 0;         // clear old overflow flag
    TMR1IE = 1;         // enable Timer1 interrupt

    TMR1ON = 1;         // start timer

}