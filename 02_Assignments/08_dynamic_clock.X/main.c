///*
// * File:   main.c
// * Author: Harish
// *
// * Created on 9 October, 2026, 4:07 PM
// */
//
//
//#include <xc.h>
//#include "dynamic_header.h"
//
//unsigned int sec;
//
//unsigned char read_dkp(unsigned char trigger){
//    static unsigned char once =1;
//    
//     if(trigger == EDGE){
//        if((PORTC & 0X0F)!= ALL_RELEASED && (once ==1)){
//            once = 0;
//            return PORTC & 0X0F;
//        }
//        else if((PORTC & 0X0F)==ALL_RELEASED){
//            once = 1;
//        }
//        return ALL_RELEASED;
//    }
//}
//
//void display(char *ssd){
//    for(int i=0; i<4; i++){
//        PORTD = ssd[i];
//        PORTA = (PORTA & 0XF0) | 1<<i;
//        for(int delay=800; delay--;);   // this delay does the work of keeping the digits lit.
//    }
//}
//
//void init_config(){
//    TRISD =  0x00;                      // 7 seg
//    PORTD =  0x00;                  
//    TRISA =  TRISA & 0xF0;              // 7 seg    
//    PORTA =  PORTA & 0xF0; 
//    
//    TRISC=TRISC | 0X0F;                 // 4 switches
//    
//    init_timer0();
//    GIE = 1;
//    PIE = 1;
//}
//
//
//void main(void){
//    unsigned int key = 0;
//    unsigned int mode = 0;
//    unsigned int field = 0;
//    unsigned int min_field = 0;
//    unsigned int hour_field = 0;
//    
//    init_config();
//    
//    while(1){
//        key = read_dkp(EDGE);
//        
//        if(key == SW4){
//            mode = !mode;
//        }
//        
//        if(mode == 0){                  // edit mode
//            if(key == S3){
//                field = !field
//            }
//            if(min_field){
//                if(SW1){
//                    min++;
//                }
//                else if(SW2){
//                    min--;
//                }
//            }
//            else if(hour_field){
//                if(SW1){
//                    hour++;
//                }
//                else if(SW2){
//                    hour--;
//                }
//            }
//        }
//        
//        else if(mode == 1){             // run mode
//            if(sec == 1){
//                min_field++;
//                if(min_field == 60){
//                    hour_field++;
//                    if(hour_field == 23){
//                        hour_field=0;
//                    }
//                    min_field = 0;
//                }
//                sec = 0;
//            }
//        }
//    }
//    
//    return;
//}

/*
 * File:   main.c
 * Author: USER
 *
 * Created on October 9, 2026, 4:11 PM
 */


#include <xc.h>
#include "dynamic_header.h"

volatile unsigned char hour = 0;
volatile unsigned char minute = 0;
volatile unsigned char sec=0;
void init_config()
{
    PORTD=0X00;
    TRISD=0X00;
    
    PORTA=PORTA & 0XF0;
    TRISA=TRISA & 0XF0;
    
    TRISC=TRISC | 0X0F;
    init_timer0();
    
    GIE=1;
    PEIE=1;
}

unsigned char read_dkp(unsigned char trigger)
{
    static unsigned char once = 1;

    if (trigger == EDGE)
    {
        if ((PORTC & 0x0F) != ALL_RELEASED && once == 1)
        {
            once = 0;
            return PORTC & 0x0F;
        }
        else if ((PORTC & 0x0F) == ALL_RELEASED)
        {
            once = 1;
        }
    }

    return ALL_RELEASED;
}
void display(char *ssd)
{
    for(int i=0;i<4;i++)
    {
        PORTD = ssd[i];
        PORTA = (PORTA & 0XF0)|1<<i ;
        for(int dealy = 1000;dealy--;);
    }
}
void main(void) 
{
    
    unsigned char digit[]={0XE7,0X21,0XCB,0X6B,0X2D,0X6E,0XEE,0X23,0XEF,0X6F};
    unsigned char ssd[4];
    
    unsigned char field=0;
    unsigned char mode=0;
    
    init_config();
    while(1)
    {
        unsigned char key = read_dkp(EDGE);
        
        if(key == 0X07)        //switching  mode to mode
        {
            mode = !mode;
        }
        if(mode==0)    //edit mode
        {
            if(key == 0X0B)
            {
                field = !field;
            }
            if(field == 0)       //minute field
            {
                if (key == 0x0E)
                {
                    minute = (minute + 1) % 60;
                }
                else if (key == 0x0D)
                {
                    minute = (minute == 0) ? 59 : minute - 1;
                }
            }
            else if(field == 1)     //hours field
            {
                if(key == 0x0E)
                {
                    hour = (hour + 1) % 24;
                }
                else if (key == 0x0D)
                {
                    hour = (hour == 0) ? 23 : hour - 1;
                }
            }
            
        }
        else if(mode == 1)  //RUN mode
        {
            if(sec == 60)
            {
                minute++;
                if(minute==60)
                {
                    hour++;
                    if(hour==24)
                    {
                        hour=0;
                    }
                    minute=0;
                }
                sec=0;
            }
            
        }
        ssd[0]= digit[(hour/10)%10];
        ssd[1]= digit[hour%10];
        ssd[2]= digit[(minute/10)%10];
        ssd[3]= digit[minute%10];
            
        display(ssd);
    }
    return;
}