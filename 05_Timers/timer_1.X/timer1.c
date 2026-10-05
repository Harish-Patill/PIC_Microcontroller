/*
 * File:   timer1.c
 * Author: Harish
 *
 * Created on 1 October, 2026, 4:49 PM
 */

#include <xc.h>
#include "timer1.h"


void init_timer1(void) {
    // Timer1 configuration
    TMR1CS = 0;       // Internal clock
    T1CKPS1 = 0;      // 1:1 prescaler
    T1CKPS0 = 0;

    TMR1ON = 1;       // Enable Timer1

    TMR1 = 3036;         // Preload value

    TMR1IF = 0;       // Clear Timer1 interrupt flag
    TMR1IE = 1;       // Enable Timer1 interrupt

}