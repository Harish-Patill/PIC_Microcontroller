/* 
 * File:   header.h
 * Author: Harish
 *
 * Created on 6 October, 2026, 11:02 AM
 */

#ifndef DIGITALKEYPAD_H
#define	DIGITALKEYPAD_H

void init_digital_keypad(void);
unsigned char read_digital_keypad(unsigned char trigger);

#define SW1 0X0E
#define SW2 0X0D
#define SW3 0X0B
#define SW4 0X07

#define ALL_RELEASED 0X0F

#define LEVEL 1
#define EDGE  0



#endif	/* DIGITALKEYPAD_H */