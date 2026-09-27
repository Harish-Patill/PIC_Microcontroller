/*
 * File:   main.c
 * Author: Harish
 *
 * Created on 27 September, 2026, 8:24 PM
 */


#include <xc.h>

void main(void){
    TRISB = 0x00;
    PORTB = 0x00;
    
    int i = 0;
    int delay = 0;
    static unsigned char mask = 0x80;   // start with just the top bit set: 10000000
    
    while(1){
        
        if(delay++ == 20000){
            if(i<8){
                PORTB = (PORTB<<1) | 1;     // turns on from lsb to msb till they fill
            }
            else if(i<16){
                PORTB = PORTB<<1;           // turn off from lsb to msb till they extenguish
            }
            else if(i<24){                  // turns on from the msb to lsb till they fill
                if(i==16) mask = 0x80;      // reset only on first entry to this stage, else it will only work for one cycle
                PORTB = PORTB | mask;       // this will make the msb as 1  
                mask = mask >> 1;           // now doing the right shift will set the new msb as 1
                
//              PORTB = PORTB | (1<<(23-i));   the alternate method using left shift
            
            }
            else if(i<32){                  
                PORTB = PORTB & (PORTB>>1); // turn off from msb to lsb till they extenguish
            }
            else{
                i=-1;                       // reset i
            }
            i++;
            
            delay = 0;                      // reset delay
        }
    }
    return;
}