/*
 * File:   main.c
 * Author: Harish
 *
 * Created on 15 October, 2026, 3:58 PM
 */


#include <xc.h>
#include "clcd.h"

static void init_config(void){          // initial configuration
    init_clcd();
}

void main(void){
    init_config();
    
    unsigned char i;
    unsigned char delay;
    unsigned char size = 16;
    unsigned char str[]={"hehehe          "};

    clcd_print("Right Scrolling ",LINE1(0));    // prints continuously

    while(1){
        
        clcd_print(str,LINE2(0));
        
        // Right rotate: move last char to front
        char last=str[size-1];
        for(int j=size-1;j>0;j--){
            str[j]=str[j-1];
        }
        str[0]=last;
        __delay_ms(500);
            
    }
}