/*
 * File:   external_interrupt0.c
 * Author: 
 *
 * Created on 5 November, 2025, 12:40 PM
 */


#include <xc.h>
#include "external_interrupt0.h"

void init_external_int0(void){
    INT0IE = 1;         //enabling the external interrupt0
    //INTEDG0 = 1;      //Interrupt on raising edge
    INT0IF = 0;
    TRISB0 = 1;
}