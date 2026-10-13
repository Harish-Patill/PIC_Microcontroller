/*
 * File:   isr.c
 * Author: Harish
 *
 * Created on 5 October, 2026, 3:51 PM
 */


#include <xc.h>
#include "timer0.h"

extern volatile unsigned char sec_count;

void __interrupt() isr(){
    
    
    static unsigned int count;
    if(TMR0IF){
        TMR0 = TMR0 + 8;
        if(count++ == 20000){
            RB1 = !RB1;
            count = 0;
            
            sec_count++;
        }
        TMR0IF = 0;
    }
    
    if(INT0IF){
        INT0IF = 0;
        sec_count = 0;
        
    }
}