/*
 * File:   timer0.c
 * Author: Harish
 *
 * Created on 9 October, 2026, 4:07 PM
 */


#include <xc.h>
#include "dynamic_header.h"


void init_timer0(){
    T08BIT = 1;
    T0CS = 0;           // internal clock source
    PSA = 1;            // prescaler (1 is off/ 0 is on)
    TMR0 = 6;
    TMR0IF = 0;         // timer0 interrut flag
    TMR0IE = 1;         // timer0 enable
    TMR0ON = 1;         // enable the module (Timer0 On/Off Control bit)
}