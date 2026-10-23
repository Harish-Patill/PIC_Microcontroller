/* 
 * File:   header.h
 * Author: Haris
 *
 * Created on 22 October, 2026, 4:21 PM
 */

#include "digital_keypad.h"
#include <xc.h>

#ifndef HEADER_H
#define	HEADER_H

void init_timer0();
void __interrupt() isr(void);

extern unsigned char period;

#endif	/* HEADER_H */

