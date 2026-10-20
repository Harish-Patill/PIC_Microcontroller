/*
 * File:   isr.c
 * Author: Haris
 *
 * Created on 19 October, 2026, 4:26 PM
 */


#include "header.h"

extern unsigned int count0;     // this is for the underscore in the clcd
extern unsigned int time;

void __interrupt() isr(){
    static unsigned int count;      // static to retain the count variables value
    
    if(TMR0IF){
        TMR0 = TMR0 + 8;            //considering context switching time + Timer changing
        if(count++ == time){
//            PORTB0 = ~PORTB0;
            PORTBbits.RB0 = ~PORTBbits.RB0;
            count = 0;
        }
        
        if(count0++ >= 20000){
            count0 = 0;
        }
        TMR0IF = 0;
    }
}