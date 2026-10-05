/*
 * File:   isr.c
 * Author: 
 *
 * Created on 5 November, 2025, 12:40 PM
 */

#include <xc.h>

void __interrupt() isr(){
    if(INT0IF){
        RB5 = !RB5;
        INT0IF = 0;
    }
}
