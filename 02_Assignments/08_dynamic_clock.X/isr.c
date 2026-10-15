/*
 * File:   isr.c
 * Author: Harish
 *
 * Created on 9 October, 2026, 4:07 PM
 */


#include <xc.h>
#include "dynamic_header.h"

extern volatile unsigned char sec;                  // global sec from the main
extern volatile unsigned int count = 0;            // count variable

void __interrupt() isr(){
    
    if(TMR0IF){                                     // if timer0 flag
        TMR0 = TMR0+8;                              // TMR0=TMR0+8 due to context switching
        if(++count == 20000){
            sec++;
            count = 0;       
        }
        TMR0IF=0;
    }
}