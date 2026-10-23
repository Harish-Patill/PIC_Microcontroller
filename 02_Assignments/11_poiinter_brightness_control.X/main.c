/*
 * File:   main.c
 * Author: Harish
 *
 * Created on 22 October, 2026, 4:14 PM
 */


#include "header.h"

unsigned char period = 100;  // Configurable
unsigned char duty_cycle = 10;  // 10% brightness by default
unsigned char brightness_level = 0;  // 0=normal(10%), 1=highlight(100%)

void init_config(void){
    TRISB = 0x00;  // RB0 as output for LED
    PORTB = 0x00;
    PORTBbits.RB0 = 0;

    init_digital_keypad();
    init_timer0();
    
    GIE = 1;   // Global Interrupt Enable
    PEIE = 1;  // Peripheral Interrupt Enable
}

void main(void){
    init_config();
    
    unsigned char key = 0x00;
    
    while(1){
        key = read_digital_keypad(STATE_CHANGE);
        
        if(key == SWITCH1){             // When SWITCH1 100% brightness
            brightness_level = 1;       // Set brightness mode
        }
    }
    return;
}