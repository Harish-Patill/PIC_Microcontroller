/*
 * File:   isr.c
 * Author: Harish
 *
 * Created on 6 October, 2026, 4:38 PM
 */


#include <xc.h>
#include "header.h"

void __interrupt() isr(){
    static unsigned int count0=0;
    static unsigned int count1=0;
    static unsigned int count2=0;

    if(TMR0IF){
        TMR0 = TMR0+8;
        if(++count0 == 20000){
            RB0 = !RB0;
            count0 = 0;
        }
        TMR0IF=0;
    }
    
    if(TMR1IF){
        TMR1 = TMR1+3038;
        if(++count1 == 80){
            RB1 = !RB1;
            count1 = 0;
        }
        TMR1IF=0;
    }
    
    if(TMR2IF){
//      TMR2 = TMR2+3038;
        if(++count2 == 1000){
            RB3 = !RB3;
            count2 = 0;
        }
        TMR2IF=0;
    }
}

