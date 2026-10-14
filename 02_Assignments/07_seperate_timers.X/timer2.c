/*
 * File:   timer2.c
 * Author: Haris
 *
 * Created on 6 October, 2026, 4:38 PM
 */


#include <xc.h>
#include "header.h"

void init_timer2(void){
    
    // 2 methods, either dierctly to the T2CON or to the inidvidual bits
    // T2CONbits.T2OUTPS = 4;      // postscale 1:5 (value = postscale - 1)
    // T2CONbits.T2CKPS = 1;       // prescale 1:4 (0 = 1:1, 1 = 1:4, 2 or 3 = 1:16)
    

    T2CON = 0x21;               // 0010 0001 -> postscale 1:5, prescale 1:4, timer OFF
    
    PR2 = 249;                  // period register
    TMR2 = 0;                   // preload=0
    
    TMR2IF = 0;                 // timer2 interrupt flag
    TMR2IE = 1;                 // timer2 interrupt enable

    T2CONbits.TMR2ON = 1;       // start the timer at last
}