/*
 * File:   isr.c
 * Author: Harish
 *
 * Created on 1 October, 2026, 4:49 PM
 */


#include <xc.h>
#include"timer1.h"

void __interrupt() isr(void){
    static unsigned int count;
    if(TMR1IF){
        TMR1 = TMR1 + 3038;  //considering context switching time + Timer changing
        if(count++ == 80){
            RB7 = ~RB7;
            count = 0;
        }
        TMR1IF = 0;
    }
}
