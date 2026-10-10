/*
 * File:   timer0.c
 * Author: Harish
 *
 * Created on 11 October, 2026, 1:03 AM
 */


#include <xc.h>
#include "timer0_header.h"

void init_timer0(void){
    
    // Configure everything first, enable the timer last
    T08BIT = 1;         // 8-bit mode
    T0CS = 0;           // internal clock source (Fosc/4)
    PSA = 1;            // 1 = prescaler bypassed, 0 = prescaler used

    TMR0 = 6;           // preload (8-bit mode uses TMR0L actually)
                        // TMR0L is what claude said would be better, else it needs to read and write for both bytes.

    TMR0IF = 0;         // clear any old overflow flag
    TMR0IE = 1;         // enable Timer0 overflow interrupt

    TMR0ON = 1;         // start timer
}
