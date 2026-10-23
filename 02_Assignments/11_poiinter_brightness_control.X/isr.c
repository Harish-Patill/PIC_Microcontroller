/*
 * File:   isr.c
 * Author: Harish
 *
 * Created on 22 October, 2026, 4:17 PM
 */


#include "header.h"

extern unsigned char duty_cycle;
extern unsigned char brightness_level;      // 1-100%, 0-10%
extern unsigned char period;

void __interrupt() isr(){
    static unsigned int iter = 0;
    static unsigned int count = 0;
    
    if(TMR0IF){
        TMR0 = TMR0 + 8;
        
        // LED on for duty_cycle% of time
        if(iter < duty_cycle){
            PORTBbits.RB0 = 1;  // LED ON
        }
        else{
            PORTBbits.RB0 = 0;  // LED OFF
        }
        
        iter++;
        if(iter >= period){  
            iter = 0;
        }
        
        // 5 sec glow logic
        if(brightness_level == 1){
            count++;
            if(count >= 100000){
                brightness_level = 0;
                duty_cycle = 10;
                count = 0;
            }
        }
        
        TMR0IF = 0;
    }
}



// below code is if LEVEL triggering is used. 
// Delay is implemented in the duty cycle incrementation, without delay duty cycle would become 100 in no time.

/*
#include "header.h"


extern unsigned char duty_cycle;
extern unsigned char brightness_level;
extern unsigned char period;

void __interrupt() isr(){
    static unsigned int iter = 0;
    static unsigned int count = 0;
    static unsigned int brightness_counter = 0;  // for gradually duty_cycle incrementation
    
    if(TMR0IF){
        TMR0 = TMR0 + 8;
        
        // PWM generation
        if(iter < duty_cycle){
            PORTBbits.RB0 = 1;
        }
        else{
            PORTBbits.RB0 = 0;
        }
        
        iter++;
        if(iter >= period){  
            iter = 0;
        }
        

        // Only increment duty_cycle every ~200 interrupts
        if(brightness_level == 1){
            brightness_counter++;
            
            // 200 interrupts = ~10ms per increment (for 20kHz ISR)
            if(brightness_counter >= 200){
                if(duty_cycle < period){
                    duty_cycle++;  // Increment slowly
                }
                brightness_counter = 0;
            }
            
            // Timeout working
            count++;
            if(count >= 100000){
                brightness_level = 0;
                duty_cycle = 10;
                count = 0;
            }
        }
        else{
            brightness_counter = 0;  
        }
        
        TMR0IF = 0;
    }
}
*/