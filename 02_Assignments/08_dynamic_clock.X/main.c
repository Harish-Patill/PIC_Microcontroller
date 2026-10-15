///*
// * File:   main.c
// * Author: Harish
// *
// * Created on 9 October, 2026, 4:07 PM
// */


#include <xc.h>
#include "dynamic_header.h"

volatile unsigned char hour = 0;
volatile unsigned char minute = 0;
volatile unsigned char sec=0;
volatile unsigned int count=0;

void display(char ssd[]){
    for(int i=0;i<4;i++){
        PORTD = ssd[i];                             // Send segment pattern
        PORTA = (PORTA & 0XF0)|1<<i ;               // Select SSD digit
        for(int dealy = 1000;dealy--;);             // Small delay
    }
}

unsigned char read_dkp(unsigned char trigger){
//  Retains state between function calls
    static unsigned char once = 1;                  // For EDGE mode
    static unsigned char repeat_count = 0;          // For LEVEL mode repeat delay

    if (trigger == EDGE){                                               // Check for edge-triggered mode
        if((PORTC & 0x0F) != ALL_RELEASED && once == 1){                // Detect the key pressd
            once = 0;                                                   // Prevent repeated detection
            return PORTC & 0x0F;                                        // Return the key
        }
        else if((PORTC & 0x0F) == ALL_RELEASED){                        // Check if all keys are released
            once = 1;                                                   // Enable next key detection
        }
    }

    else if(trigger == LEVEL){                     // Level-triggered mode
        if((PORTC & 0x0F) != ALL_RELEASED){        // Is a key pressed?
            
            // start
            repeat_count++;
            if(repeat_count >= 50){              // Every 50 loop iterations
                repeat_count = 0;
                return PORTC & 0x0F;             // Return key, return it (every call!)
            }
        }
        else{
            repeat_count = 0;                    // Reset when released
        }
            // end
    }
    
    return ALL_RELEASED;  // No key pressed
}

void init_config(){
    PORTD=0X00;                         // 7segment uses PORTD & PORTA, thus config them
    TRISD=0X00;
    
    PORTA=PORTA & 0XF0;
    TRISA=TRISA & 0XF0;
    
    TRISC=TRISC | 0X0F;                 // digital_keypad uses PORTC, thus config em
    init_timer0();                      // config timer0
    
    GIE=1;                              // global enable
    PEIE=1;                             // pheripheral enable
}

void main(void) {
    
    unsigned char ssd[4];
    unsigned char digit[]={0XE7,0X21,0XCB,0X6B,0X2D,0X6E,0XEE,0X23,0XEF,0X6F};
    
    unsigned char mode=0;
    unsigned char field=0;
    
    init_config();
    while(1){
        unsigned char key = read_dkp(EDGE);
        
        if(key == SW4){         //switching  mode if its switch4
            mode = !mode;
        }
        
        //edit mode
        if(mode == EDIT_MODE){          
            if(key == SW3){             // switch the fields when its sw3
                field = !field;
            }
            
            //minute field
            if(field == MINUTES_FIELD){             
                if(key == SW1){         // increment
                    if(minute == 59){
                        minute = 0;
                    }
                    else if(minute < 59){
                        minute++;
                    }
                }
                else if(key == SW2){    //decrement
                    if(minute == 0){
                        minute = 59;
                    }
                    else if(minute > 0){
                        minute--;
                    }
                }                
            }
            
            //hours field
            else if(field == HOURS_FIELD){     
                if(key == SW1){
                    if(hour == 23){
                        hour = 0;
                    }
                    else{
                        hour++;
                    }
                }
                else if(key == SW2){
                    if(hour == 0){
                        hour = 23;
                    }
                    else{
                        hour--;
                    }
                }
            }     
            
            ssd[0]= digit[(hour/10)];
            ssd[1]= digit[hour%10];
            ssd[2]= digit[(minute/10)];
            ssd[3]= digit[minute%10];
            
            // logic for field blinking, to visualize what field user is on
            if(count <= 10000){
                if (field == MINUTES_FIELD){
                    ssd[2] = 0x00;
                    ssd[3] = 0x00;
                }
                else if(field == HOURS_FIELD){
                    ssd[0] = 0x00;
                    ssd[1] = 0x00;
                }
            }   
        }
        
        //run mode
        else if(mode == RUN_MODE){  
            if(sec == 60){
                minute++;
                if(minute == 60){
                    hour++;
                    if(hour==24){
                        hour=0;
                    }
                    minute=0;
                }
                sec=0;
            }
            ssd[0] = digit[hour/10];
            ssd[1] = digit[hour%10];
            ssd[2] = digit[minute/10];
            ssd[3] = digit[minute%10];
            
             
            if(count < 10000){   
             // this is for dp
                ssd[1] |= 0x10;      //the pos of dp is XXX1 XXXX, thus we do the 0x10
            }
            else{
                ssd[1] &= ~0x10;    // Decimal OFF (500ms)
            }
        }    
        display(ssd);
    }
    return;
}