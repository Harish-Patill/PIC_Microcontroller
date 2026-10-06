/*
 * File:   main.c
 * Author: Harish
 *
 * Created on 5 October, 2026, 3:51 PM
 */


#include <xc.h>
#include "timer0.h"

volatile unsigned char sec_count = 0;

void display(char *ssd){
     for(int i=0; i<4; i++){
        
        PORTA = PORTA & 0XF0; 
        
        PORTD = ssd[i];
        
        PORTA = (PORTA & 0XF0) | 1<<i;
        for(int delay=200; delay--;);
    }
}

void init_int0(void){
    TRISB0 = 1;
    
    INT0IE = 1;
    INT0IF = 0;
}



void init_config(){
    TRISA = 0X00;
    TRISD = 0X00;
    
    TRISB1 = 0;
    RB1 = 0;
    
    init_timer0();
    init_int0();
    GIE = 1;
    PEIE = 1;
}

void main(void){
	unsigned char digit[] = {0X21,0XCB,0X6B,0X2D};
    char ssd[4];
    
    init_config();
	while(1){
		ssd[0] = digit[0];
		ssd[1] = digit[1];
		ssd[2] = digit[2];
		ssd[3] = digit[3];
        
		display(ssd);
        
        if(sec_count >=5){
            
            TMR0IE = 0;
            SLEEP();
            
            TMR0IF = 0;
            TMR0IE = 1;
            sec_count = 0;
        }
        
	}
}