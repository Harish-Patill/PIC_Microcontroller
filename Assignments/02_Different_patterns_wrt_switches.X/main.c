/*
 * File:   main.c
 * Author: Harish
 *
 * Created on 27 September, 2026, 10:45 PM
 */

#include <xc.h>

//#define SW1 0x0E   // 00001110
//#define SW2 0x0D   // 00001101
//#define SW3 0x0B   // 00001011
//#define SW4 0x07   // 00000111

void main(void){
    
    TRISB=0X00;                         // PORTB all outputs (LEDs)
    PORTB=0X00;
                                        
                                        // TRISC lower 4 bits are inputs (SWITCH's)
    TRISC=TRISC | 0X0F;                 // set lower 4 bits of PORTC (RC0-RC3) as inputs, keep rest as-is
    
    int flag=0;
    int i=0;
    unsigned long int delay=0;
    
    while(1){ 
        if(delay++ == 50000){
            if(RC0==0){
                flag=1;
                i=0;
                PORTB=0X00;
            }
            
            else if(RC1==0){
                flag=2;
                i=0;
                PORTB=0X00;
            }
            
            else if(RC2==0){
                flag=3;
                i=0;
                PORTB=0X55;
            }
            
            else if(RC3==0){
                flag=4;
                i=0;
                PORTB=0X0F;
            }
            
            // pattern 1:
            if(flag == 1){
                if(i<8){
                    PORTB = (PORTB<<1) | 1;             // lit from lsb to msb
                }
                else if(i<16){
                    PORTB = PORTB<<1;                   // ext from lsb to msb
                }
                else if(i<24){                          
                    PORTB = PORTB | (1<<(23-i));        // lit from msb to lsb
                }
                else if(i<32){
                    PORTB = PORTB & (PORTB>>1);         // ext from msb to lsb
                }
                else{
                    i=-1;
                }
                i++;
            }
            
            // pattern 2:
            if(flag == 2){
                if(i<8){
                    PORTB = (PORTB<<1) | 1;
                }
                else if(i<16){
                    PORTB = PORTB<<1;
                }
                else{
                    i = -1;
                }
                i++;
            }
            
            // pattern 3: 
            if(flag==3){
                PORTB= ~PORTB;
            }
            
            // pattern 4:
            if(flag==4){
                PORTB= ~PORTB;
            }
            delay = 0;
        }
    }
    return;
}