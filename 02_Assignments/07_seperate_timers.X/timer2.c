/*
 * File:   timer2.c
 * Author: Haris
 *
 * Created on 6 October, 2026, 4:38 PM
 */


#include <xc.h>
#include "header.h"

void init_timer2(){
    T2OUTPS3 = 0;
    T2OUTPS2 = 0;
    T2OUTPS1 = 0;
    T2OUTPS0 = 0;
    
    TMR2ON = 1;
    T2CKPS1 = 0;
    T2CKPS0 = 0;
}
