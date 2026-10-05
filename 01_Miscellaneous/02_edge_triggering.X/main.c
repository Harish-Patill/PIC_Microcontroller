/*
 * File:   main.c
 * Author: Harish
 *
 * Created on 30 September, 2026, 4:06 PM
 */


#include <xc.h>
void main(void){
    TRISB=0X00;                     // PORTB all outputs (LEDs)
    PORTB=0X00;                     // all LEDs off at start

    TRISC=TRISC|0X0F;               // RC0 to RC3 as inputs (switches)

    int flag=1;                     // 1 = switch released, ready for next press

    while(1){
        if(RC0==0 && flag==1){          // switch pressed (active low), counted once
            PORTB=~PORTB;               // invert all 8 bits: all on becomes all off and vice versa
            flag=0;                     // block repeat until released
        }
        else if(RC0==1 && flag==0){     // switch released
            flag=1;                     // ready for the next press
        }
    }
    return;
}