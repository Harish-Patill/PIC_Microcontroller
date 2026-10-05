/*
 * File:   main.c
 * Author: Haris
 *
 * Created on 30 September, 2026, 4:15 PM
 */


#define _XTAL_FREQ 20000000     // set this to your real oscillator frequency
#include <xc.h>
void main(void){
    TRISB=0X00;
    PORTB=0X00;

    TRISC=TRISC|0X0F;

    while(1){
        if(RC0==0){
            PORTB=~PORTB;       // toggle all LEDs
            __delay_ms(300);    // slow enough to see the blinking
        }
    }
    return;
}