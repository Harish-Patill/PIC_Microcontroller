/*
 * File:   main.c
 * Author: Harish
 *
 * Created on 28 September, 2026, 12:21 AM
 */

#include <xc.h>
void display(char *ssd){
    for(int i=0; i<4; i++){
        PORTD = ssd[i];
        PORTA = (PORTA & 0XF0) | 1<<i;
        for(int delay=1000; delay--;);  // this delay does the work of keeping the digits lit.
    }
}

void main(void){
    
    PORTD = 0x00;
    TRISD = 0x00;           // PORTD = all outputs ? drives the 7-segment patterns

    TRISA = TRISA & 0xF0;   // clear lower 4 bits of TRISA ? RA0-RA3 as outputs, upper 4 untouched
    PORTA = PORTA & 0xF0;   // clear lower 4 bits of PORTA ? start with all digit-select lines off
    
    int i=0;
    char ssd[4];
    int delay=0;
    unsigned char digit[]={0XE7,0X21,0XCB,0X6B,0X2D,0X6E,0XEE,0X23,0XEF,0X6F,0x00,0x00};
    
    while(1){
        ssd[0]=digit[i];
        ssd[1]=digit[(i+1)%12];
        ssd[2]=digit[(i+2)%12];
        ssd[3]=digit[(i+3)%12];
        display(ssd);
        
        // This delay controls how fast the display scrolls
        if(delay++==200){
            i++;
            if(i==12){
                i=0;
            }
            delay=0;
        }
    }
    return;
}