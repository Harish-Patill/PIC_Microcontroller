/*
 * File:   main.c
 * Author: 
 *
 * Created on 5 November, 2025, 12:40 PM
 */


#include <xc.h>
#include "external_interrupt0.h"

void init_config(void){
    init_external_int0();
    TRISB5 = 0; //RB5 as output pin
    RB5 = 0;
    GIE = 1;
    PEIE = 1;
}
void main(void) {
    init_config();
    while(1){
        ;
    }
    return;
}
