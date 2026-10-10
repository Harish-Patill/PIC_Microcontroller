/*
 * File:   isr.c
 * Author: Haris
 *
 * Created on 11 October, 2026, 1:02 AM
 */


#include <xc.h>
#include "timer0_header.h"

void __interrupt() isr(){
    static unsigned int count;      // static to retain the count variables value
    if(TMR0IF){
        TMR0 = TMR0 + 8;            //considering context switching time + Timer changing
        if(count++ == 5000){
            PORTB = ~PORTB;
            count = 0;
        }
        TMR0IF = 0;
    }
}
