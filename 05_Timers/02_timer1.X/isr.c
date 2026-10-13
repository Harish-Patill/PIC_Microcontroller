/*
 * File:   isr.c
 * Timer1 ISR: toggles RB7 every 1 s
 *
 * Fosc = 20 MHz, preload 3036, prescale 1:1
 * One overflow = 62500 x 0.2 us = 12.5 ms
 * 80 overflows x 12.5 ms = 1 s
 */

#include <xc.h>
#include "timer1_header.h"

void __interrupt() isr(void){
    static unsigned int count = 0;     // static: keeps its value between ISR calls

    if(TMR1IF){                        
        TMR1 = TMR1 + 3038;            // compensated reload: 3036 (preload) + 2 (write penalty)
                                       // adds to current value so counts during ISR entry are kept
        
        if(++count == 80){             // 80 overflows = 1 sec
            RB7 = ~RB7;                
            count = 0;                 // restart the count
        }
        TMR1IF = 0;                    // clear flag in software, otherwise ISR re-enters
    }
}