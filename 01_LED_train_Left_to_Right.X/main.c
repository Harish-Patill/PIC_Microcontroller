/*
 * File:   main.c
 * Author: Harish
 *
 * Created on 27 September, 2026, 5:05 PM
 */


#include <xc.h>

void main(void) {
    int i=0;
    
    TRISB = 0x00;                               // TRISB=0 as mc sends signals 
    PORTB = 0x00;                               // turning off all the leds
    
    
    while(1){
        if(i++ < 8){                            // will turn on the leds one by one(we've 8 leds)
            PORTB=(PORTB<<1) | 1;               // left shift && setting the LSB
                                                // 0000 0010 | 0000 0001 = 0000 0011
        }
        else if(i<16){                          // will turn off the leds one by one from the back
            PORTB=PORTB<<1;                     // left shifting, will fill the LSB's with 0's
                                                // 1111 1110 << 1 = 1111 1100
        }
        else{
            i=0;
        }
        for(int delay=60000;delay--;);          // this delay is between each led turning ON or OFF;
    }
    return;
}