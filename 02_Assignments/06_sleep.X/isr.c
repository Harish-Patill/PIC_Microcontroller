/*
 * File:   isr.c
 * Author: Harish
 *
 * Created on 5 October, 2026, 3:51 PM
 */


#include"timer0.h"
#include<xc.h>
void __interrupt() isr(){
    static unsigned int count;
    
    if(TMR0IF){
        TMR0 = TMR0 + 8;  //considering context switching time + Timer changing
        
        if(count++ == 5000){
            PORTB = ~PORTB;
            count = 0;
        }
        TMR0IF = 0;
    }
}