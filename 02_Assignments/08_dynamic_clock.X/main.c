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
    static unsigned char once = 1;                                      // Retains state between function calls

    if (trigger == EDGE){                                               // Check for edge-triggered mode
        if((PORTC & 0x0F) != ALL_RELEASED && once == 1){                // Detect the key pressd
            once = 0;                                                   // Prevent repeated detection
            return PORTC & 0x0F;                                        // Return the key
        }
        else if((PORTC & 0x0F) == ALL_RELEASED){                        // Check if all keys are released
            once = 1;                                                   // Enable next key detection
        }
    }

    return ALL_RELEASED;  // No new key press
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
    
    unsigned char digit[]={0XE7,0X21,0XCB,0X6B,0X2D,0X6E,0XEE,0X23,0XEF,0X6F};
    unsigned char ssd[4];
    
    unsigned char field=0;
    unsigned char mode=0;
    
    init_config();
    while(1){
        unsigned char key = read_dkp(EDGE);
        
        if(key == 0X07){        //switching  mode to mode
            mode = !mode;
        }
        if(mode==0){    //edit mode
            if(key == 0X0B){
                field = !field;
            }
            if(field == 0){       //minute field
                if (key == 0x0E){
                    minute = (minute + 1) % 60;
                }
                else if (key == 0x0D){
                    minute = (minute == 0) ? 59 : minute - 1;
                }                
            }
            else if(field == 1){     //hours field
                if(key == 0x0E){
                    hour = (hour + 1) % 24;
                }
                else if (key == 0x0D){
                    hour = (hour == 0) ? 23 : hour - 1;
                }
                
                ssd[0]= digit[(hour/10)%10];
                ssd[1]= digit[hour%10];
                ssd[2]= digit[(minute/10)%10];
                ssd[3]= digit[minute%10];
                
            }     
            if(count <= 10000){
                if (field == 0){
                    ssd[2] = 0x00;
                    ssd[3] = 0x00;
                }
                else{
                    ssd[0] = 0x00;
                    ssd[1] = 0x00;
                }
            }
                
            
            
        }
        else if(mode == 1){  //RUN mode
            if(sec == 60){
                minute++;
                if(minute==60){
                    hour++;
                    if(hour==24){
                        hour=0;
                    }
                    minute=0;
                }
                sec=0;
            }
            
            ssd[0] = digit[hour / 10];
            ssd[1] = digit[hour % 10];
            ssd[2] = digit[minute / 10];
            ssd[3] = digit[minute % 10];
            
             
            if(count < 10000){
//                ssd[1]=ssd[1]|(1<<4);
                ssd[1] |= 0x10;
            }
            
            
        }
         display(ssd);
            
       
    }
    return;
}