/*
 * File:   isr.c
 * Author: Haris
 *
 * Created on 13 October, 2026, 11:14 AM
 */


#include <xc.h>
#include "timer2_header.h"

void __interrupt() isr(void){
    static unsigned int count = 0;

    if(TMR2IF){                     
        if(++count == 1000){        // 1000 × 1 ms = 1 s
            RB7 = ~RB7;
         // LATB7 ^= 1;
            count = 0;
        }
        TMR2IF = 0;                 // clear flag;
    }
}