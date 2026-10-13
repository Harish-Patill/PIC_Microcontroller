/*
 * File:   timer1.c
 * Author: Haris
 *
 * Created on 6 October, 2026, 4:37 PM
 */


#include <xc.h>
#include "header.h"

void init_timer1(){
    
    T1CON = 0X00;
    //RD16 = 1;
    TMR1CS = 0;
    //T1RUN = 0;
    T1CKPS1 = 1;
    T1CKPS0 = 0;
    
    TMR1=3036;
    TMR1IF = 0;
    TMR1IE = 1;
    TMR1ON = 1;
}
