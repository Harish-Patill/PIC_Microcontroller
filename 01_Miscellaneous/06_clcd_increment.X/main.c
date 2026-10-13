/*
 * File:   main.c
 * Author: Harish
 *
 * Created on 7 October, 2026, 12:25 AM
 */



#include <xc.h>
#include "header.h"

static void init_config(void){          // initial configuration
    init_clcd();
}

void main(void){
    unsigned long num=0,temp;           // variables
    signed char i;
    init_config();

    clcd_print("Count:- ",LINE1(0));    // prints continuously

    while(1){
        temp=num;                                       // temp is copy of num
        for(i=9;i>=0;i--){                              // will start to display from the unit digit, which is 9th box!
            clcd_putch(temp%10+'0',LINE2(i));           // %10 will give the last digit + '0' to display the number else the ascii would be displayed
            temp/=10;                                   // update the temp to discard and be updated without the last digit
        }
        num++;
        __delay_ms(500);
    }
}