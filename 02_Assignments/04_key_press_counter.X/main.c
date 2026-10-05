/*
 * File:   main.c
 * Author: Harish
 *
 * Created on 28 September, 2026, 4:26 PM
 */


#include <xc.h>
void display(char *ssd){
    for(int i=0;i<4;i++){
        PORTD=ssd[i];
        PORTA= PORTA & 0XF0|1<<i;
        
        for(int delay=1000; delay--;);  // how long the digit should be lit
    }
}

void main(void){
    TRISD=0X00;             // tris=0, means o/p
    PORTD=0X00;
    
    TRISA = TRISA & 0XF0;   // tris=0 for lower 4bits
    PORTA = PORTA & 0XF0;
    
    unsigned char digit[]={0XE7,0X21,0XCB,0X6B,0X2D,0X6E,0XEE,0X23,0XEF,0X6F};
    int flag=1;   // 1 = button is ready to count a new press
    int num=0;    // the number being displayed
    int count=0;  // measures how long the button is held
    char ssd[4];  // 4 patterns to show, one per digit
    
    while(1){                           
        if(RC0 == 0){                   // button is pressed (active-low)
            count++;                    // button is held, so the hold timer goes up

            if(count > 300){            // held for a long time = long press
                num = 0;                // reset the displayed number to 0
                flag = 0;               // block counting while still held
            }
            else if(flag){              // short press, and this is the first cycle of it
                num++;                  // add 1 to the number
                flag = 0;               // block more counting until the button is released
            }
        }
        else{                           // button is released
            flag = 1;                   // ready to count the next press
            count = 0;                  // restart the hold timer
        }

        ssd[0]=digit[num/1000];         // thousands digit pattern
        ssd[1]=digit[(num/100)%10];     // hundreds digit pattern
        ssd[2]=digit[(num/10)%10];      // tens digit pattern
        ssd[3]=digit[num%10];           // ones digit pattern

        display(ssd);                   // show all 4 digits once (repeats every loop, so it looks steady)
    }
    return;
}