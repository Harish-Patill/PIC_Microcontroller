/*
 * File:   main.c
 * Author: Harish
 *
 * Created on 6 October, 2026, 11:03 AM
 * 
 * This project can perform both EDGE and the LEVEL triggering, just change the wording in 21st line!
 * 
 */


#include <xc.h>
#include"header.h"

void main(void) {
    init_digital_keypad();
    
    TRISB = 0X00;
    PORTB = 0X00;
    while(1){
        unsigned char key = read_digital_keypad(LEVEL);
         
        if(key == SW1){
            PORTB = 0XFF;
            for(unsigned int delay = 50000; delay--;);
            PORTB = 0X00;
            for(unsigned int delay = 50000; delay--;);
        }
    }
    return;
}
