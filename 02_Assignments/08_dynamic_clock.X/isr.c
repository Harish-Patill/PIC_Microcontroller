/*
 * File:   isr.c
 * Author: Harish
 *
 * Created on 9 October, 2026, 4:07 PM
 */


#include <xc.h>
#include "dynamic_header.h"

extern volatile unsigned char sec;                  // global sec from the main

void __interrupt() isr(){
    static unsigned int count0 = 0;                 // count variable
    
    if(TMR0IF){                                     // if timer0 flag
        TMR0 = TMR0+8;                              // TMR0=TMR0+8 due to context switching
        if(++count0 == 20000){
            sec++;
            count0 = 0;       
        }
        TMR0IF=0;
    }
}