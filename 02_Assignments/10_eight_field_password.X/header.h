/* 
 * File:   header.h
 * Author: Harish
 *
 * Created on 20 October, 2026, 12:04 PM
 */

#include <xc.h>
#include "string.h"
#include "clcd.h"
#include "matrix_keypad.h"

#ifndef HEADER_H
#define	HEADER_H

unsigned int time = 100000;
unsigned int count0 = 0;     // Global for underscore blinking in ISR

void init_config();
void init_timer0(void);
void init_clcd();
void init_matrix_keypad();

#endif	/* HEADER_H */

